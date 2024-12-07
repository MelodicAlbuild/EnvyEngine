//
// Created by ralex on 12/7/2024.
//

#include "EnvyEventSystem.h"

EnvyEventSystem& EnvyEventSystem::getInstance() {
    static EnvyEventSystem instance;
    return instance;
}

template <typename... Args>
void EnvyEventSystem::addEventListener(const std::string& eventName, std::function<void(Args...)> callback) {
    std::lock_guard<std::mutex> lock(mtx);

    auto wrapper = [callback](Args... args) {
        callback(args...);
    };

    listeners[eventName].emplace_back([wrapper](Args... args) { wrapper(args...); });
}

template <typename... Args>
void EnvyEventSystem::removeEventListener(const std::string& eventName, std::function<void(Args...)> callback) {
    std::lock_guard<std::mutex> lock(mtx);

    auto it = listeners.find(eventName);
    if (it != listeners.end()) {
        auto& callbacks = it->second;
        std::erase_if(callbacks, [&callback](const std::function<void()>& existingCallback) {
            return callback.target_type() == existingCallback.target_type();
        });

        if (callbacks.empty()) {
            listeners.erase(it);
        }
    }
}

template <typename... Args>
void EnvyEventSystem::dispatchEvent(const std::string& eventName, Args... args) {
    std::vector<std::function<void(Args...)>> snapshot;

    {
        std::lock_guard<std::mutex> lock(mtx);
        if (listeners.find(eventName) != listeners.end()) {
            for (const auto& genericCallback : listeners[eventName]) {
                snapshot.emplace_back([genericCallback](Args... args) {
                    genericCallback(args...);
                });
            }
        }
    }

    for (const auto& callback : snapshot) {
        callback(args...);
    }
}