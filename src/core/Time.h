#ifndef TIME_H
#define TIME_H

class Time {
public:
    static void Init();
    static void Update();
    static void Simulate(void (*simulateFunc)(float));
    static void LimitFrameRate();

    static float GetDeltaTime();
    static float GetFixedDeltaTime();
    static float GetAccumulatedTime();
    static float GetTimeScale();
    static float GetCurrentTime();
    static float GetAlpha();
    static float GetTargetFrameRate();
    static float GetActualFrameRate();

    static void SetFixedDeltaTime(float dt);
    static void SetTimeScale(float scale);
    static void SetMaxDeltaTime(float maxDt);
    static void SetTargetFrameRate(float fps);

private:
    Time() {}

    static float currentTime;       // Current time in seconds
    static float previousTime;      // Time at the previous frame
    static float deltaTime;         // Time elapsed since last frame
    static float fixedDeltaTime;    // Fixed timestep for physics simulation (e.g., 0.01 seconds)
    static float timeScale;         // Allows for time manipulation (slow motion, etc.)
    static float accumulatedTime;   // Accumulated time for fixed timestep updates
    static float maxDeltaTime;      // Maximum allowed deltaTime to prevent spiral of death
    static float alpha;             // Interpolation factor between physics steps
    static bool initialized;        // Whether the time system has been initialized
    static float targetFrameRate;   // Target frame rate (in FPS)
    static float frameTimeTarget;   // Target time per frame (in seconds)
    static float actualFrameRate;   // Actual measured frame rate
    static float frameCounter;      // Counter for frames in the current second
    static float lastFpsUpdateTime; // Time of last FPS update calculation
};

#endif