#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(
        p_title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        p_w,
        p_h,
        SDL_WINDOW_SHOWN
    );

    if ( window == NULL ) {
        printf( "Window failed to initialise! SDL Error: %s\n", SDL_GetError() );
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if ( texture == NULL ) {
        printf( "Failed to load texture! SDL_image Error: %s\n", IMG_GetError() );
    }

    return texture;
}

void RenderWindow::cleanUp() {
    SDL_DestroyWindow( window );
}



void RenderWindow::clear() {
    SDL_RenderClear( renderer );
}

void RenderWindow::render( SDL_Texture* p_tex, int p_x, int p_y, int p_w, int p_h ) {
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = p_w;
    src.h = p_h;


    SDL_Rect dst;
    dst.x = p_x * 4;
    dst.y = p_y * 4;
    dst.w = p_w * 4;
    dst.h = p_h * 4;

    SDL_RenderCopy( renderer, p_tex, &src, &dst );
}

void RenderWindow::display() {
    SDL_RenderPresent( renderer );
}