# Quant

Hands-on study material for quantitative development in modern C++. The focus is on the language, systems, and mathematical ideas that show up when building trading systems, pricing engines, and low-latency market infrastructure.

## Layout

```
quant/
├── notes/          Theory: probability, stats, linear algebra, calculus,
│                   stochastic processes, derivatives, optimisation, algorithms
├── cpp/            C++ language practice
│   ├── fundamentals/   Core mechanics (RAII, move/copy, refs, OOP, …)
│   ├── idioms/         Templates, lambdas, allocation, I/O tricks
│   └── patterns/       Design patterns used in larger codebases
├── networking/     Sockets, HTTP, endianness, and low-latency primitives
│   ├── endianness/
│   ├── http/
│   ├── sockets/
│   ├── low-latency/    Cache lines, SPSC rings, latency measurement
│   └── tools/          Shell helpers and platform notes
└── simd/           Vectorised numeric kernels and benchmarks
```

## Compiling snippets

Most files are standalone. Compile with a recent Clang or GCC:

```bash
clang++ -std=c++20 -O2 -o out path/to/file.cpp
./out
```

For SIMD or architecture-specific work, add `-march=native` (or the relevant `-mavx2` / NEON flags). Some networking examples need platform headers available on macOS/Linux.

## Notes

Open the HTML files under `notes/` in a browser. They use MathJax for equations and cover the quantitative theory side of the material.
