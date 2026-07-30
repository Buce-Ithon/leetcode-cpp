# Project description
This repository is designed to manage and compile **leetcode** experiments and exercises using **CMake**. It supports a hybrid development environment of both **C** and **C++** (C11 and C++20 standards). 

## Key Features
* **Modular Library Architecture**: Common data structure implementations (located in `src/common/`) are automatically built into a static library (`alg_lib`), separating reusable core logic from individual chapter experiments.
* **Auto-Scanning Build System**: You do not need to manually edit `CMakeLists.txt` when adding new exercise files under `src/0*/` or `src/1*/`. Any `.c` or `.cpp` file in the chapter directories is automatically detected, compiled, and linked against `alg_lib`.
* **Conflict-Free Target Naming**: Executable target names are automatically prefixed with their directory names (e.g., `src/01/lc0001.cpp` becomes `01_lc0001`), preventing name collisions across different chapters.
* **CMake Presets Support**: Fully integrated with `CMakePresets.json` to simplify configuring and building across different toolchains (Ninja, MinGW, and MSVC).
* **Robust Code Quality**: Features strict compiler warning flags (for both GCC/Clang and MSVC) to help catch common pointer, memory management, and type-mismatch bugs early.
* **Editor/LSP Integration**: Automatically generates and syncs `compile_commands.json` to the project root for precise code completion and diagnostics when using language servers like `clangd` in Vim/Neovim/Emacs or VS Code.

## Project Structure
```text
leetcode-cpp/
├── CMakeLists.txt         # Core build configuration
├── CMakePresets.json      # Pre-configured build/configure environments
├── .gitignore             # Git ignore rules
├── LICENSE                # Project license
├── README.md              # Project documentation
├── ref                    # Reference materials, lecture notes, or PDFs
├── include                # Public header files (.h / .hpp)
│   └── ...
└── src/                   # Source files organized by common implementations and categories
    ├── common             # # Common custom algorithm implementations (compiled into alg_lib)
    │   └── ...
	└── 01_dp              # Exercises about dynamic programming
        └── ...
```

# Build commands
This project utilizes CMake Presets, so you can configure and build the project using the simplified preset names without manually specifying generators or build directories.

## Prerequisites
Make sure you have CMake (3.15+) and at least one of the following toolchains installed and added to your system PATH:

- Ninja + LLVM/Clang (Recommended for the fastest build speeds and excellent clangd compatibility)

- MinGW (GCC)

- MSVC (Visual Studio 2022)

## Building with Ninja (Recommended)
Debug Mode (with debugging symbols):

```Bash
# Configure the project (generates compile_commands.json in the build directory)
cmake --preset ninja-debug

# Build all targets
cmake --build --preset ninja-debug
```

Release Mode (optimized):

```Bash
cmake --preset ninja-release
cmake --build --preset ninja-release
```

## Building with MinGW Makefiles
Debug Mode:

```Bash
cmake --preset mingw-debug
cmake --build --preset mingw-debug
```

Release Mode:

```Bash
cmake --preset mingw-release
cmake --build --preset mingw-release
```

## Building with Visual Studio (MSVC)
Since MSVC is a multi-configuration generator, configuration is done once, and the build type is determined at the build step:

```Bash
# Configure the project
cmake --preset msvc

# Build Debug version
cmake --build --preset msvc-debug

# Build Release version
cmake --build --preset msvc-release
```

## Compiling & Running a Specific Exercise
To avoid rebuilding the entire project, you can compile a single target (the filename without the extension) by using the `--target` flag.

*Note: Target names are automatically formatted as <chapter>_<filename> (e.g., src/01/lc0001.cpp -> 01_lc0001).*

```bash
# Example: Compile only 'ch2_link_list_test'
cmake --build --preset ninja-debug --target 01_lc0001

# Run the compiled executable (Ninja Debug build path example)
./build/ninja/debug/01_lc0001.exe
```
