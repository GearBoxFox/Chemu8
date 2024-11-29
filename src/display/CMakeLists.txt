add_library(Display display.hpp display.cpp)
find_package(SDL2 REQUIRED)
target_link_libraries(Display SDL2::SDL2 SDL2_ttf)
