// Include SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Include standard libraries
#include <stdio.h>
#include <iostream>

// Extra inclused
#include "RenderWindow.hpp"
#include "EventHandler.hpp"

// Creates a window and renderer for the game
RenderWindow::RenderWindow( const char* title, int width, int height )
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED, // it should be blue but isnt so its very scary
        SDL_WINDOWPOS_UNDEFINED, // ^
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf( "Window failed to initialise! SDL Error: %s\n", SDL_GetError() );
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
}

// Cleans up SDL
void RenderWindow::cleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
}

// Clears the screen
void RenderWindow::clear() { SDL_RenderClear(renderer); }

// Displays everything to the screen
void RenderWindow::display() { SDL_RenderPresent(renderer); }

// Renders a texture to the screen
void RenderWindow::render( SDL_Texture* texture, int x, int y, int w, int h ) {
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = w;
    src.h = h;

    SDL_Rect dst;
    dst.x = x * SCREEN_SCALE;
    dst.y = y * SCREEN_SCALE;
    dst.w = w * SCREEN_SCALE;
    dst.h = h * SCREEN_SCALE;

    SDL_RenderCopy( renderer, texture, &src, &dst );
}

// Loads textures to use
SDL_Texture* RenderWindow::loadTexture( const char* path ) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture( renderer, path );

    if ( texture == NULL ) {
        printf( "Failed to load texture! SDL_image Error%s\n", IMG_GetError() );
    }

    return texture;
}










// Actually rendering stuff ig

void RenderWindow::mainMenu( bool &quit ) {
    SDL_Texture* guesserGameLogo = loadTexture( "res/gfx/guesser_game.png" );
    enum MENU_BUTTONS {
        BUTTON_START,
        BUTTON_SCOREBOARD,
        BUTTON_OPTIONS,
        BUTTON_QUIT,
        BUTTON_TOTAL
    };

    int menuSelector = 0;

    // Load media for each button
    SDL_Texture* startButton = loadTexture( "res/gfx/start.png" );
    SDL_Texture* scoreboardButton = loadTexture( "res/gfx/scoreboard.png" );
    SDL_Texture* optionsButton = loadTexture( "res/gfx/options.png" );
    SDL_Texture* quitButton = loadTexture( "res/gfx/quit.png" );

    // Load media for each selected button
    SDL_Texture* startButtonSelected = loadTexture( "res/gfx/start_selected.png" );
    SDL_Texture* scoreboardButtonSelected = loadTexture( "res/gfx/scoreboard_selected.png" );
    SDL_Texture* optionsButtonSelected = loadTexture( "res/gfx/options_selected.png" );
    SDL_Texture* quitButtonSelected = loadTexture( "res/gfx/quit_selected.png" );

    // Pre-render buttons because C++ and SDL is stupid
    // render( guesserGameLogo, 320, 30, 640, 150 );
    // render( startButton, 400, 210, 480, 100 );
    // render( scoreboardButton, 400, 340, 480, 100 );
    // render( optionsButton, 400, 470, 480, 100 );
    // render( quitButton, 400, 600, 480, 100 );

    // Menu loop
    while ( !quit ) {
        // Event handler for main menu
        EventHandler::mainMenu( quit, menuSelector );

        // Clear renderer
        clear();

        // Render stuff -- add 130 each button
        render( guesserGameLogo, 320, 30, 640, 150 );
        render( startButton, 400, 210, 480, 100 );
        render( scoreboardButton, 400, 340, 480, 100 );
        render( optionsButton, 400, 470, 480, 100 );
        render( quitButton, 400, 600, 480, 100 );

        // Switch button based on menu selector value
        switch (menuSelector)
        {
        case BUTTON_START:
            render( startButtonSelected, 400, 210, 480, 100 );
            break;
        case BUTTON_SCOREBOARD:
            render( scoreboardButtonSelected, 400, 340, 480, 100 );
            break;
        case BUTTON_OPTIONS:
            render( optionsButtonSelected, 400, 470, 480, 100 );
            break;
        case BUTTON_QUIT:
            render( quitButtonSelected, 400, 600, 480, 100 );
            break;
        default:
            break;
        }

        display();
    }
}