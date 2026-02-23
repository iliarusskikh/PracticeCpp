#!/usr/bin/env bash
set -euo pipefail
# Run script for this small project: compile src/main.cpp and run build/main
ROOT="$(cd "$(dirname "$0")" && pwd)"
mkdir -p "$ROOT/build"
echo "Compiling src/main.cpp -> build/main"
g++ -std=c++20 -I "$ROOT/include" -g "$ROOT/src/main.cpp" -o "$ROOT/build/main"
echo "Running build/main"
"$ROOT/build/main"
