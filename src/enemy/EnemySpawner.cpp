#include "EnemySpawner.h"
#include "../helpers/IniReader.h"
#include <iostream>

EnemySpawner::EnemySpawner(SDL_Renderer* renderer)
    : renderer(renderer), currentWave(0), spawnTimer(0.0f) {

    std::string basePath = SDL_GetBasePath() ? SDL_GetBasePath() : "";
    std::string iniFile = basePath + "config/enemy_wave_config.ini";
    std::string enemyConfigFile = basePath + "config/enemy_config.ini";

    enemyConfig.LoadConfig(enemyConfigFile);
    LoadWaves(iniFile);
}

void EnemySpawner::LoadWaves(const std::string& iniFile) {

    IniReader iniReader;

    if (!iniReader.loadFile(iniFile)) {
        std::cerr << "Failed to load enemy waves config" << std::endl;
        return;
    }

    // Load enemy waves
    std::vector<std::string> waveSections = iniReader.getArray("Waves", "waveTypes");

    for (const std::string& waveSection : waveSections) {
        EnemyWave wave;
        wave.enemyType = iniReader.getString(waveSection, "enemyType", "defaultEnemy");
        wave.count = iniReader.getInt(waveSection, "count", 5);
        wave.spawnDelay = iniReader.getFloat(waveSection, "spawnDelay", 1.0f);
        wave.formation = iniReader.getString(waveSection, "formation", "defaultFormation");

        waves.push_back(wave);
    }
}

void EnemySpawner::Update(float deltaTime) {
    if (currentWave < waves.size()) {
        spawnTimer += deltaTime;

        if (spawnTimer >= waves[currentWave].spawnDelay) {
            SpawnEnemiesForWave();
            spawnTimer = 0.0f;
            currentWave++;
        }
    }
}

void EnemySpawner::SpawnEnemiesForWave() {
    if (currentWave < waves.size()) {
        const EnemyWave& wave = waves[currentWave];

        for (int i = 0; i < wave.count; ++i) {
            SpawnEnemy(wave);
        }
    }
}

void EnemySpawner::SpawnEnemy(const EnemyWave& wave) {
    if (const EnemyConfig::EnemyData* enemyData = enemyConfig.GetEnemyData(wave.enemyType)) {
        // Example spawn position, you can modify this based on the formation
        int x = rand() % 800;  // Random X position
        int y = rand() % 600;  // Random Y position

        Enemy* newEnemy = new Enemy(renderer, enemyData->spriteSheetPath, enemyData->frameWidth,
                                     enemyData->frameHeight, enemyData->frameDelay, enemyData->rows,
                                     enemyData->columns, x, y, enemyData->speedX, enemyData->speedY);

        activeEnemies.push_back(newEnemy);
    }
}

std::vector<Enemy*> EnemySpawner::GetSpawnedEnemies() {
    return activeEnemies;
}
