#include "DependencyInjection.h"

std::unordered_map<std::type_index, std::function<std::shared_ptr<void>(void)>> DependencyInjection::factories;
