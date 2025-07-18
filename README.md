# Snake Game (C++ with raylib)

A simple Snake game written in C++ using the raylib graphics library.

## Features
- Real-time movement and collision logic
- Food spawning with image assets
- Game over detection (out of bounds & self-collision)
- Object-oriented structure (Snake, Food, Game classes)

## Requirements
- [raylib](https://www.raylib.com/)
- C++17

## To Run
```bash
g++ main.cpp -o snake -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./snake
