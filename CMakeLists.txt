# Set SDL2 and SDL2_image paths
set(SDL2_DIR "/opt/homebrew/opt/sdl2/share/cmake/SDL2")
set(SDL2_IMAGE_DIR "/opt/homebrew/Cellar/sdl2_image/2.8.8/share/cmake/SDL2_image")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find SDL2 explicitly using the path
find_package(SDL2 REQUIRED PATHS ${SDL2_DIR})

# Include directories for SDL2 and SDL2_image
include_directories(
        ${SDL2_INCLUDE_DIRS}
        /opt/homebrew/Cellar/sdl2_image/2.8.8/include
)

set(SOURCE_FILES
        src/main.cpp
        src/sprites/SpriteAnimator.cpp
        src/core/GameEntity.cpp
        src/player/Player.cpp
        src/core/Time.cpp
        src/core/Time.h
        src/sprites/ParallaxLayer.cpp
        src/sprites/ParallaxLayer.h
        src/shooting/Bullet.cpp
        src/shooting/Bullet.h
        src/shooting/BulletPath.cpp
        src/shooting/BulletPath.h
        src/shooting/StraightBulletPath.cpp
        src/shooting/StraightBulletPath.h
        src/shooting/Shooter.cpp
        src/shooting/Shooter.h
        src/shooting/StraightBulletWeapon.cpp
        src/shooting/StraightBulletWeapon.h
        src/player/EngineFlame.cpp
        src/player/EngineFlame.h
        src/shooting/Weapon.h
        src/shooting/ShotgunWeapon.cpp
        src/shooting/ShotgunWeapon.h
        src/core/CollisionManager.cpp
        src/core/CollisionManager.h
        src/core/DependencyInjection.h
        src/core/DependencyInjection.cpp
        src/helpers/DebugLog.cpp
        src/helpers/DebugLog.h
        src/core/QuadTree.cpp
        src/core/QuadTree.h
        src/core/GameSettings.cpp
        src/core/GameSettings.h
        src/helpers/INIReader.cpp
        src/helpers/INIReader.h
        src/enemy/Enemy.cpp
        src/enemy/Enemy.h
        src/helpers/Tags.cpp
        src/helpers/Tags.h
        src/core/GameWorld.cpp
        src/core/GameWorld.h
        src/enemy/EnemySpawner.cpp
        src/enemy/EnemySpawner.h
        src/enemy/EnemyConfig.cpp
        src/enemy/EnemyConfig.h
)

# Create the executable
add_executable(SDLProject ${SOURCE_FILES})

# Link SDL2 and SDL2_image to the executable
target_link_libraries(SDLProject
        PRIVATE
        ${SDL2_LIBRARIES}
        /opt/homebrew/Cellar/sdl2_image/2.8.8/lib/libSDL2_image.dylib
)

# Post-build command to copy the assets and config files to the build directory
add_custom_command(TARGET SDLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
)

add_custom_command(TARGET SDLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/config/enemy_wave_config.ini
        ${CMAKE_BINARY_DIR}/config/enemy_wave_config.ini
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/config/enemy_config.ini
        ${CMAKE_BINARY_DIR}/config/enemy_config.ini
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/config/config.ini
        ${CMAKE_BINARY_DIR}/config/config.ini
)