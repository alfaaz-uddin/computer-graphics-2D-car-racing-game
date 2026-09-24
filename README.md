# 2D Car Racing Game (OpenGL / C++)

A classic, retro-style 2D top-down car dodging game built using C++ and the OpenGL (GLUT) library. Navigate traffic, avoid collisions, and achieve a high score while experiencing dynamic weather and day/night cycles.

## Features

- **Dynamic Environment:** The game automatically toggles between Day and Night modes every 10 points .
- **Weather Effects:** Players can toggle visual rain effects on and off .
- **Progressive Difficulty:** The game speed increases as your score reaches 10, 20, 30, and 40 .
- **Enemy Variety:** Encounter base cars, colored cars, and police cars that actively steer towards the player's lane .
- **Crash Animation:** Features an expanding explosion animation upon collision .
- **Audio Support:** Includes background music and a game-over sound effect using the Windows Multimedia library .

## Prerequisites

To compile and run this game, you will need:

- A C++ compiler (e.g., GCC/MinGW for Windows).
- The **GLUT / FreeGLUT** library installed and configured.
- Windows OS (due to `<windows.h>` and `<mmsystem.h>` dependencies for audio playback).

## Required Assets

Ensure the following files are placed in the same directory as the compiled executable to prevent missing sound errors:

- `main.cpp` (The core source code).
- `background.wav` (Played during active gameplay).
- `over.wav` (Played when a collision occurs).

_(Note: A `start.wav` is commented out in the source code but can be added if the line is uncommented)._

## Compilation

If you are compiling via the command line with MinGW, use a command similar to this:
`g++ main.cpp -o CarGame.exe -lfreeglut -lopengl32 -lglu32 -lwinmm`

_(The `-lwinmm` flag is required to link the Windows multimedia API for the game's sound functions)._

## How to Play

Launch the compiled executable. You will be greeted by the start screen.

- **SPACEBAR**: Start the game .
- **W / A / S / D** or **Arrow Keys**: Move the player's car Up, Left, Down, and Right.
- **P**: Pause and resume the game.
- **V**: Toggle Rain effects.
- **R**: Restart after a Game Over.
- **X**: Exit the application.

## Gameplay Elements

- **HUD**: The top of the screen displays your current Score, the Time of Day (DAY/NIGHT), and the weather status (RAIN).
- **Scenery**: As you drive, trees, buildings (which feature illuminated windows at night), and streetlights scroll past to simulate movement.
