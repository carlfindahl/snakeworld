# Snakeworld

This is a simple snake game implemented in C and Raylib

![Snake Game](https://i.imgur.com/pSLK2Rh.png)

## Installation

To run the game, follow these steps:

1. Clone the repository
2. Navigate to the project directory: `cd snakeworld`
3. Compile the game with CMake
4. Run the game: `./snakeworld`

## Gameplay

The objective of the game is to control the snake and eat as much food as possible without colliding with the walls or the snake's own body. The snake grows longer each time it eats food.

Use the arrow keys to control the snake's movement: `up`, `down`, `left`, and `right`. Use the `R` key to toggle post processing, and exit at any time with the `Escape` key.

## Files

### main.c

This file contains the main function that initializes the game and handles user input.

### game.c

**Data Structures:** Defines structures for Wall and GameData to manage game elements like walls, the snake, score, and game state.

**Global Variables:** Uses a static GameData pointer to hold the game's state across different functions.

**Initialization and Cleanup:** Implements game_init and game_uninit functions to allocate resources at the start and clean up at the end, respectively.

#### Game Loop Functions:

 - `game_update` handles game logic updates such as input processing, snake movement, wall and food interactions, and game state transitions (e.g., game over).
 - `game_draw` is responsible for rendering the game state to the screen, including the snake, walls, food, score, and other UI elements.
 
#### Utility Functions: 

Includes functions like `spawn_wall` for adding new wall elements to the game.

### snake.c

This file implements the core functionalities of a snake in a classic snake game. It includes the initialization of the snake, updating its state during the game, handling damage, and managing the snake's length. The file utilizes several external resources such as snake.h for the snake structure definition, game_math.h for mathematical operations, message_queue.h for event handling, and raylib.h for graphical rendering.

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request. Especially any suggestions to improve or write more idiomatic C. My main design struggles revlove around the use of internally linked `static` variables that I expose. I did this to avoid allocating each scene dynamically, although this does mean I can't have multiple main menus. But since I designed the game so that this invariant should never happen I also think it's fine given the size.
