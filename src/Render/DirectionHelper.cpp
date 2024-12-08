//
// Created by ralex on 12/7/2024.
//

#include "DirectionHelper.h"

DirectionHelper::Direction DirectionHelper::computeFromBooleans(bool left, bool right, bool up, bool down) {
    if(left && right && up && down) {
        return DirectionHelper::Direction::None;
    }

    if(left && !right) {
        return DirectionHelper::Direction::Left;
    } else if(right && !left) {
        return DirectionHelper::Direction::Right;
    } else if(up && !down) {
        return DirectionHelper::Direction::Up;
    }else if(down && !up) {
        return DirectionHelper::Direction::Down;
    }

    return DirectionHelper::Direction::None;
}