//
// Created by ralex on 12/4/2024.
//

#include "Sprite.h"

#include <SDL_log.h>

#include "../Core/Events/EventTypes/Events.h"

Sprite::Sprite() : position(0, 0)
{
    SDL_Log("X: %d, Y: %d", this->position.getX(), this->position.getY());

    std::function<void(DirectionHelper::Direction)> moveHandler = [this]<typename T0>(T0 && PH1) { onMoveUpdate(std::forward<T0>(PH1)); };
    this->subscribe<SpriteMoveEvent<DirectionHelper::Direction>>(moveHandler);

    std::function<void(EnvyRenderer *)> drawHandler = [this]<typename T0>(T0 && PH1) { onDraw(std::forward<T0>(PH1)); };
    this->subscribe<DrawEvent<EnvyRenderer *>>(drawHandler);
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
    SDL_Log("Sprite::onMoveUpdate");
    SDL_Log("X: %d, Y: %d", this->position.getX(), this->position.getY());

    if (dir == DirectionHelper::Direction::None && this->position.isMoveComplete()) return;

    if (dir != DirectionHelper::Direction::None && this->position.isMoveComplete())
    {
        this->position.update(dir, speed);
    }
    else
    {
        this->position.update(speed);
    }
}
