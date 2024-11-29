cmake_minimum_required(VERSION 3.14)
project(chemu8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_SDL=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
    find_package(SDL2 REQUIRED)
endif()

set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_BUILD_TYPE DEBUG)

add_subdirectory(src/emu)
add_subdirectory(src/display)

add_executable(chemu8 src/main.cpp)

target_link_libraries(chemu8 SDL2 Emu Display)
target_include_directories(chemu8 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/memory"
                          )
