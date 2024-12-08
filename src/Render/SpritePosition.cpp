//
// Created by ralex on 12/4/2024.
//

#include "SpritePosition.h"

#include <SDL_log.h>

void SpritePosition::update(DirectionHelper::Direction d, float elapsedTime) {
    _d = d;
    _moveComplete = false;
    switch(d)
    {
        case DirectionHelper::Direction::Left: _x -= static_cast<int>(_tileSize * elapsedTime); break;
        case DirectionHelper::Direction::Right: _x += static_cast<int>(_tileSize * elapsedTime); break;
        case DirectionHelper::Direction::Up: _y -= static_cast<int>(_tileSize * elapsedTime); break;
        case DirectionHelper::Direction::Down: _y += static_cast<int>(_tileSize * elapsedTime); break;
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

    if(_d == DirectionHelper::Direction::Left) {
        int d = _x % _tileSize;
        if(step > d) {
            _x -= d;
        } else {
          _x -= step;
        }
    } else if(_d == DirectionHelper::Direction::Right) {
        int d = _x % _tileSize;
        if(step > d) {
            _x += d;
        } else {
            _x += step;
        }
    } else if(_d == DirectionHelper::Direction::Up) {
        int d = _y % _tileSize;
        if(step > d) {
            _y -= d;
        } else {
            _y -= step;
        }
    } else if(_d == DirectionHelper::Direction::Down) {
        int d = _y % _tileSize;
        if(step > d) {
            _y += d;
        } else {
            _y += step;
        }
    }
}