# Falling Sand Simulation
A real-time falling sand simulation written in C using SDL2.  
This project demonstrates particle-based simulation expandable C code.

## Features

- Real-time falling sand simulation on a 2D grid
- Interactive simulation using mouse input
- Modular C code separating simulation logic and input/rendering
- Uses SDL2 for rendering

---

## Requirements

- C compiler (clang or gcc)
- [SDL2](https://www.libsdl.org/) development libraries installed
- [CMake](https://cmake.org/) 3.20 or higher

## Build instructions
1. Create a build directory and navigate into it:  
   ```bash
   mkdir -p build
   cd build
   ```  
2. Generate build files with CMake:  
   ```bash
   cmake ..
   ```  
3. Build the project:  
   ```bash
   cmake --build .
   ```
4. Run the simulation:  
   ```bash
   ./FallingSand
   ```

   ---

## About the Project
The Falling Sand Simulation runs on a 2D grid where each cell represents a grain of sand or empty space. 
Sand falls naturally according to simple physics rules: it moves down if the space below is empty, 
or diagonally downward if there is free space to the side. Grains stack on top of each other, 
allowing realistic piling and flow effects. The simulation updates in real-time and allows the user 
to place sand interactively using the mouse.

The code is modular, with separate files handling the simulation logic, grid management, and 
rendering/input through SDL2.

## Future improvements
- Add more realistic physics behaviors (e.g., friction, spreading)
- Optimize simulation performance for larger grids
- Implement additional interaction tools (erase, move)
- Optionally add other grain types in the future
   
   
