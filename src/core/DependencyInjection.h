#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <typeindex>

class DependencyInjection {
public:
    template <typename T>
    static void Register(std::function<std::shared_ptr<T>()> factory, bool singleton = false) {
        auto typeIndex = std::type_index(typeid(T));

        if (singleton) {

            std::shared_ptr<void> instance = factory();
            factories[typeIndex] = [instance](void) -> std::shared_ptr<void> {
                return instance;
            };
            instances[typeIndex] = instance;
        } else {

            factories[typeIndex] = [factory](void) -> std::shared_ptr<void> {
                return factory();
            };
        }
    }

    template <typename T>
    static void RegisterSingleton(std::shared_ptr<T> instance) {
        auto typeIndex = std::type_index(typeid(T));


        factories[typeIndex] = [instance](void) -> std::shared_ptr<void> {
            return instance;
        };
        instances[typeIndex] = instance;
    }

    template <typename T>
    static std::shared_ptr<T> Resolve() {

        auto typeIndex = std::type_index(typeid(T));
        auto instanceIt = instances.find(typeIndex);

        if (instanceIt != instances.end()) {

            return std::static_pointer_cast<T>(instanceIt->second);
        }

        auto factoryIt = factories.find(typeIndex);

        if (factoryIt != factories.end()) {
            return std::static_pointer_cast<T>(factoryIt->second());
        }

        return nullptr;
    }

private:

    static std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>> factories;
    static std::unordered_map<std::type_index, std::shared_ptr<void>> instances;
};

