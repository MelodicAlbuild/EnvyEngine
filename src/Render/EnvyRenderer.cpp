//
// Created by ralex on 12/6/2024.
//

#include "EnvyRenderer.h"

EnvyRenderer::EnvyRenderer() {
    _r = 0;
    _b = 0;
    _g = 0;
    _a = SDL_ALPHA_OPAQUE;
}

void EnvyRenderer::initRenderer(SDL_Renderer *renderer) {
    _renderer = renderer;
    _window = SDL_RenderGetWindow(renderer);
}


void EnvyRenderer::drawGrid(int tileSize, int displayHeight, int displayWidth) {

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    for (int y = 0; y < displayHeight; y += 32) {
        SDL_RenderDrawLine(_renderer, 0, y, displayWidth, y);
    }

    for (int x = 0; x < displayWidth; x += 32) {
        SDL_RenderDrawLine(_renderer, x, 0, x, displayHeight);
    }

    resetColor();
}

void EnvyRenderer::resetColor() {
    SDL_SetRenderDrawColor(_renderer, _r, _g, _b, _a);
}

void EnvyRenderer::setColor(int r, int g, int b, int a) {
    _r = r;
    _g = g;
    _b = b;
    _a = a;
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void EnvyRenderer::fillRect(SDL_Rect *rect, int r, int g, int b) {
    SDL_SetRenderDrawColor(_renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(_renderer, rect);
}
