# 2D Car Racing Game (OpenGL / C++)

A classic, retro-style 2D top-down car dodging game built using C++ and the OpenGL (GLUT) library. Navigate traffic, avoid collisions, and achieve a high score while experiencing dynamic weather and day/night cycles.

## Features

- **Dynamic Environment:** The game automatically toggles between Day and Night modes every 10 points[cite: 1].
- **Weather Effects:** Players can toggle visual rain effects on and off[cite: 1].
- **Progressive Difficulty:** The game speed increases as your score reaches 10, 20, 30, and 40[cite: 1].
- **Enemy Variety:** Encounter base cars, colored cars, and police cars that actively steer towards the player's lane[cite: 1].
- **Crash Animation:** Features an expanding explosion animation upon collision[cite: 1].
- **Audio Support:** Includes background music and a game-over sound effect using the Windows Multimedia library[cite: 1].

## Prerequisites

To compile and run this game, you will need:

- A C++ compiler (e.g., GCC/MinGW for Windows).
- The **GLUT / FreeGLUT** library installed and configured.
- Windows OS (due to `<windows.h>` and `<mmsystem.h>` dependencies for audio playback)[cite: 1].

## Required Assets

Ensure the following files are placed in the same directory as the compiled executable to prevent missing sound errors:

- `main.cpp` (The core source code)[cite: 1].
- `background.wav` (Played during active gameplay)[cite: 1].
- `over.wav` (Played when a collision occurs)[cite: 1].

_(Note: A `start.wav` is commented out in the source code but can be added if the line is uncommented)[cite: 1]._

## Compilation

If you are compiling via the command line with MinGW, use a command similar to this:
`g++ main.cpp -o CarGame.exe -lfreeglut -lopengl32 -lglu32 -lwinmm`

_(The `-lwinmm` flag is required to link the Windows multimedia API for the game's sound functions)[cite: 1]._

## How to Play

Launch the compiled executable. You will be greeted by the start screen.

- **SPACEBAR**: Start the game[cite: 1].
- **W / A / S / D** or **Arrow Keys**: Move the player's car Up, Left, Down, and Right[cite: 1].
- **P**: Pause and resume the game[cite: 1].
- **V**: Toggle Rain effects[cite: 1].
- **R**: Restart after a Game Over[cite: 1].
- **X**: Exit the application[cite: 1].

## Gameplay Elements

- **HUD**: The top of the screen displays your current Score, the Time of Day (DAY/NIGHT), and the weather status (RAIN)[cite: 1].
- **Scenery**: As you drive, trees, buildings (which feature illuminated windows at night), and streetlights scroll past to simulate movement[cite: 1].
