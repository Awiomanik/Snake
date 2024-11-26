# Console Snake Game
This project is a console-based Snake game written in C++. It was one of my earliest programming projects, discovered in the depths of my old computer. While it is not a programming marvel, it holds sentimental value as the project that sparked my love for programming and the satisfaction of creating something from scratch.
Now, years later, I have decided to dust it off, refine it slightly, and present it as a nostalgic memoir—a tribute to the beginnings of my coding adventure.

## Description
The Snake game is a classic arcade game where the player controls a snake that grows longer as it eats food. The goal is to collect as much food as possible without colliding with the walls or the snake's own tail.

This version of the Snake game is implemented entirely in a console environment, without a GUI. It showcases basic programming concepts such as:

- Console manipulation for rendering the game board.
- Simple game loop logic.
- Handling user input for controlling the snake.
- Managing dynamic data like the snake's growing length.

**Key Features**:
- Console-based gameplay with keyboard input.
- Growing snake length as it consumes food.
- Game over conditions when the snake collides with itself or the edges.
- High-score tracking for the classic mode.

## Dependencies
This project uses standard C++ libraries and a few Windows-specific features:

- `Windows.h`: For handling console operations and key events.
- `MMSystem.h`: For sound effects (optional).
- `fstream`: For saving and reading high scores.

To compile and run the game, you need a C++ compiler (`G++`) and the `Windows` platform.

## Compilation and Setup
To simplify the setup and compilation process, a build wizard is provided. Run Snake_setup.bat from the main directory to automatically compile and prepare the game:

```bash
Snake_setup.bat
```

### Manual Compilation
If you prefer manual compilation, use the following command (adjust paths as necessary):

```bash
g++ src/*.cpp src/Snake_res.o -o Snake.exe -lwinmm -lgdi32
```

## Running the Game
Once compiled, run the game executable:

```bash
./Snake.exe
```

**Example**
Gameplay Screenshot (Text-based)
```shell
   ########################
   #                      #
   #      Oooooo          #
   #                      #
   #          *           #
   #                      #
   ########################
```
The snake (O) grows as it consumes food (*).
Avoid crashing into walls or the snake's tail.

## Author
Wojciech Kośnik-Kowalczuk ([Email me](wojciech.kosnik.kowalczuk@gmail.com))

## License
This project is licensed under the MIT License (see [LICENSE](LICENSE)).