cmake_minimum_required(VERSION 3.30)

project(Tetris)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif()

if(${CMAKE_BUILD_TYPE} MATCHES "Debug") 
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -O0 -g2")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(RAYLIB_PATH ".")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)



add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/Textures.cpp
    src/Game.cpp
    src/Tetramino.cpp
    src/Field.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC -lstatic-raylib -L"${RAYLIB_PATH}")
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
