cmake_minimum_required(VERSION 2.8)

project (Termbot)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(Termbot src/Point.cpp src/Bot.cpp src/Tile.cpp src/RuntimeEnvironment.cpp src/Laboratory.cpp src/main.cpp)