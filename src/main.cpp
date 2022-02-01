#include <iostream>
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include <sstream>

#include "Game.hpp"

Game *game = nullptr;

int main()
{

    const int FPS = 1000;
    const double frameDelay = 1000000.0 / FPS;

    std::chrono::steady_clock::time_point lastFrame;
    lastFrame = std::chrono::steady_clock::now();

    float deltaTime;
    const float maxDeltaTime = 1.0f / 6.0f;

    float currentFPS = 0.0f;
    int frameCounter = 0;
    float timeAccumulator = 0.0f;

    game = new Game();
    game->init("Particle Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1620, 1620, false);

    while (game->running())
    {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::micro> diff = now - lastFrame;

        if (diff.count() >= frameDelay)
        {
            deltaTime = (float)diff.count() * 0.000001;
            lastFrame = now;

            frameCounter++;
            timeAccumulator += deltaTime;
            if (timeAccumulator >= 1.0f)
            {
                currentFPS = frameCounter / timeAccumulator;
                frameCounter = 0;
                timeAccumulator = 0.0;
                std::stringstream ss;
                ss << "Particle Simulator " << currentFPS;
                game->set_window_title(ss.str().c_str());
            }

            if (deltaTime > maxDeltaTime)
            {
                deltaTime = maxDeltaTime;
            }

            game->handleEvents();
            game->update(deltaTime);
            game->render();
        } else {
            std::chrono::duration<long, std::micro> tilNextFrame = std::chrono::microseconds((long)(frameDelay - diff.count()));
            std::this_thread::sleep_for(tilNextFrame);
        }
    }

    game->clean();
}
