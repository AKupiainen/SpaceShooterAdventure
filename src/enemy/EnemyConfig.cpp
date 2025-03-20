#include "EnemyConfig.h"
#include <iostream>
#include <ostream>
#include "../helpers/IniReader.h"

EnemyConfig::EnemyConfig() {}

EnemyConfig::~EnemyConfig() {}

bool EnemyConfig::LoadConfig(const std::string& iniFile) {
    IniReader iniReader;
    if (!iniReader.LoadFile(iniFile)) {
        std::cerr << "Failed to load enemy config" << std::endl;
        return false;
    }

    std::vector<std::string> enemyTypes = iniReader.GetArray("Enemies", "types");

    for (const std::string& enemyType : enemyTypes) {
        EnemyData data;

        data.spriteSheetPath = iniReader.GetString(enemyType, "spriteSheetPath", "");
        data.frameWidth = iniReader.GetInt(enemyType, "frameWidth", 32);
        data.frameHeight = iniReader.GetInt(enemyType, "frameHeight", 32);
        data.frameDelay = iniReader.GetInt(enemyType, "frameDelay", 100);
        data.rows = iniReader.GetInt(enemyType, "rows", 1);
        data.columns = iniReader.GetInt(enemyType, "columns", 1);
        data.speedX = iniReader.GetFloat(enemyType, "speedX", 0.0f);
        data.speedY = iniReader.GetFloat(enemyType, "speedY", 0.0f);

        enemyDataMap[enemyType] = data;
    }

    return true;
}

const EnemyConfig::EnemyData* EnemyConfig::GetEnemyData(const std::string& enemyType) const {
    const auto it = enemyDataMap.find(enemyType);
    if (it != enemyDataMap.end()) {
        return &it->second;
    }
    return nullptr;
}