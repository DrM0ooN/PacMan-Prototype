# PacMan Prototype

A Pac-Man clone written in C, rendered entirely in the console using ANSI escape codes. Old university/personal project, uploaded here years after it was written.

## How it works

- `main.c` is the entry point and pulls in the other modules directly (`opts.c`, `maze.c`, `levels.c`, `area.c`) as a single-translation-unit build.
- `maze.c` generates and manages the maze layout.
- `levels.c` handles level progression.
- `area.c` is the largest module: game area/screen rendering, Pac-Man and ghost movement, input handling, and the play/pause/game-over state machine.
- `opts.c` holds game configuration and settings.
- Console rendering and input are handled through [rlutil](https://github.com/tapio/rlutil) (`rlutil.h`), a small single-header cross-platform console utility library by Tapio Vierros, used here under its WTFPL license. Vendored directly in this repo since it's a single header.

## Building

Requires only a C compiler.

**Linux/macOS:**
```bash
gcc main.c -o pacman
./pacman
```

**Windows (Code::Blocks):**
Open `PacMan.cbp` in [Code::Blocks](https://www.codeblocks.org/) and build/run (GCC toolchain).

## Status

This was a prototype/learning project, not actively maintained. It compiles and runs, but expect rough edges - some in-progress debug output is still visible during play in a few states.
