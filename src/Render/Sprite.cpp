//
// Created by MelodicAlbuild on 12/4/2024.
//

#include "Sprite.h"

#include <SDL_log.h>

#include "../Core/Events/EventTypes/Events.h"

Sprite::Sprite() : position(0, 0)
{
    std::function moveHandler = [this](DirectionHelper::Direction &dir)
    { onMoveUpdate(dir); };
    this->subscribe<SpriteMoveEvent<DirectionHelper::Direction>>(moveHandler);

    std::function drawHandler = [this](EnvyRenderer &renderer)
    { onDraw(&renderer); };
    this->subscribe<DrawEvent<EnvyRenderer>>(drawHandler);
}

void Sprite::onDraw(EnvyRenderer *renderer)
{
    SDL_Rect spriteRect;
    renderer->setColor(255, 255, 255, SDL_ALPHA_OPAQUE);
    spriteRect.x = this->position.getX();
    spriteRect.y = this->position.getY();
    spriteRect.w = 32;
    spriteRect.h = 32;
    renderer->fillRect(&spriteRect, 255, 0, 0);
}

void Sprite::onMoveUpdate(DirectionHelper::Direction dir)
{
    if (dir != DirectionHelper::Direction::None && this->position.isMoveComplete())
    {
        this->position.update(dir, SPEED);
    }
    else
    {
        this->position.update(SPEED);
    }
}
