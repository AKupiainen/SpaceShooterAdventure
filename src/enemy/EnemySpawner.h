#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <vector>
#include <string>
#include "Enemy.h"
#include "EnemyConfig.h"

class EnemySpawner {
public:
    EnemySpawner(SDL_Renderer* renderer);

    void LoadWaves(const std::string& iniFile);
    void Update(float deltaTime);
    void SpawnEnemiesForWave();

private:
    struct EnemyWave {
        std::string enemyType;
        int count;
        float spawnDelay;
        std::string formation;
    };

    SDL_Renderer* renderer;
    EnemyConfig enemyConfig;
    std::vector<EnemyWave> waves;
    int currentWave;
    float spawnTimer;

    void SpawnEnemiesInFormation(const EnemyWave& wave);
    void SpawnEnemiesInGrid(const EnemyWave& wave, const EnemyConfig::EnemyData& enemyData, int screenWidth);
    void SpawnEnemiesInPyramid(const EnemyWave& wave, const EnemyConfig::EnemyData& enemyData, int screenWidth);
    void SpawnEnemiesInCircle(const EnemyWave& wave, const EnemyConfig::EnemyData& enemyData, int screenWidth);
    void SpawnEnemiesInLine(const EnemyWave& wave, const EnemyConfig::EnemyData& enemyData, int screenWidth);
    void SpawnEnemy(int x, int y, const EnemyConfig::EnemyData& enemyData);
};

#endif