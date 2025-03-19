#include "EnemyConfig.h"

#include <iostream>
#include <ostream>

#include "../helpers/IniReader.h"

EnemyConfig::EnemyConfig() {}

EnemyConfig::~EnemyConfig() {}

bool EnemyConfig::LoadConfig(const std::string& iniFile) {
    IniReader iniReader;
    if (!iniReader.loadFile(iniFile)) {
        std::cerr << "Failed to load enemy config" << std::endl;
        return false;
    }

    std::vector<std::string> enemyTypes = iniReader.getArray("Enemies", "types");

    for (const std::string& enemyType : enemyTypes) {
        EnemyData data;

        data.spriteSheetPath = iniReader.getString(enemyType, "spriteSheetPath", "");
        data.frameWidth = iniReader.getInt(enemyType, "frameWidth", 32);
        data.frameHeight = iniReader.getInt(enemyType, "frameHeight", 32);
        data.frameDelay = iniReader.getInt(enemyType, "frameDelay", 100);
        data.rows = iniReader.getInt(enemyType, "rows", 1);
        data.columns = iniReader.getInt(enemyType, "columns", 1);
        data.speedX = iniReader.getFloat(enemyType, "speedX", 0.0f);
        data.speedY = iniReader.getFloat(enemyType, "speedY", 0.0f);

        enemyDataMap[enemyType] = data;
    }

    return true;
}

const EnemyConfig::EnemyData* EnemyConfig::GetEnemyData(const std::string& enemyType) const {
    auto it = enemyDataMap.find(enemyType);
    if (it != enemyDataMap.end()) {
        return &it->second;
    }
    return nullptr;
}