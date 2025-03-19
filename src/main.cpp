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

Player* player = nullptr;
std::shared_ptr<GameWorld> gameWorld;

bool Initialize(SDL_Renderer* renderer) {

    gameWorld = std::make_shared<GameWorld>(renderer);
    DependencyInjection::RegisterSingleton<GameWorld>(gameWorld);

    std::shared_ptr<GameSettings> settings = DependencyInjection::Resolve<GameSettings>();

    if (!settings->Load()) {
        std::cerr << "Failed to load the game settings! Using defaults." << std::endl;
    }

    auto* collisionManager = new CollisionManager(settings);
    gameWorld->SetCollisionManager(collisionManager);

    Time::Init();
    Time::SetTargetFrameRate(60.0f);
    Time::SetFixedDeltaTime(1.0f / 60.0f);

    std::string basePath = SDL_GetBasePath() ? SDL_GetBasePath() : "";

    gameWorld->AddParallaxLayer(new ParallaxLayer(renderer, (basePath + "assets/sprites/parallax/layer1.png").c_str(), -20.0f));
    gameWorld->AddParallaxLayer(new ParallaxLayer(renderer, (basePath + "assets/sprites/parallax/layer2.png").c_str(), -30.0f));

    player = new Player(renderer, (basePath + "assets/sprites/ships/player_ship.png").c_str(), 148, 188, 10, 5, 5, 100, 100);
    player->IncrementRotation(180);

    gameWorld->AddEntity(player);

    if (SDL_Window* window = SDL_GetWindowFromID(1)) {
        SDL_SetWindowSize(window, settings->GetWindowWidth(), settings->GetWindowHeight());
        if (settings->IsFullscreen()) {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
    }

    return true;
}

void Render(SDL_Renderer* renderer){

    SDL_SetRenderDrawColor(renderer, 0, 0, 32, 255);
    SDL_RenderClear(renderer);

    gameWorld->Render(renderer);

    SDL_RenderPresent(renderer);
}

void Update(SDL_Renderer* renderer) {

    Time::Update();

    static float accumulator = 0.0f;
    accumulator += Time::GetDeltaTime();

    while (accumulator >= Time::GetFixedDeltaTime()) {
        gameWorld->Update(Time::GetDeltaTime());
        accumulator -= Time::GetFixedDeltaTime();
    }

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

    gameSettings->Load();

    int screenWidth = gameSettings->GetWindowWidth();
    int screenHeight = gameSettings->GetWindowHeight();

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

    if (gameSettings->IsFullscreen()) {
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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}