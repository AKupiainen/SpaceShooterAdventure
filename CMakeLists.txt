# Set SDL2 and SDL2_image paths
set(SDL2_DIR "/opt/homebrew/opt/sdl2/share/cmake/SDL2")
set(SDL2_IMAGE_DIR "/opt/homebrew/Cellar/sdl2_image/2.8.8/share/cmake/SDL2_image")
set(CMAKE_CXX_STANDARD 11)
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
        src/SpriteAnimator.cpp
        src/GameEntity.cpp
        src/Player.cpp
        src/Time.cpp
        src/Time.h
        src/ParallaxLayer.cpp
        src/ParallaxLayer.h
        src/Bullet.cpp
        src/Bullet.h
        src/BulletPath.cpp
        src/BulletPath.h
        src/StraightBulletPath.cpp
        src/StraightBulletPath.h
        src/Shooter.cpp
        src/Shooter.h
)

# Create the executable
add_executable(SDLProject ${SOURCE_FILES})

# Link SDL2 and SDL2_image to the executable
target_link_libraries(SDLProject
        PRIVATE
        ${SDL2_LIBRARIES}
        /opt/homebrew/Cellar/sdl2_image/2.8.8/lib/libSDL2_image.dylib
)

# Post-build command to copy the assets folder to the build directory
add_custom_command(TARGET SDLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
)