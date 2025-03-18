#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "core/Time.h"
#include "player/Player.h"
#include "sprites/ParallaxLayer.h"
#include "core/CollisionManager.h"
#include "core/DependencyInjection.h"
#include "core/GameSettings.h"
#include "core/GameWorld.h"

std::shared_ptr<CollisionManager> collisionManager = nullptr;
std::shared_ptr<GameWorld> gameWorld = nullptr;

bool Initialize(SDL_Renderer* renderer) {
    std::shared_ptr<GameSettings> settings = DependencyInjection::Resolve<GameSettings>();
    if (!settings->Load()) {
        std::cerr << "Failed to load the game settings! Using defaults." << std::endl;
    }

    collisionManager = std::make_shared<CollisionManager>(settings);
    DependencyInjection::RegisterSingleton<CollisionManager>(collisionManager);

    // Create and register GameWorld
    gameWorld = std::make_shared<GameWorld>();
    DependencyInjection::RegisterSingleton<GameWorld>(gameWorld);

    Time::Init();
    Time::SetTargetFrameRate(60.0f);
    Time::SetFixedDeltaTime(1.0f / 60.0f);

    std::string basePath = SDL_GetBasePath() ? SDL_GetBasePath() : "";

    ParallaxLayer* layer1 = new ParallaxLayer(renderer, (basePath + "assets/sprites/parallax/layer1.png").c_str(), -20.0f);
    ParallaxLayer* layer2 = new ParallaxLayer(renderer, (basePath + "assets/sprites/parallax/layer2.png").c_str(), -30.0f);

    gameWorld->AddParallaxLayer(layer1);
    gameWorld->AddParallaxLayer(layer2);

    Player* player = new Player(renderer, (basePath + "assets/sprites/ships/player_ship.png").c_str(), 148, 188, 10, 5, 5, 100, 100);
    player->IncrementRotation(180);

    std::unique_ptr<GameEntity> playerEntity(player);
    gameWorld->AddEntity(std::move(playerEntity));

    Player* playerPtr = static_cast<Player*>(gameWorld->getEntities().back().get());

    collisionManager->AddEntity(playerPtr);

    if (SDL_Window* window = SDL_GetWindowFromID(1)) {
        SDL_SetWindowSize(window, settings->GetWindowWidth(), settings->GetWindowHeight());
        if (settings->IsFullscreen()) {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
    }

    return true;
}

void FixedUpdate() {

    collisionManager->CheckCollisions();
}

void Render(SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 32, 255);
    SDL_RenderClear(renderer);

    gameWorld->Render(renderer);
    collisionManager->DrawCollisionBoxes(renderer);

    SDL_RenderPresent(renderer);
}

void Update(SDL_Renderer* renderer) {
    Time::Update();

    static float accumulator = 0.0f;
    accumulator += Time::GetDeltaTime();

    while (accumulator >= Time::GetFixedDeltaTime()) {
        FixedUpdate();
        accumulator -= Time::GetFixedDeltaTime();
    }

    gameWorld->Update(Time::GetDeltaTime());
    Render(renderer);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::string configPath = SDL_GetBasePath() ? std::string(SDL_GetBasePath()) + "config/config.ini" : "config/config.ini";
    std::shared_ptr<GameSettings> gameSettings = std::make_shared<GameSettings>(configPath);
    DependencyInjection::RegisterSingleton<GameSettings>(gameSettings);

    std::shared_ptr<GameSettings> settings = DependencyInjection::Resolve<GameSettings>();
    settings->Load();

    int screenWidth = settings->GetWindowWidth();
    int screenHeight = settings->GetWindowHeight();

    SDL_Window* window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                         screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    if (settings->IsFullscreen()) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    Initialize(renderer);

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }

        Update(renderer);
        Time::LimitFrameRate();
    }

    SpriteAnimator::ClearTextureCache();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}