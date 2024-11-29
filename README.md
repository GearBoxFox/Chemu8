# Chemu8
## A Toy Chip-8 Emulator compiled for the web!

CHIP-8 was an high-level interpreted computer language orignally developed for the COSMAC-VIP in 1977. It was then imported into a variety of other 
systems, and eventually become SUPER-CHIP. Because of it's similarity to assembly running on actual hardware, using hexadecimal opcodes and registers,
it is often used as the "Hello, world" of emulator development. You can read more about CHIP-8 and it's history on [Wikipedia](https://en.wikipedia.org/wiki/CHIP-8).

Chemu8 can either be built and run locally, or played on the web on [my Github Pages](gearboxfox.github.io/chemu8). The web version comes bundles with 7 different ROM files to play with.

## ROM Files Included
1. IBM Logo - A common testing ROM.
2. Octojam Title Screen - A common animation test, the title screen for Octojam, a CHIP-8 game jam.
3. Pong
4. Lights Out
5. 15 Puzzle
6. Connect 4
7. Tic Tac Toe

## Building
1. Clone the repository with `git clone https://github.com/gearboxfox/chemu8.git`
2. Install the SDL2 and SDL2_ttf with `sudo apt-get install libsdl2-dev libsdl2-ttf-dev`
3. Move into the build folder and run the build script `cd build && make`
