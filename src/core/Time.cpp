#include "Time.h"
#include <chrono>
#include <stdexcept>
#include <thread>

float Time::currentTime = 0.0f;
float Time::previousTime = 0.0f;
float Time::deltaTime = 0.0f;
float Time::fixedDeltaTime = 1.0f / 60.0f;  // Default to 60 FPS
float Time::timeScale = 1.0f;
float Time::accumulatedTime = 0.0f;
float Time::maxDeltaTime = 0.25f;  // Default to 250ms max frame time
float Time::alpha = 1.0f;
bool Time::initialized = false;
float Time::targetFrameRate = 60.0f;
float Time::frameTimeTarget = 1.0f / 60.0f;
float Time::actualFrameRate = 0.0f;
float Time::frameCounter = 0.0f;
float Time::lastFpsUpdateTime = 0.0f;

void Time::Init() {

    const auto now = std::chrono::high_resolution_clock::now();
    const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(
        now.time_since_epoch()).count();

    currentTime = static_cast<float>(nanoseconds) / 1e9f;
    previousTime = currentTime;
    deltaTime = 0.0f;
    accumulatedTime = 0.0f;
    lastFpsUpdateTime = currentTime;
    initialized = true;
}

void Time::Update() {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }

    const auto now = std::chrono::high_resolution_clock::now();
    const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(
        now.time_since_epoch()).count();

    currentTime = static_cast<float>(nanoseconds) / 1e9f;

    deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    deltaTime *= timeScale;

    deltaTime = std::min(deltaTime, maxDeltaTime);
    accumulatedTime += deltaTime;
    alpha = accumulatedTime / fixedDeltaTime;

    frameCounter++;

    if (currentTime - lastFpsUpdateTime >= 1.0f) {
        actualFrameRate = frameCounter / (currentTime - lastFpsUpdateTime);
        frameCounter = 0;
        lastFpsUpdateTime = currentTime;
    }
}

void Time::Simulate(void (*simulateFunc)(float)) {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }

    while (accumulatedTime >= fixedDeltaTime) {
        simulateFunc(fixedDeltaTime);
        accumulatedTime -= fixedDeltaTime;
    }

    alpha = accumulatedTime / fixedDeltaTime;
}

void Time::LimitFrameRate() {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }

    const float frameEnd = previousTime + frameTimeTarget;

    const auto now = std::chrono::high_resolution_clock::now();
    const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(
        now.time_since_epoch()).count();

    float currentTimeNow = static_cast<float>(nanoseconds) / 1e9f;

    if (currentTimeNow < frameEnd) {
        float sleepTime = frameEnd - currentTimeNow;
        std::this_thread::sleep_for(std::chrono::microseconds(
            static_cast<int>(sleepTime * 1000000)));
    }
}

float Time::GetDeltaTime() {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    return deltaTime;
}

float Time::GetFixedDeltaTime() {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    return fixedDeltaTime;
}

float Time::GetAccumulatedTime() {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    return accumulatedTime;
}

float Time::GetTimeScale() {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    return timeScale;
}

float Time::GetCurrentTime() {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    return currentTime;
}

float Time::GetAlpha() {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    return alpha;
}

float Time::GetTargetFrameRate() {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    return targetFrameRate;
}

float Time::GetActualFrameRate() {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    return actualFrameRate;
}

void Time::SetFixedDeltaTime(float dt) {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    fixedDeltaTime = dt;
}

void Time::SetTimeScale(float scale) {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    timeScale = scale;
}

void Time::SetMaxDeltaTime(float maxDt) {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    maxDeltaTime = maxDt;
}

void Time::SetTargetFrameRate(float fps) {
    if (!initialized) {
        throw std::runtime_error("Time system not initialized. Call Time::Init() first.");
    }
    targetFrameRate = fps;
    frameTimeTarget = 1.0f / fps;
}