#pragma once

// Include SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Include standard libraries
#include <stdio.h>

namespace EventHandler {
    void update( bool &quit );

    void mainMenu( bool &quit, bool &levelQuit, int &levelSelector, int &menuSelector ); 
    void scoreboard( bool &quit, bool &levelQuit, int &levelSelector );
}