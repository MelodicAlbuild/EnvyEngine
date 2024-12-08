#include "Game.h"

#include <cstdio>
#include <iostream>

#include "Events/EventTypes/Events.h"

enum
{
    DISPLAY_WIDTH = 1280,
    DISPLAY_HEIGHT = 720,
    UPDATE_RANGE = 1000 / 128
};

std::mutex Game::mtx;
Game *Game::instance = nullptr;

Game::Game() : frameS(0), running(0), window(nullptr), renderer(nullptr) {}

Game::~Game()
{
    this->quit();
}

void Game::start()
{
    instance = this;

    int flags = SDL_WINDOW_SHOWN;
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        return;
    }

    if (SDL_CreateWindowAndRenderer(DISPLAY_WIDTH, DISPLAY_HEIGHT, flags, &window, &renderer))
    {
        return;
    }
    envyRenderer.initRenderer(renderer);
    this->running = 1;
    run();
}

void Game::createSprites() {
    Sprite block{};
    block.position.setPosition(0, 0);
    sprites.push_back(block);
}

void Game::draw()
{
    SDL_RenderClear(renderer);

    auto& eventManager = EnvyEventManager::getInstance();
    eventManager.getEvent<DrawEvent<EnvyRenderer*>>().notify(&envyRenderer);

    envyRenderer.drawGrid(32, DISPLAY_HEIGHT, DISPLAY_WIDTH);

    SDL_RenderPresent(renderer);
}

void Game::quit()
{
    if (nullptr != renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (nullptr != window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Game::fpsChanged(int fps)
{
    char sFps[128];
    sprintf(sFps, "%s: %d FPS", "EnvyEngine", fps);
    SDL_SetWindowTitle(window, sFps);
}

void Game::onQuit()
{
    running = 0;
}

void Game::run()
{
    int past = SDL_GetTicks();
    int now = past, pastFps = past;
    int fps = 0, framesSkipped = 0;
    createSprites();
    SDL_Event event;
    while (running)
    {
        int timeElapsed = 0;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                onQuit();
                break;
            case SDL_KEYDOWN:
                onKeyDown(&event);
                break;
            case SDL_KEYUP:
                onKeyUp(&event);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
                break;
            }
        }

        timeElapsed = (now = SDL_GetTicks()) - past;
        if (timeElapsed >= UPDATE_RANGE)
        {
            past = now;
            update();
            if (framesSkipped++ > frameS)
            {
                draw();
                fps++;
                framesSkipped = 0;
            }
        }

        if (now - pastFps >= 1000)
        {
            pastFps = now;
            fpsChanged(fps);
            fps = 0;
        }

        SDL_Delay(1);
    }
}

void Game::update()
{
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    if (keys[SDLK_LEFT])
    {
        moveLeft = true;
    }
    else
    {
        moveLeft = false;
    }
    if (keys[SDLK_RIGHT])
    {
        moveRight = true;
    }
    else
    {
        moveRight = false;
    }
    if (keys[SDLK_UP])
    {
        moveUp = true;
    }
    else
    {
        moveUp = false;
    }
    if (keys[SDLK_DOWN])
    {
        moveDown = true;
    }
    else
    {
        moveDown = false;
    }

    auto& eventManager = EnvyEventManager::getInstance();

    SDL_Log("%d, %d, %d, %d", moveLeft, moveRight, moveUp, moveDown);

    if (moveLeft || moveRight || moveUp || moveDown)
    {
        eventManager.getEvent<SpriteMoveEvent<DirectionHelper::Direction>>().notify(DirectionHelper::computeFromBooleans(moveLeft, moveRight, moveUp, moveDown));
    }
    else
    {
        eventManager.getEvent<SpriteMoveEvent<DirectionHelper::Direction>>().notify(DirectionHelper::Direction::None);
    }
}

void Game::onKeyDown(SDL_Event *e)
{
    keys[e->key.keysym.sym] = 1;
}

void Game::onKeyUp(SDL_Event *e)
{
    keys[e->key.keysym.sym] = 0;
}
