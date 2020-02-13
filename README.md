# Pathfinding Visualizer


## Dependencies

- OpenGL `sudo apt-get install freeglut3 freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev on Ubuntu`
- FreeType2 `libfreetype6-dev on Ubuntu`
- GLAD (included)
- GLFW3 `libglfw3-dev on Ubuntu`
- GLM `libglm-dev on Ubuntu`
- [SimpleGuiEngine](https://github.com/d-kowalik/simple-gui-engine)

## How to compile
1. Build SimpleGuiEngine
2. Copy **libsge.a** to **lib** directory
3. Create a build directory `mkdir build`
4. Enter build directory `cd build`
5.  Run `cmake ..`
6. Run `make`
7. **PathfindingVisualizer** is the resulting file

## Usage
### Keybindings
- D - enter drawing mode
- E - enter erase mode
- \+ - increase board size
- \'-' - decrease board size
- R - reset all drawn walls
- Spacebar - run selected algorithm

## Algorithms available
- Dijkstra
- A* - two versions. The second one has much more aggressive heuristics
- BFS - works exactly the same as Dijkstra
- DFS

