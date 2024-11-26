add_library(Emu cpu.hpp cpu.cpp memory.hpp memory.cpp)
target_link_libraries(Emu SDL2 SDL2main)