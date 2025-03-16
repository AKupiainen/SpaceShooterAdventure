#include <memory>
#include <unordered_map>
#include <functional>
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
    
    // Convenience method for registering a singleton
    template <typename T>
    static void RegisterSingleton(std::function<std::shared_ptr<T>()> factory) {
        Register<T>(factory, true);
    }

    template <typename T>
    static std::shared_ptr<T> Resolve() {
        auto typeIndex = std::type_index(typeid(T));
        if (factories.find(typeIndex) != factories.end()) {
            const auto factory = factories[typeIndex];
            return std::static_pointer_cast<T>(factory());
        }
        return nullptr;
    }

private:
    static std::unordered_map<std::type_index, std::function<std::shared_ptr<void>(void)>> factories;
    static std::unordered_map<std::type_index, std::shared_ptr<void>> instances;
};