#ifndef ENVYEVENT_H
#define ENVYEVENT_H

#include <functional>
#include <vector>
#include <mutex>

#include "EventBase.h"
#include <SDL_log.h>

template <typename... Args>
class EnvyEvent : public EventBase
{
public:
    using HandlerType = std::function<void(Args...)>;

    void subscribe(const HandlerType &handler)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _handlers.push_back(handler);
    }

    void unsubscribe(const HandlerType &handler)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _handlers.erase(std::remove(_handlers.begin(), _handlers.end(), handler), _handlers.end());
    }

    void notify(Args... args)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        for (const auto &handler : _handlers)
        {
            handler(args...);
        }
    }

private:
    std::vector<HandlerType> _handlers;
    std::mutex _mutex;
};
;

#endif // ENVYEVENT_H