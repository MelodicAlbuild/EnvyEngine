#ifndef SPRITEMOVEEVENT_H
#define SPRITEMOVEEVENT_H

#include "../EnvyEvent.h"

template <typename... Args>
class SpriteMoveEvent : public EnvyEvent<Args...>
{
public:
    virtual ~SpriteMoveEvent() = default;
};

#endif // SPRITEMOVEEVENT_H