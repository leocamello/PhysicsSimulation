# PhysicsSimulation

A simple physics simulation project using C++, OpenGL, and GLUT.

## Dependencies

This project requires the following dependencies:

*   **CMake:** (Version 3.11 or higher) For building the project.
*   **C++ Compiler:** A compiler supporting C++17 (e.g., GCC, Clang).
*   **OpenGL/GLU/GLUT:** Libraries for graphics rendering.
*   **Doxygen:** (Optional) For generating documentation.
*   **Graphviz:** (Optional, for Doxygen) For generating diagrams.

## Setup (Linux - Debian/Ubuntu based)

1.  **Install Build Tools and Libraries:**
    ```bash
    sudo apt update
    sudo apt install build-essential cmake freeglut3-dev libglu1-mesa-dev libgl1-mesa-dev
    ```

2.  **Install Doxygen and Graphviz (Optional):**
    ```bash
    sudo apt install doxygen graphviz
    ```

## Building the Project

1.  **Clone the repository (if you haven't already):**
    ```bash
    git clone <your-repository-url>
    cd PhysicsSimulation
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Run CMake:**
    ```bash
    cmake ..
    ```

4.  **Compile the project:**
    ```bash
    make
    ```
    The executable `PhysicsSimulation` will be created in the `build` directory.

## Running

Navigate to the build directory and run the executable:

```bash
cd /path/to/PhysicsSimulation/build
./PhysicsSimulation
```

## Documentation (Optional)

If you have Doxygen installed and configured the `Doxyfile` (run `doxygen -g` in the `docs` directory and configure it first):

1.  **Generate documentation using the CMake target (if configured):**
    ```bash
    cd build
    make doc
    ```
    The documentation will be generated (typically in `build/docs/html`).

2.  **Alternatively, run Doxygen manually:**
    ```bash
    cd docs
    doxygen Doxyfile
    ```
    Open `docs/html/index.html` in your browser.

## Running Tests

Google Test is fetched and built automatically by CMake.

1.  **Build the project (if not already done):**
    ```bash
    cd build
    make
    ```

2.  **Run tests using CTest:**
    ```bash
    ctest
    ```
    Or:
    ```bash
    make test
    ```
