#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdio.h>

#include "RenderWindow.hpp"

int main (int argc, char* argv[]) {
    if ( SDL_Init( SDL_INIT_VIDEO ) > 0 )
        printf( "SDL failed to initialise! SDL Error: %s\n", SDL_GetError() );
    if ( !IMG_Init( IMG_INIT_PNG ) )
        printf( "SDL_image has failed to initialise! SDL_image Error: %s\n", IMG_GetError() );

    RenderWindow window("LearnSDL v1.0", 1280, 720);

    SDL_Texture* grassTexture = window.loadTexture( "res/gfx/ground_grass_1.png" );

    bool gameRunning = true;
    SDL_Event event;

    while ( gameRunning ) {
        while ( SDL_PollEvent( &event ) > 0 ) {
            if ( event.type == SDL_QUIT ) gameRunning = false;
        }

        window.clear();
        window.render(grassTexture, 32, 32, 32, 32);
        window.display();

        // Keep the game to 20 TPS
        SDL_Delay(50);
    }


    window.cleanUp();
    SDL_Quit();

    return 0;
}