#include "game.h"
#include "surface.h"
#include <iostream>

#include "Windows.h"

#pragma warning( disable : 26812 )

//    ******** ****     **   *******   **       **   *******     *******   *******     ********  ********
//   **////// /**/**   /**  **/////** /**      /**  /**////**   **/////** /**////**   **//////**/**///// 
//  /**       /**//**  /** **     //**/**   *  /**  /**    /** **     //**/**    /** **      // /**      
//  /*********/** //** /**/**      /**/**  *** /**  /**    /**/**      /**/**    /**/**         /******* 
//  ////////**/**  //**/**/**      /**/** **/**/**  /**    /**/**      /**/**    /**/**    *****/**////  
//         /**/**   //****//**     ** /**** //****  /**    ** //**     ** /**    ** //**  ////**/**      
//   ******** /**    //*** //*******  /**/   ///**  /*******   //*******  /*******   //******** /********
//  ////////  //      ///   ///////   //       //   ///////     ///////   ///////     ////////  //////// 

namespace Tmpl8
{
    void Game::KeyUp(const SDL_Scancode key)
    {
        switch (key)
        {
        case SDL_SCANCODE_W:
            movementStates.at("m_up") = 0;
            break;

        case SDL_SCANCODE_S:
            movementStates.at("m_down") = 0;
            break;

        case SDL_SCANCODE_A:
            movementStates.at("m_left") = 0;
            break;

        case SDL_SCANCODE_D:
            movementStates.at("m_right") = 0;
            break;
        default:
            break;
        }
    }

    void Game::KeyDown(const SDL_Scancode key)
    {
        switch (key)
        {
        case SDL_SCANCODE_W:
            movementStates.at("m_up") = 1;
            break;

        case SDL_SCANCODE_S:
            movementStates.at("m_down") = 1;
            break;

        case SDL_SCANCODE_A:
            movementStates.at("m_left") = 1;
            break;

        case SDL_SCANCODE_D:
            movementStates.at("m_right") = 1;
            break;

        case SDL_SCANCODE_RETURN:
            // Remove IF-statement for cheat code >:) 
            if (GameMenu->GetActiveState() == true)
            {
                EnemySpawn();
                PlayerBody->ResetHP();
                GameMenu->SetActiveState(false);
            }
            break;

        case SDL_SCANCODE_X:
            if (GameMenu->GetActiveState()) shutDown = true;
            break;

        default:
            break;
        }
    }

    Game::Game()
    = default;

    // Initialize variables
	void Game::Init()
	{
        // Bullet properties
        // :: Snowflake sprite from https://www.dreamstime.com/stock-illustration-bit-pixel-crystalline-snowflake-eps-vector-each-square-separated-easy-modifications-image47935947 
        BulletSprite = new Sprite(new Surface("assets/snowflake.png"), 1);
        BulletSize = { 25.f, 25.f };

        // Fireball bullets properties
        // :: Sprite from https://www.wattpad.com/530348816-sandbox-pixel-art-fireball
        FireballSprite = new Sprite(new Surface("assets/fireball2.png"), 1);

        // Bounds
        GameBounds = new Snowy::Bounds(0, 0, ScreenWidth, ScreenHeight);
        
        // Booleans (game rules)
        gameOver = false;
        shutDown = false;

        // KinematicBodies
        // :: Penguin sprite from https://media.spelunky.fyi/mods/file/01EQXP6Y72AD3Y7Q079XEFAXJW/01EQXP6Y71DD53R8865H62HY3B/penguin.png
        PlayerSprite = new Sprite(new Surface("assets/penguin.png"), 2);
        PlayerSprite->SetFrame(0);
		PlayerBody = new Snowy::Player(PlayerSprite);
		PlayerBody->SetPosition(1050, 860);
        PlayerBody->setHitboxDiameter(35.f);

        // HUD
        CurrentHUD = new Snowy::HUD(PlayerBody, screen);
			
        // Background Sprite
        Background = new Sprite(new Surface("assets/index.png"), 1);

        // Game over sprite
        GameOverImage = new Sprite(new Surface("assets/gameover.png"), 1);
        
        // Menu
        GameMenu = new Snowy::Menu(new Sprite(new Surface("assets/menu.png"),1));

        // Windows properties
		ShowCursor(false);

        // Initialize game over timer
        gameover_timer = new Snowy::Timer(0.0);
	}
	
	// Shutdown destructors
	void Game::Shutdown() const
	{
        // Bullets
        delete this->BulletSprite;

        // Bounds
        delete GameBounds;
        
        // Player
        delete this->PlayerSprite;
        delete this->PlayerBody;

        // Menu & background
        delete this->Background;
        delete this->GameMenu;
	}

	// Update function
	void Game::Tick(float deltaTime)
	{
        // If the player has lost the game, show the gameover screen for 3 second and then return to main menu
        if (GameMenu->GetActiveState() && gameOver)
        {
            if (gameover_timer->elapsed_sec() > 3.0) gameOver = false;
            GameOverImage->Draw(screen, 0, 0);
        }

        // Check whether the Menu of Game is active
        else if (GameMenu->GetActiveState() == true)
        {
            GameMenu->DrawOnScreen(screen);
        }

        // If the menu isn't active (anymore), start the game loop
        else 
        {
            // Clear the buffer
            screen->Clear(0);

            // Draw the background
            Background->Draw(screen, 0, 0);

            // Calculate movement and border checks
            Movement(deltaTime);

            // Spawn new bullets
            EnemySpawn();

            // Check whether  bullets are offscreen
            DrawBullets(deltaTime);

            // Detect collisions between player and bullets
            CollisionDetection();

            // Render all entities (bullets, player, hearts in HUD etc.)
            RenderEntities();
        }
    }

	void Game::Movement(float deltaTime) const
	{
        // Case: user pressed A
        if (movementStates.at("m_left")) 
        {
            PlayerBody->AddToVelocity(-1.f, 0.f);
            PlayerSprite->SetFrame(1);
            // PlayerBody->setDirection(0);
        }

        // Case: user pressed D
        if (movementStates.at("m_right"))
        {
            PlayerBody->AddToVelocity(1.f, 0.f);
            PlayerSprite->SetFrame(0);
            // PlayerBody->setDirection(1);
        }

        // Calculate WOULD BE newPosition (needs to be verified with borders first)
        const vec2 newPosition = PlayerBody->GetPosition() + (PlayerBody->GetVelocity() * deltaTime * movementSpeed);

        // Border / bounds check
        if (newPosition.x > GameBounds->GetBounds().at("left") - 20.f && newPosition.x < GameBounds->GetBounds().at("right") - 50.f)
        {
            PlayerBody->SetPosition(newPosition);
        }

        // Reset velocity for next frame calculation
        PlayerBody->SetVelocity(0.f, 0.f);
	}

    void Game::CollisionDetection()
    {
        // Collision detections between bullets and PlayerBody
        for (const Snowy::Bullet& bulletIT : bullets)
        {
            if (Snowy::detectCollision(bulletIT, *PlayerBody) && PlayerBody->GetHP() == 1)
            {
                GameMenu->SetActiveState(true);
                PlayerBody->ResetHP();
                gameOver = true;
                gameover_timer->reset();

                bullets.clear();
                uniqueBullets.clear();

                //shutDown = true;
            }

            if (Snowy::detectCollision(bulletIT, *PlayerBody))
            {
                PlayerBody->LoseHP();
                bullets.clear();
                uniqueBullets.clear();

                //shutDown = true;
            }
        }

        // Collision detections betweens Uniquebullets and PlayerBody
    }

    void Game::DrawBullets(float deltaTime)
    {
        /*for (int i = static_cast<int>(bullets.size()) - 1; i >= 0; i--)
        {
            bullets[i].SetPosition(bullets[i].GetPosition() + bullets[i].GetVelocity() * deltaTime);
            if (bullets[i].GetPosition().x > 0 &&
                bullets[i].GetPosition().x < ScreenWidth - 25 &&
                bullets[i].GetPosition().y > 0 &&
                bullets[i].GetPosition().y < ScreenHeight - 25)
            {
                bullets[i].DrawBody(static_cast<int>(BulletSize.x), static_cast<int>(BulletSize.y), screen);
            }
            else
            {
                bullets.erase(bullets.begin() + i);
                ballsOnScreen--;
            }
        }*/
        for (auto iter = bullets.begin(); iter != bullets.end(); )
        {
            auto& bullet = *iter;
            bullet.SetPosition(bullet.GetPosition() + bullet.GetVelocity() * deltaTime);
            if (bullet.GetPosition().x > 0 &&
                bullet.GetPosition().x < ScreenWidth - 25 &&
                bullet.GetPosition().y > 0 &&
                bullet.GetPosition().y < ScreenHeight - 25)
            {
                ++iter;
            }
            else
            {
                iter = bullets.erase(iter);
            }
        }

        for (auto iter = uniqueBullets.begin(); iter != uniqueBullets.end(); )
        {
            auto& bullet = *iter;
            bullet.SetPosition(bullet.GetPosition() + bullet.GetVelocity() * deltaTime);
            if (bullet.GetPosition().x > 0 &&
                bullet.GetPosition().x < ScreenWidth - 25 &&
                bullet.GetPosition().y > 0 &&
                bullet.GetPosition().y < ScreenHeight - 25)
            {
                ++iter;
            }
            else
            {
                iter = uniqueBullets.erase(iter);
            }
        }
    }

    void Game::EnemySpawn()
    {
        for (int i = 0; i < (difficultyBallAmount - static_cast<int>(bullets.size())); i++)
        {
            bullets.emplace_back(BulletSprite);
            bullets[bullets.size()-1].SetPosition(static_cast<float>(IRand(ScreenWidth - 50)), static_cast<float>(IRand(300)));
            bullets[bullets.size()-1].SetVelocity(0.f, static_cast<float>(rand() % difficultyBallSpeed_Min + difficultyBallSpeed_Max));
        }

        if (IRand(100) == 1)
        {
            uniqueBullets.emplace_back(FireballSprite, 1);
            uniqueBullets[uniqueBullets.size() - 1].SetPosition(static_cast<float>(IRand(ScreenWidth - 50)), static_cast<float>(IRand(300)));
            uniqueBullets[uniqueBullets.size() - 1].SetVelocity(0.f, static_cast<float>(rand() % difficultyBallSpeed_Min + difficultyBallSpeed_Max));
        }
    }
    void Game::RenderEntities()
    {
        for (auto iter = bullets.begin(); iter != bullets.end(); )
        {
            auto& bullet = *iter;
            bullet.DrawBody(static_cast<int>(BulletSize.x), static_cast<int>(BulletSize.y), screen);
            /*screen->Line(bullet.GetPosition().x + bullet.getHitboxRadius(), bullet.GetPosition().y + bullet.getHitboxRadius(), bullet.GetPosition().x + bullet.getHitboxRadius(), ScreenHeight, 0xFF0000);*/
            ++iter;
        }

        for (auto iter = uniqueBullets.begin(); iter != uniqueBullets.end(); )
        {
            auto& bullet = *iter;
            bullet.DrawBody(static_cast<int>(BulletSize.x), static_cast<int>(BulletSize.y), screen);
            /*screen->Line(bullet.GetPosition().x + bullet.getHitboxRadius(), bullet.GetPosition().y + bullet.getHitboxRadius(), bullet.GetPosition().x + bullet.getHitboxRadius(), ScreenHeight, 0xFF0000);*/
            ++iter;
        }

        PlayerBody->DrawBody(50, 50, screen);
        CurrentHUD->DrawHearts();
    }
};