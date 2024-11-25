add_subdirectory(imgui)

add_library(Display display.hpp display.cpp)
target_link_libraries(Display imgui)
