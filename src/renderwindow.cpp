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

// Creates a window and renderer for the game
RenderWindow::RenderWindow( const char* title, int width, int height )
    :window(NULL), renderer(NULL), font(NULL)
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

    font = TTF_OpenFont( "res/gfx/fonts/press_start.ttf", 72 );
}

// Cleans up SDL
void RenderWindow::cleanUp() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    font = NULL;
    renderer = NULL;
    window = NULL;
}

// Clears the screen
void RenderWindow::clear() { SDL_RenderClear(renderer); }

// Displays everything to the screen
void RenderWindow::display() { SDL_RenderPresent(renderer); }

// Renders a texture to the screen
void RenderWindow::render( SDL_Texture* texture, int x, int y, int w, int h ) {
    // SDL_Rect src;
    // src.x = 0;
    // src.y = 0;
    // src.w = w;
    // src.h = h;

    SDL_Rect dst;
    dst.x = x * SCREEN_SCALE;
    dst.y = y * SCREEN_SCALE;
    dst.w = w * SCREEN_SCALE;
    dst.h = h * SCREEN_SCALE;

    SDL_RenderCopy( renderer, texture, NULL, &dst );
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

SDL_Texture* RenderWindow::textureFromFont( TTF_Font* fromFont , const char* text ) {
    SDL_Colour white = { 225, 225, 225 };
    SDL_Texture* texture = NULL;
    SDL_Surface* surfaceMsg = TTF_RenderText_Solid( fromFont, text, white );
    texture = SDL_CreateTextureFromSurface( renderer, surfaceMsg );

    return texture;
}










// Actually rendering stuff ig

// Main Menu
void RenderWindow::mainMenu( bool &quit, int &levelSelector ) {
    // Main Menu quit flag
    bool levelQuit = false;

    // Menu stuff ig
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
    SDL_Texture* startButton = loadTexture( "res/gfx/main_menu/start.png" );
    SDL_Texture* scoreboardButton = loadTexture( "res/gfx/main_menu/scoreboard.png" );
    SDL_Texture* optionsButton = loadTexture( "res/gfx/main_menu/options.png" );
    SDL_Texture* quitButton = loadTexture( "res/gfx/main_menu/quit.png" );

    // Load media for each selected button
    SDL_Texture* startButtonSelected = loadTexture( "res/gfx/main_menu/start_selected.png" );
    SDL_Texture* scoreboardButtonSelected = loadTexture( "res/gfx/main_menu/scoreboard_selected.png" );
    SDL_Texture* optionsButtonSelected = loadTexture( "res/gfx/main_menu/options_selected.png" );
    SDL_Texture* quitButtonSelected = loadTexture( "res/gfx/main_menu/quit_selected.png" );

    // Pre-render buttons because C++ and SDL is stupid
    // render( guesserGameLogo, 320, 30, 640, 150 );
    // render( startButton, 400, 210, 480, 100 );
    // render( scoreboardButton, 400, 340, 480, 100 );
    // render( optionsButton, 400, 470, 480, 100 );
    // render( quitButton, 400, 600, 480, 100 );

    // Menu loop
    while ( !levelQuit ) {
        // Event handler for main menu
        EventHandler::mainMenu( quit, levelQuit, levelSelector, menuSelector );

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

// Scoreboard
void RenderWindow::scoreboard( bool &quit, int &levelSelector ) {
    // Main Menu quit flag
    bool levelQuit = false;

    // Menu stuff ig
    SDL_Texture* guesserGameLogo = loadTexture( "res/gfx/guesser_game.png" );


    // Load media for each button
    SDL_Texture* startButton = textureFromFont( font, "Hello Test" );
    SDL_Texture* optionsButton = loadTexture( "res/gfx/scoreboard/" );
    SDL_Texture* quitButton = loadTexture( "res/gfx/scoreboard/" );

    // Menu loop
    while ( !levelQuit ) {
        // Event handler for main menu
        EventHandler::scoreboard( quit, levelQuit, levelSelector );

        // Clear renderer
        clear();

        // Render stuff -- add 130 each button
        render( guesserGameLogo, 320, 30, 640, 150 );
        render( startButton, 400, 210, 480, 100 );
        render( optionsButton, 400, 470, 480, 100 );
        render( quitButton, 400, 600, 480, 100 );

        display();
    }
}