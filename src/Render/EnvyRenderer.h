//
// Created by ralex on 12/6/2024.
//

#ifndef ENVYRENDERER_H
#define ENVYRENDERER_H

#include <SDL_render.h>

class EnvyRenderer {
  public:
    EnvyRenderer();
    void initRenderer(SDL_Renderer* renderer);

    void drawGrid(int tileSize, int displayHeight, int displayWidth);
    void setColor(int r, int g, int b, int a);
    void resetColor();

    void fillRect(SDL_Rect *rect, int r, int g, int b);

  private:
    SDL_Window* _window;
    SDL_Renderer* _renderer{};
    int _r, _g, _b, _a;
};

#endif //ENVYRENDERER_H
