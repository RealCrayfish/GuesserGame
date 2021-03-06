#pragma once

// Include SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Include standard libraries
#include <stdio.h>
#include <iostream>

class RenderWindow {
    public:
        RenderWindow( const char* title, int width, int height );
        void cleanUp();

        void clear();
        void render( SDL_Texture* texture, int x, int y, int w, int h );
        void display();

        SDL_Texture* loadTexture( const char* path );
        SDL_Texture* textureFromFont( TTF_Font* fromFont , const char* text ); // idk why but i decided to give font a weird name

        void mainMenu( bool &quit, int &levelSelector );
        void scoreboard( bool &quit, int &levelSelector );
    private:
        // Screen scale factor
        float SCREEN_SCALE = 1.0f;

        // Game window
        SDL_Window* window;
        // Game renderer
        SDL_Renderer* renderer;
        // Game font
        TTF_Font* font;
};