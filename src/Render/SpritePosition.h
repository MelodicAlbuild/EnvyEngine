#ifndef SPRITEPOSITION_H
#define SPRITEPOSITION_H

#include "./DirectionHelper.h"

class SpritePosition
{
public:
    SpritePosition(int x, int y) : _x(x), _y(y), _d(DirectionHelper::None), _moveComplete(true) {}

    void update(DirectionHelper::Direction d, float elapsedTime);
    void update(float elapsedTime);

    void setPosition(int x, int y) { _x = x; _y = y; }

    [[nodiscard]] bool isMoveComplete() const { return _moveComplete; }

    [[nodiscard]] int getX() const { return _x;}
    [[nodiscard]] int getY() const { return _y;}

    [[nodiscard]] int getTileX() const { return _x / _tileSize;}
    [[nodiscard]] int getTileY() const { return _y / _tileSize;}

private:
    const int _tileSize = 32;
    int _x;
    int _y;
    DirectionHelper::Direction _d;
    bool _moveComplete;
};

#endif //SPRITEPOSITION_H
