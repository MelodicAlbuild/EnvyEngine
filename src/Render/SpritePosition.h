#ifndef SPRITEPOSITION_H
#define SPRITEPOSITION_H

class SpritePosition
{
public:
    enum Direction { Left, Right, Up, Down, None };

    SpritePosition(int x, int y) : _x(x), _y(y), _d(), _moveComplete(true) {}

    static Direction computeFromBooleans(bool left, bool right, bool up, bool down);

    void update(Direction d, float elapsedTime);
    void update(float elapsedTime);

    [[nodiscard]] bool isMoveComplete() const { return _moveComplete; }

    [[nodiscard]] int getX() const { return _x;}
    [[nodiscard]] int getY() const { return _y;}

    [[nodiscard]] int getTileX() const { return _x / _tileSize;}
    [[nodiscard]] int getTileY() const { return _y / _tileSize;}

private:
    const int _tileSize = 32;
    int _x;
    int _y;
    Direction _d;
    bool _moveComplete;
};

#endif //SPRITEPOSITION_H
