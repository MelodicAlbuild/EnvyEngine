#ifndef DRAWEVENT_H
#define DRAWEVENT_H

#include "../EnvyEvent.h"

template <typename... Args>
class DrawEvent : public EnvyEvent<Args...>
{
public:
    virtual ~DrawEvent() = default;
};

#endif // DRAWEVENT_H