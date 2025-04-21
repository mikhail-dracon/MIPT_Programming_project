cmake_minimum_required(VERSION 3.29)
project(MIPT)

set(CMAKE_CXX_STANDARD 17)
set(SFML_INCLUDE_DIR "/usr/include")
set(SFML_LIBRARY_DIR "/usr/lib")


include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})
add_executable(MIPT main.cpp
        Cell.cpp
        Map.cpp
        Texture_List.cpp
        building.cpp
        Building_List.cpp
        Available_Buildings.cpp)

find_package(SFML COMPONENTS System Window Graphics REQUIRED)
target_link_libraries(MIPT sfml-graphics sfml-window sfml-system)
