#ifndef GAME_H
#define GAME_H

#include <list>
#include <SDL.h>
#include <map>
#include <mutex>

#include "../Render/Sprite.h"
#include "../Render/EnvyRenderer.h"
#include "./Events/EnvyEventSystem.h"

#define SPEED 0.05

class Game {
  public:
    Game();
    ~Game();
    void start();
    void quit();
    void draw();
    void fillRect(SDL_Rect* rect, int r, int g, int b);
    void fpsChanged(int fps);
    void onQuit();
    void onKeyDown(SDL_Event* e);
    void onKeyUp(SDL_Event* e);
    void run();
    void update();

    // Get
    [[nodiscard]] SDL_Renderer* getRenderer() const {return renderer;};
    [[nodiscard]] static Game* getInstance() {
      if (instance == nullptr) {
        std::lock_guard lock(mtx);
        if (instance == nullptr) {
          instance = new Game();
        }
      }
      return instance;
    };
    [[nodiscard]] std::list<Sprite> getSpriteList() const {return sprites;};
  private:
    // Instance
    static Game* instance;
    static std::mutex mtx;

    // Vars
    std::map<int,int> keys;
    int frameS;
    int running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    EnvyRenderer* envyRenderer;

    // Lists
    std::list<Sprite> sprites;
};

#endif //GAME_H
