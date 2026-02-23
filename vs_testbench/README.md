# vs_cpp — small C++ project

This repository contains a small C++ example using C++20. The instructions below show the recommended VS Code workflow (open the project root) and a few alternative commands you can run from the terminal.

## Recommended VS Code workflow (project root)

1. Open the folder `vs_cpp` (File → Open Folder) — do not open `src` alone unless you prefer the alternate workflow.
2. Install the following VS Code extensions if you don't have them:
   - C/C++ (ms-vscode.cpptools) — provides the debugger and language features.
   - Code Runner (optional) — convenience to run single-file programs (configured here to use `run.sh`).
3. Build the active source file (uses the workspace `tasks.json`):
   - Press `Cmd+Shift+B` and select `g++: build active file (project)`.
   - The task compiles the active file (for example `src/main.cpp`) with `-I ${workspaceFolder}/include` and places the binary in `build/`.
4. Debug (F5):
   - Open `src/main.cpp` in the editor.
   - Press `F5` and select `Debug build/main` (this configuration always runs `build/main`) or `Debug active file` (runs `build/${fileBasenameNoExtension}`).
   - The preLaunchTask will build before launching the debugger.

## Running with Code Runner (Run Code button)

This repo includes a `run.sh` script and a settings override so the Code Runner extension calls the script when you click "Run Code":

```bash
# from the project root
./run.sh
```

`run.sh` compiles `src/main.cpp` with `-I include` and runs `build/main`. This avoids placeholder-expansion problems when Code Runner tries to substitute `${file}` and `${workspaceFolder}`.

## Terminal commands (manual)

From the project root:

```bash
# compile
g++ -std=c++20 -I include -g src/main.cpp -o build/main

# run
./build/main
```

Or from `src/` (if you prefer):

```bash
# from src
g++ -std=c++20 -I ../include -g main.cpp -o ../build/main
../build/main
```

## CMake

`CMakeLists.txt` is present and configured to use C++20. If you prefer to use CMake, install CMake (e.g. `brew install cmake`) and run from the project root:

```bash
mkdir -p build && cd build
cmake ..
make
./VS_CPP
```

## Files of interest

- `src/main.cpp` — main source file
- `include/header1.hpp` — small header used by `main.cpp`
- `run.sh` — helper script used by Code Runner and for manual convenience
- `.vscode/tasks.json` — tasks used by Cmd+Shift+B (root workspace)
- `.vscode/launch.json` — debugger configurations (F5)
- `src/.vscode/tasks.json` — alternate tasks if you open `src` as the workspace

## Troubleshooting

- "header1.hpp file not found": ensure you opened the project root and that the task or command includes `-I include` (root) or `-I ../include` (if you opened `src`). The repo's root `tasks.json` and `run.sh` already configure the include path correctly.
- If F5 doesn't start the debugger after a successful build, open the Run and Debug view and make sure `Debug build/main` is selected. Also confirm the C/C++ extension is installed.
- If Code Runner shows `clang++: error: no input files`, that means the run command used VS Code placeholders (like `$file`) directly in a terminal — use the Run Code button while the workspace root is open, or run `./run.sh` from the terminal instead.


