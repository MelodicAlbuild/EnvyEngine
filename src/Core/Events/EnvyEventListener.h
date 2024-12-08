#ifndef ENVYEVENTLISTENER_H
#define ENVYEVENTLISTENER_H

#include "EnvyEventManager.h"

class EnvyEventListener
{
public:
    template <typename EventType, typename... Args>
    void subscribe(const std::function<void(Args...)> &handler)
    {
        EnvyEventManager::getInstance().getEvent<EventType>().subscribe(handler);
    }

    template <typename EventType, typename... Args>
    void unsubscribe(const std::function<void(Args...)> &handler)
    {
        EnvyEventManager::getInstance().getEvent<EventType>().unsubscribe(handler);
    }
};

#endif // ENVYEVENTLISTENER_H