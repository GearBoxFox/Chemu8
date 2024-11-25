cmake_minimum_required(VERSION 3.14)
project(chemu8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_BUILD_TYPE DEBUG)

add_subdirectory(src/emu)
add_subdirectory(src/display)

set(ROOT ./imgui)

add_library(imgui STATIC
	${ROOT}/imgui.cpp
	${ROOT}/imgui.h
	${ROOT}/imstb_rectpack.h
	${ROOT}/imstb_textedit.h
	${ROOT}/imstb_truetype.h
    ${ROOT}/imgui_demo.cpp
    ${ROOT}/imgui_draw.cpp
    ${ROOT}/imgui_internal.h
    ${ROOT}/imgui_tables.cpp
    ${ROOT}/imgui_widgets.cpp
)

add_executable(chemu8 src/main.cpp)

target_link_libraries(chemu8 SDL2main SDL2 Emu Display)
target_include_directories(chemu8 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/memory"
                          )
