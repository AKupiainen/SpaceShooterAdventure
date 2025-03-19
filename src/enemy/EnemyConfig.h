#ifndef ENEMYCONFIG_H
#define ENEMYCONFIG_H

#include <string>
#include <unordered_map>

class EnemyConfig {
public:
    struct EnemyData {
        std::string spriteSheetPath;
        int frameWidth;
        int frameHeight;
        int frameDelay;
        int rows;
        int columns;
        float speedX;
        float speedY;
    };

    EnemyConfig();
    ~EnemyConfig();

    bool LoadConfig(const std::string& iniFile);
    const EnemyData* GetEnemyData(const std::string& enemyType) const;

private:
    std::unordered_map<std::string, EnemyData> enemyDataMap;
};

#endif
