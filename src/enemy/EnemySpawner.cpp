#include "EnemySpawner.h"
#include "../helpers/IniReader.h"
#include <iostream>
#include "../core/DependencyInjection.h"
#include "../core/GameWorld.h"

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

    if (!iniReader.LoadFile(iniFile)) {
        std::cerr << "Failed to load enemy waves config" << std::endl;
        return;
    }

    std::vector<std::string> waveSections = iniReader.GetArray("Waves", "waveTypes");

    for (const std::string& waveSection : waveSections) {
        EnemyWave wave;
        wave.enemyType = iniReader.GetString(waveSection, "enemyType", "defaultEnemy");
        wave.count = iniReader.GetInt(waveSection, "count", 5);
        wave.spawnDelay = iniReader.GetFloat(waveSection, "spawnDelay", 1.0f);
        wave.formation = iniReader.GetString(waveSection, "formation", "line");

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
        SpawnEnemiesInFormation(wave);
    }
}

void EnemySpawner::SpawnEnemiesInFormation(const EnemyWave& wave) {
    int screenWidth = 800;
    int screenHeight = 600;
    int spawnY = -50;

    if (const EnemyConfig::EnemyData* enemyData = enemyConfig.GetEnemyData(wave.enemyType)) {
        if (wave.formation == "grid") {
            SpawnEnemiesInGrid(wave, *enemyData, screenWidth, spawnY);
        } else if (wave.formation == "pyramid") {
            SpawnEnemiesInPyramid(wave, *enemyData, screenWidth, spawnY);
        } else if (wave.formation == "circle") {
            SpawnEnemiesInCircle(wave, *enemyData, screenWidth, spawnY);
        } else if (wave.formation == "line") {
            SpawnEnemiesInLine(wave, *enemyData, screenWidth, spawnY);
        }
    }
}

void EnemySpawner::SpawnEnemiesInGrid(const EnemyWave& wave, const EnemyConfig::EnemyData& enemyData, int screenWidth, int spawnY) {
    int cols = std::ceil(std::sqrt(wave.count));
    int rows = std::ceil(static_cast<float>(wave.count) / cols);
    int startX = (screenWidth - (cols * enemyData.frameWidth)) / 2;

    for (int i = 0; i < wave.count; ++i) {
        int row = i / cols;
        int col = i % cols;
        int x = startX + col * enemyData.frameWidth;
        int y = spawnY + row * enemyData.frameHeight;

        SpawnEnemy(x, y, enemyData);
    }
}

void EnemySpawner::SpawnEnemiesInPyramid(const EnemyWave& wave, const EnemyConfig::EnemyData& enemyData, int screenWidth, int spawnY) {
    int baseSize = std::ceil(std::sqrt(2 * wave.count));
    int startX = (screenWidth - (baseSize * enemyData.frameWidth)) / 2;

    int index = 0;
    for (int row = 0; row < baseSize; ++row) {
        int numInRow = baseSize - row;
        int rowX = startX + (row * enemyData.frameWidth / 2);
        int rowY = spawnY + (row * enemyData.frameHeight);

        for (int j = 0; j < numInRow && index < wave.count; ++j, ++index) {
            SpawnEnemy(rowX + j * enemyData.frameWidth, rowY, enemyData);
        }
    }
}

void EnemySpawner::SpawnEnemiesInCircle(const EnemyWave& wave, const EnemyConfig::EnemyData& enemyData, int screenWidth, int spawnY) {
    int radius = 100;
    int centerX = screenWidth / 2;
    int centerY = spawnY - radius;

    for (int i = 0; i < wave.count; ++i) {
        float angle = (2.0f * M_PI * i) / wave.count;
        int x = centerX + radius * std::cos(angle);
        int y = centerY + radius * std::sin(angle);

        SpawnEnemy(x, y, enemyData);
    }
}

void EnemySpawner::SpawnEnemiesInLine(const EnemyWave& wave, const EnemyConfig::EnemyData& enemyData, int screenWidth, int spawnY) {
    int startX = (screenWidth - (wave.count * enemyData.frameWidth)) / 2;
    for (int i = 0; i < wave.count; ++i) {
        int x = startX + i * enemyData.frameWidth;
        SpawnEnemy(x, spawnY, enemyData);
    }
}

void EnemySpawner::SpawnEnemy(int x, int y, const EnemyConfig::EnemyData& enemyData) {
    std::string basePath = SDL_GetBasePath() ? SDL_GetBasePath() : "";
    std::string spritePath = basePath + enemyData.spriteSheetPath;

    Enemy* newEnemy = new Enemy(renderer, spritePath.c_str(), enemyData.frameWidth,
                                enemyData.frameHeight, enemyData.frameDelay, enemyData.rows,
                                enemyData.columns, x, y, enemyData.speedX, enemyData.speedY);

    auto gameWorld = DependencyInjection::Resolve<GameWorld>();

    if (!gameWorld) {
        std::cerr << "Error: GameWorld not found in DependencyInjection!" << std::endl;
        return;
    }

    gameWorld->AddEntity(newEnemy);
}
