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
    std::vector<Enemy*> GetSpawnedEnemies();

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
    std::vector<Enemy*> activeEnemies;
    int currentWave;
    float spawnTimer;

    void SpawnEnemy(const EnemyWave& wave);
};

#endif