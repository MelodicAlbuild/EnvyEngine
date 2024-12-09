#ifndef SPRITE_H
#define SPRITE_H

#include "EnvyRenderer.h"
#include "SpritePosition.h"
#include "../Objects/Object.h"

#define SPEED 0.05f

class Sprite : public Object
{
public:
  Sprite();

  SpritePosition position;

  void onDraw(EnvyRenderer *renderer);
  void onMoveUpdate(DirectionHelper::Direction dir);
};

#endif // SPRITE_H
