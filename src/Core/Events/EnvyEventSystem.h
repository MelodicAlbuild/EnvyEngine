//
// Created by ralex on 12/7/2024.
//

#ifndef ENVYEVENTSYSTEM_H
#define ENVYEVENTSYSTEM_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include <mutex>
#include <algorithm>

// Templated Singleton Event System
class EnvyEventSystem {
public:
    static EnvyEventSystem& getInstance();
    template <typename... Args>
    void addEventListener(const std::string& eventName, std::function<void(Args...)> callback);
    template <typename... Args>
    void removeEventListener(const std::string& eventName, std::function<void(Args...)> callback);
    template <typename... Args>
    void dispatchEvent(const std::string& eventName, Args... args);
    EnvyEventSystem(const EnvyEventSystem&) = delete;
    EnvyEventSystem& operator=(const EnvyEventSystem&) = delete;

private:
    EnvyEventSystem() = default;
    ~EnvyEventSystem() = default;
    std::unordered_map<std::string, std::vector<std::function<void()>>> listeners;
    mutable std::mutex mtx;
};

#endif //ENVYEVENTSYSTEM_H
