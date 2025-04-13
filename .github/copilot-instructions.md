# Copilot Instructions for PhysicsSim Project

- The primary language is **Modern C++** (assume C++17 or newer). Prioritize idiomatic C++ features (RAII, smart pointers, STL algorithms, etc.).
- Strictly follow the **Google C++ Style Guide** for all formatting and naming conventions.
- Apply best practices and recommendations from the **C++ Core Guidelines**.
- The build system is **CMake**. Use modern CMake practices (targets, properties, `find_package` where appropriate).
- Documentation is generated using **Doxygen**. Ensure code comments are compatible with Doxygen (`/** ... */` or `///` style).
- Unit tests are written using the **Google Test** framework (GTest/GMock). Assume tests should accompany new or modified logic.
- Graphics rendering relies on **OpenGL**. Focus on core profile features and avoid deprecated functionality unless specifically requested.
- Emphasize code clarity, maintainability, resource safety, and reasonable performance.