#include "DependencyInjection.h"

std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>> DependencyInjection::factories;
std::unordered_map<std::type_index, std::shared_ptr<void>> DependencyInjection::instances;