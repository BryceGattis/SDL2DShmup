# SDL2DShmup
A basic 2D shoot 'em up style game made with SDL.

This version of the game is fully playable. There are no UI elements, but the stage resets after ~2 seconds after death.

## Controls

Arrow keys: Move Player

Spacebar: Fire

## TODO

- Scoring
- Main Menu

## Dependencies

[SDL 2](https://github.com/libsdl-org/SDL/tree/SDL2
[CMake](https://cmake.org)

## Building

To generate the build system for your current platform run:
`cmake . -D CMAKE_PREFIX_PATH=<PATH TO SDL2 install>`

To generate the .exe run:
`cmake --build .`

Lastly to run the executable, from the root directory run:
`./Debug/SDL2DShmup.exe`


## Notes

For the .exe to launch on Windows as is, you need to copy the SDL `SDL2.dll` file to the build folder containing the
`SDLTest.exe` file prior to executing the `.exe`.

## Resources

The game's graphical assets are from the [Kenny Asset Packs](https://kenney.nl/assets). Specifically I'm using:

- [Kenny Space Shooter Extension](https://kenney.nl/assets/space-shooter-extension)
- [Kenny Space Shooter Redux](https://kenney.nl/assets/space-shooter-redux)
