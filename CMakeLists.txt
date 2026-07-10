cmake_minimum_required(VERSION 3.16)
project(SubSub)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML
set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/include")
set(SFML_LIB_DIR "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/lib")

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

# SDL2 + SDL2_mixer
find_package(SDL2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
)

add_executable(SubSub main.cpp)

target_link_libraries(SubSub
        sfml-graphics
        sfml-window
        sfml-system

        ${SDL2_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
)