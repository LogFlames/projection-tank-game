#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Game
{

public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void set_window_title(const char* new_title);

    void handleEvents();
    void update(float deltaTime);
    void render();
    void clean();

    bool running() { return isRunning; };

    static SDL_Renderer *renderer;
    static SDL_Event event;

private:
    bool isRunning;

    SDL_Window *window;
    SDL_Surface *surface;

};
