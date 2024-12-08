#ifndef SPRITE_H
#define SPRITE_H

#include "EnvyRenderer.h"
#include "SpritePosition.h"
#include "../Core/Events/EnvyEventListener.h"

class Sprite : public EnvyEventListener
{
public:
  Sprite();
  SpritePosition position;

  void onDraw(EnvyRenderer *renderer);
  void onMoveUpdate(DirectionHelper::Direction dir);

private:
  float speed = 0.05f;
};

#endif // SPRITE_H
