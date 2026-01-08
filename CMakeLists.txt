cmake_minimum_required(VERSION 3.20)
project(FallingSand C)

# Generera compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Standard C-version
set(CMAKE_C_STANDARD 11)

# Include directories
include_directories(include)

# Hitta SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


# Källfiler
file(GLOB SOURCES src/*.c)

# Skapa executable
add_executable(FallingSand ${SOURCES})

# Länka SDL2
target_link_libraries(FallingSand ${SDL2_LIBRARIES})
