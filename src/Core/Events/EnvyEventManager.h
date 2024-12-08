#ifndef ENVYEVENTMANAGER_H
#define ENVYEVENTMANAGER_H

#include <map>
#include <memory>
#include <mutex>
#include <typeindex>
#include "EnvyEvent.h"
#include "EventBase.h"

class EnvyEventManager
{
public:
    static EnvyEventManager &getInstance()
    {
        static EnvyEventManager instance;
        return instance;
    }

    template <typename EventType>
    EventType &getEvent()
    {
        std::lock_guard lock(_mutex);
        auto it = _events.find(std::type_index(typeid(EventType)));
        if (it == _events.end())
        {
            auto event = std::make_unique<EventType>();
            _events[std::type_index(typeid(EventType))] = std::move(event);
            return *static_cast<EventType *>(_events[std::type_index(typeid(EventType))].get());
        }
        return *static_cast<EventType *>(it->second.get());
    }

private:
    EnvyEventManager() = default;
    ~EnvyEventManager() = default;

    EnvyEventManager(const EnvyEventManager &) = delete;
    EnvyEventManager &operator=(const EnvyEventManager &) = delete;

    std::map<std::type_index, std::unique_ptr<EventBase>> _events;
    std::mutex _mutex;
};

#endif // ENVYEVENTMANAGER_H