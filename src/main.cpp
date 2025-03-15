#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "core/Time.h"
#include "player/Player.h"
#include "sprites/ParallaxLayer.h"


void FixedUpdate(Player& player) {
    player.Update();
}

int main(int argc, char* argv[]) {

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    std::string basePath = SDL_GetBasePath() ? SDL_GetBasePath() : "";

    ParallaxLayer layer1(renderer, (basePath + "assets/sprites/parallax/layer1.png").c_str(), -20.0f);
    ParallaxLayer layer2(renderer, (basePath + "assets/sprites/parallax/layer2.png").c_str(), -30.0f);

    Player player(renderer, (basePath + "assets/sprites/ships/player_ship.png").c_str(), 148, 188, 10, 5, 5, 100, 100);
    player.IncrementRotation(180);

    bool running = true;
    SDL_Event e;
    Time::Init();
    Time::SetTargetFrameRate(60.0f);
    Time::SetFixedDeltaTime(1.0f / 60.0f);
    float accumulator = 0.0f;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }

        Time::Update();
        accumulator += Time::GetDeltaTime();

        while (accumulator >= Time::GetFixedDeltaTime()) {
            FixedUpdate(player);
            accumulator -= Time::GetFixedDeltaTime();
        }

        layer1.Update(Time::GetDeltaTime());
        layer2.Update(Time::GetDeltaTime());

        SDL_SetRenderDrawColor(renderer, 0, 0, 32, 255);
        SDL_RenderClear(renderer);

        layer1.Render(renderer);
        layer2.Render(renderer);

        player.Render(renderer);

        SDL_RenderPresent(renderer);
        Time::LimitFrameRate();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}