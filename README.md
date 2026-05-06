# Mariner

## Requirements

- clang++ with C++23 support
- CMake 3.21+
- Git
- macOS

## Build

```sh
make
```

This will clone and build all dependencies (bgfx, bimg, bx, GLFW) into `libraries/.build` and `libraries/.install`, then compile and bundle the app to `build/MarinerClient.app`.

Dependencies are only built once. Re-running `make` skips them if already built.

## Options

| Variable | Default | Description |
|---|---|---|
| `JOBS` | `32` | Parallel job count |
| `CMAKE_BUILD_TYPE` | `Release` | CMake build type |
| `ASAN` | `1` | Enable AddressSanitizer |

```sh
make ASAN=0 JOBS=8
```

## Clean

```sh
make clean        # removes build/
make clean-deps   # removes built and installed dependencies
```
