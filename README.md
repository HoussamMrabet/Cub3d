# cub3D - Raycasting Engine with miniLibX

Welcome to the **cub3D** project repository, a raycasting engine inspired by the legendary **Wolfenstein 3D**. This project introduces you to the fascinating world of raycasting and 3D rendering in C, while utilizing **miniLibX** for graphics rendering. It simulates the first-person view of a maze and allows users to navigate through it in real-time.

In addition to the core raycasting features, this implementation includes several exciting **bonus features**, such as dynamic lighting, sky rendering, sprite animations, and a user-friendly menu. The game also supports multiple platforms, with dedicated scripts for **macOS** and **Linux** to generate the proper Makefile.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Bonus Features](#bonus-features)
- [Building and Running Bonus Features](#building-and-running-bonus-features)

---

## Features

- **Raycasting Engine**: Real-time 3D rendering of a maze using raycasting techniques.
- **Navigation**: Move through the maze in a first-person perspective with intuitive controls.
- **Dynamic Lighting**: Simulate light sources and shadows for a more immersive experience.
- **Sky Rendering**: Optionally render the sky above the maze to create a realistic environment.
- **Sprite Animations**: Animated sprites for opening doors and additional dynamic elements.
- **User Interface**: A menu to enable/disable sky rendering, access a gameplay guide, and control game options.
- **Cross-Platform Support**: Makefile generation scripts for both **macOS** and **Linux**.
- **Minimap**: A small map showing your current position in the maze.
- **Wall Textures**: Different textures for walls based on direction (North, South, East, West).
- **Floor and Ceiling Colors**: Customizable floor and ceiling colors.

---

## Installation

To run the cub3D game on your machine, follow these installation steps:

### macOS Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/HoussamMrabet/cub3D.git
   cd cub3D
   ```

2. Run the macOS Makefile script to generate the appropriate Makefile:
   ```bash
   ./macos_makefile.sh
   ```

3. Build the project:
   ```bash
   make
   ```

### Linux Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/HoussamMrabet/cub3D.git
   cd cub3D
   ```

2. Run the Linux Makefile script to generate the appropriate Makefile:
   ```bash
   ./linux_makefile.sh
   ```

3. Build the project:
   ```bash
   make
   ```

---

## Usage

1. After building the project, you can run the game with a **.cub** map file as the first argument. For example:
   ```bash
   ./cub3D ./mandatory/maps/map.cub
   ```

2. You can create your own **.cub** map files or use the ones provided in the `maps/` directory.

---

## Bonus Features

In addition to the core functionality, the following **bonus features** have been added:

- **Dynamic Lighting**: Lights affect the way walls and objects appear based on your position and orientation.
- **Sky Rendering**: An optional sky is rendered above the maze, adding to the visual appeal of the game.
- **Sprite Animation**: Doors in the maze open and close with animated sprites.
- **User Interface/Menu**: The game includes a menu where you can toggle the sky, view a gameplay guide, and exit or resume the game.
- **Minimap**: A minimap displays your position within the maze for easier navigation.

---

### Building and Running Bonus Features

If you'd like to compile the project **with bonus features** (such as dynamic lighting, sky rendering, sprite animations, etc.), follow the steps below:

#### 1. **Compiling the Project with Bonus Features**

To compile the project including the bonus features, use the `bonus` rule in the Makefile.

- **macOS/Linux**:
   ```bash
   make bonus
   ```

This will compile and link all the necessary code for both the mandatory and bonus features.

#### 2. **Running the Game with Bonus Features**

Once compiled with the bonus features, you can run the game as usual, and the bonus features will be enabled by default.

```bash
./cub3D_bonus ./bonus/maps/map.cub
```

---

By using the `make bonus` rule, you'll be able to experience the game with all the additional features that enhance gameplay.

Thank you for exploring cub3D! If you have any questions or encounter any issues, feel free to open an issue or contact me directly. Happy coding!
