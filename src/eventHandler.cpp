// Include SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Include standard libraries
#include <stdio.h>
#include <iostream>

// Extra inclused
#include "EventHandler.hpp"

void EventHandler::update( bool &quit ) {
    SDL_Event e;
    // Check for game events
    while ( SDL_PollEvent(&e) > 0 ) {
        if ( e.type == SDL_QUIT ) quit = true;
    }
}

// Event handler for the Main Menu
void EventHandler::mainMenu( bool &quit, bool &levelQuit, int &levelSelector, int &menuSelector ) {
    // Get mouse pos
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (
        x >= 400 &&
        x <= (880) &&
        y >= 210 &&
        y <= 310
    ) menuSelector = 0;
    else if (
        x >= 400 &&
        x <= (880) &&
        y >= 340 &&
        y <= 410
    ) menuSelector = 1;
    else if (
        x >= 400 &&
        x <= (880) &&
        y >= 470 &&
        y <= 570
    ) menuSelector = 2;
    if (
        x >= 400 &&
        x <= (880) &&
        y >= 600 &&
        y <= 700
    ) menuSelector = 3;

    // Check for game events
    SDL_Event e;
    while ( SDL_PollEvent(&e) > 0 ) {
        if ( e.type == SDL_QUIT ) { quit = true; levelQuit = true; }
        // Check for mouse clicks
        else if ( e.type == SDL_MOUSEBUTTONUP )
        {
            SDL_MouseButtonEvent b = e.button;
            // If left button
            if ( b.button == SDL_BUTTON_LEFT ) {
                // Switch between levels
                switch (menuSelector)
                {
                case 0:
                    levelQuit = true;
                    levelSelector = 3;
                    break;
                case 1:
                    levelQuit = true;
                    levelSelector = 1;
                    break;
                case 2:
                    levelQuit = true;
                    levelSelector = 3;
                    break;
                case 3:
                    quit = true;
                    levelQuit = true;
                    break;
                
                default:
                    break;
                }
            }
        }
        
    }
}

// Event handler for the scoreboard
void EventHandler::scoreboard( bool &quit, bool &levelQuit, int &levelSelector ) {
    // Get mouse pos
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Check for game events
    SDL_Event e;
    while ( SDL_PollEvent(&e) > 0 ) {
        if ( e.type == SDL_QUIT ) { quit = true; levelQuit = true; }
        // Check for escape
        if ( e.type == SDL_KEYUP ) { if (e.key.keysym.sym == SDLK_ESCAPE ) {
            levelSelector = 0;
            levelQuit = true;
        }}
        
    }
}