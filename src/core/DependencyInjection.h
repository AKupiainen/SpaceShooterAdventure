#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>

class DependencyInjection {
public:
    template <typename T>
    static void Register(std::function<std::shared_ptr<T>()> factory) {
        auto typeIndex = std::type_index(typeid(T));
        factories[typeIndex] = [factory](void) -> std::shared_ptr<void> {
            return factory();
        };
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
};
