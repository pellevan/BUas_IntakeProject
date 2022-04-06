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

        // Bullet managers
        snowballManager = new Snowy::BulletManager(BulletSprite, difficultyBallAmount, difficultyBallSpeed_Min, difficultyBallSpeed_Max);
        fireballManager = new Snowy::BulletManager(FireballSprite, 5, difficultyBallSpeed_Min + 150, difficultyBallSpeed_Max + 150);

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

            // Check whether  bullets are offscreen
            BorderCheckBullets(deltaTime);

            // Detect collisions between player and bullets
            CollisionDetection(snowballManager);
            CollisionDetection(fireballManager);

            // Spawn new bullets
            EnemySpawn();

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

    void Game::CollisionDetection(const Snowy::BulletManager* activeManager)
    {
        if (activeManager->DetectCollisions(*PlayerBody) && PlayerBody->GetHP() == 1)
        {
            GameMenu->SetActiveState(true);
            PlayerBody->ResetHP();
            gameOver = true;
            gameover_timer->reset();

            snowballManager->ClearArray();
            fireballManager->ClearArray();
        }

        else if (activeManager->DetectCollisions(*PlayerBody))
        {
            PlayerBody->LoseHP();

            snowballManager->ClearArray();
            fireballManager->ClearArray();
        }

    }

    void Game::BorderCheckBullets(float deltaTime)
    {
        snowballManager->BorderCheck(deltaTime);
        fireballManager->BorderCheck(deltaTime);
    }

    void Game::EnemySpawn()
    {
        snowballManager->SpawnBullets();
        fireballManager->SpawnBullets();
    }
    void Game::RenderEntities()
    {
        snowballManager->DrawBullets(screen);
        fireballManager->DrawBullets(screen);

        PlayerBody->DrawBody(50, 50, screen);
        CurrentHUD->DrawHearts();
    }
};