// Include SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Include standard libraries
#include <stdio.h>
#include <iostream>

// Extra inclused
#include "RenderWindow.hpp"
#include "EventHandler.hpp"

void close() {
    // Quits SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
        printf( "SDL failed to initialise! SDL Error: %s\n", SDL_GetError() );
    if ( !IMG_Init(IMG_INIT_PNG) )
        printf( "SDL_image failed to initialise! SDL_image Error: %s\n", IMG_GetError() );
    if ( TTF_Init() != 0 )
        printf( "SDL_ttf failed to initialise! SDL_ttf Error: %s\n", TTF_GetError() );

    // Create window
    RenderWindow window( "GuesserGame SDL v1.0", 1280, 720 );

    // Levels
    enum LEVELS {
        LEVEL_MAIN_MENU,
        LEVEL_SCOREBOARD,
        LEVEL_OPTIONS,
        LEVEL_START,
        LEVEL_INGAME,
        LEVEL_FINISH,
        LEVEL_DEV_MENU
    };

    // Level selector
    int levelSelector = LEVEL_MAIN_MENU;

    // Game Loop
    bool quit = false;
    while ( !quit ) {
        EventHandler::update( quit );

        window.clear();

        // Select level based on level selector
        switch (levelSelector)
        {
        case LEVEL_MAIN_MENU:
            window.mainMenu( quit, levelSelector );
            break;
        case LEVEL_SCOREBOARD:
            window.scoreboard( quit, levelSelector );
            break;
        default:
            break;
        }

        window.display();

        // Game update limiter to 100tps & 100fps because im to lazy to do it the actual way
        SDL_Delay(10);
    }

    // Clean up and close
    window.cleanUp();
    close();
    return 0;
}