//
// Created by ralex on 12/4/2024.
//

#include "Sprite.h"

#include "../Core/Events/EnvyEventSystem.h"

void onDraw(EnvyRenderer *renderer) {
    SDL_Rect spriteRect;
    renderer->setColor(255, 255, 255, SDL_ALPHA_OPAQUE);
    spriteRect.x = this->position.getX();
    spriteRect.y = this->position.getY();
    spriteRect.w = 32;
    spriteRect.h = 32;
    renderer->fillRect(&spriteRect, 255, 0, 0);
}

Sprite::Sprite() : position(0, 0) {
    auto& eventSystem = EnvyEventSystem::getInstance();
    eventSystem.addEventListener<EnvyRenderer*>("draw", std::function(onDraw));
}
