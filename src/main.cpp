// Include SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
        printf( "SDL_image failed to initialise! SDL_image Error: %s\n", SDL_GetError() );

    // Create window
    RenderWindow window( "GuesserGame SDL v1.0", 1280, 720 );

    // Game Loop
    bool quit = false;
    while ( !quit ) {
        EventHandler::update( quit );

        window.clear();

        window.mainMenu( quit );

        window.display();

        // Game update limiter to 100tps & 100fps because im to lazy to do it the actual way
        SDL_Delay(10);
    }

    // Clean up and close
    window.cleanUp();
    close();
    return 0;
}