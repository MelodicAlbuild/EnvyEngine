//
// Created by ralex on 12/7/2024.
//

#ifndef DIRECTIONHELPER_H
#define DIRECTIONHELPER_H

class DirectionHelper {
  public:
    enum Direction { Left, Right, Up, Down, None };

    static Direction computeFromBooleans(bool left, bool right, bool up, bool down);
};

#endif //DIRECTIONHELPER_H
