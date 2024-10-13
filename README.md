# Accelerine

WIP game.

## Building

### On Linux

1. Install SDL2. Follow [this link](https://wiki.libsdl.org/SDL2/Installation) for specifics.

2. Run the following commands:

```sh
git clone https://github.com/Antonn114/Accelerine.git .
cd ./Accelerine
make
```

## Running

### On Linux

After building the binary, the binary is stored in `bin`. As of October 13th 2024, the game assets are stored inside of a different directory outside of `bin`, so according to the code, you can only run the game while in the base directory of the repo. Please follow the following commands:

1. Give permissions to execute the game
```sh
chmod +x ./bin/Accelerine
```
2. Run the binary
```sh
./bin/Accelerine
# OR
make run
```

## Third-party libraries:
- [SDL2](https://www.libsdl.org/) for user input, window
- [HandmadeMath](https://github.com/HandmadeMath/HandmadeMath) for math with matrices
- [stb](https://github.com/nothings/stb) for images loading