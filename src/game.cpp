#include "Game.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
        flags |= SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialised" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window Created" << std::endl;
        } else {
            std::cout << "Failed to create window. SDL_Error: " << SDL_GetError() << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
            SDL_RenderSetScale(renderer, width / 1080.0f, height / 1080.0f);
            std::cout << "Renderer created" << std::endl;
        } else {
            std::cout << "Failed to create renderer. SDL_Error: " << SDL_GetError() << std::endl;
        }

        surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
        if (surface)
        {
            std::cout << "Surface created" << std::endl;
        } else {
            std::cout << "Failed to create surface. SDL_Error: " << SDL_GetError() << std::endl;
        }

        isRunning = true;
    } else {
        std::cout << "SDL_Init has failed. SDL_Error: " << SDL_GetError() << std::endl;

        isRunning = false;
    }
}

void Game::set_window_title(const char* new_title)
{
    SDL_SetWindowTitle(window, new_title);
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update(float deltaTime)
{
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderClear(renderer);

    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);

    // for (int i = 0; i < PARTICLE_COUNT; ++i)
    // {
    //     SDL_Rect rect = { px[i] - ps[i] / 2.0f * 2.0f, py[i] - ps[i] / 2.0f * 2.0f, ps[i] * 2.0f, ps[i] * 2.0f };
    //     SDL_RenderFillRect(renderer, &rect);
    // }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game Cleaned" << std::endl;
}
