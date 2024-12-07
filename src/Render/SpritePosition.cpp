//
// Created by ralex on 12/4/2024.
//

#include "SpritePosition.h"

#include <SDL_log.h>

SpritePosition::Direction SpritePosition::computeFromBooleans(bool left, bool right, bool up, bool down) {
  if(left && right && up && down) {
    return SpritePosition::Direction::None;
  }

  if(left && !right) {
    return SpritePosition::Direction::Left;
  } else if(right && !left) {
    return SpritePosition::Direction::Right;
  } else if(up && !down) {
    return SpritePosition::Direction::Up;
  }else if(down && !up) {
    return SpritePosition::Direction::Down;
  }

  return SpritePosition::Direction::None;
}

void SpritePosition::update(Direction d, float elapsedTime) {
    _d = d;
    _moveComplete = false;
    switch(d)
    {
        case Left: _x -= static_cast<int>(_tileSize * elapsedTime); break;
        case Right: _x += static_cast<int>(_tileSize * elapsedTime); break;
        case Up: _y -= static_cast<int>(_tileSize * elapsedTime); break;
        case Down: _y += static_cast<int>(_tileSize * elapsedTime); break;
        default: break;
    }
}

void SpritePosition::update(float elapsedTime) {
    if((_x % _tileSize) == 0 && (_y % _tileSize) == 0) {
        _moveComplete = true;
        return;
    }

    _moveComplete = false;

    int step = static_cast<int>(_tileSize * elapsedTime);

    if(_d == Left) {
        int d = _x % _tileSize;
        if(step > d) {
            _x -= d;
        } else {
          _x -= step;
        }
    } else if(_d == Right) {
        int d = _x % _tileSize;
        if(step > d) {
            _x += d;
        } else {
            _x += step;
        }
    } else if(_d == Up) {
        int d = _y % _tileSize;
        if(step > d) {
            _y -= d;
        } else {
            _y -= step;
        }
    } else if(_d == Down) {
        int d = _y % _tileSize;
        if(step > d) {
            _y += d;
        } else {
            _y += step;
        }
    }
}