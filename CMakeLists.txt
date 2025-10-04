cmake_minimum_required(VERSION 3.10)

# Projektname
project(SubSub)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Finde SFML (Grafik, Fenster, System, Audio, Netzwerk falls nötig)
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Quelle hinzufügen (hier nur main.cpp)
add_executable(SubSub main.cpp)

# SFML Bibliotheken linken
target_link_libraries(SubSub sfml-graphics sfml-window sfml-system sfml-audio)
