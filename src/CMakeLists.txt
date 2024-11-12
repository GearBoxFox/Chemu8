cmake_minimum_required(VERSION 3.14)
project(chemu8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_BUILD_TYPE DEBUG)

add_subdirectory(emu)

add_executable(chemu8 main.cpp)

target_link_libraries(chemu8 SDL2main SDL2 Emu)
target_include_directories(chemu8 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/memory"
                          )
