# CMakeSemVerExample

A small example of adding [semantic versioning](https://semver.org/) to a C++ library using CMake and git tags.

This repo goes with a blog post. Each commit is one step in the life of a toy library called **superAwesome**, so you can step through the history and see what changes as versioning is introduced and the library evolves.

## Contents

| Path | Description |
| --- | --- |
| `CMakeLists.txt` | Top-level project that adds `superAwesome/` and `demo/` so both build together. |
| `superAwesome/` | Standalone CMake project for the `superAwesomeLibrary` static library. Installs as the `superAwesome` CMake package. |
| `superAwesome/include/superAwesome/` | Public header (`rd::SuperAwesomeFunction()`). |
| `superAwesome/src/` | Library sources. |
| `demo/` | Standalone CMake project for `demo`, a small executable that uses the library through `find_package(superAwesome)`. |

The demo links to `superAwesome::superAwesomeLibrary`, the same target name a downstream user gets from `find_package(superAwesome)`. The library defines this name as an alias of its own target, so the demo links to it the same way whether the library is built in the same tree or installed.

## How to push a new tag

```sh
git tag -a v0.1.0 -m "superAwesome 0.1.0"
git push origin v0.1.0
```

## Commit history

Each commit captures the library at a specific point:

1. **Before versioning.** A plain CMake library and demo, with no version information.
2. **v0.1.0: Semantic versioning added.** The version comes from a git tag and is exposed to C++ code. The demo checks the library version at runtime.
3. **v0.2.0: Breaking change.** A function signature changes. Consumers can use `#if` on the `SUPER_AWESOME_VERSION` macro to support both the old and new API.
4. **v1.0.0: Launch.** A very important feature is added, and the library is ready for its 1.0.0 release.

## Building

Requires CMake 3.20 or newer.

### Everything at once

Build the library and demo together from the repo root (or open the folder in Visual Studio):

```bash
cmake -S . -B build
cmake --build build --config Release
```

### Library and demo separately

This is how a real consumer uses the library. First build and install the library:

```bash
cmake -S superAwesome -B build/superAwesome
cmake --build build/superAwesome --config Release
cmake --install build/superAwesome --config Release --prefix build/install
```

Then build the demo against the install by pointing `CMAKE_PREFIX_PATH` at it. Use an absolute path, because CMake does not resolve a relative prefix path from your current directory:

```bash
cmake -S demo -B build/demo -DCMAKE_PREFIX_PATH="$PWD/build/install"
cmake --build build/demo --config Release
```

The demo cannot be configured on its own until the library is installed. Without an install, `find_package(superAwesome)` finds nothing, so the `superAwesome::superAwesomeLibrary` target does not exist.

Any other downstream project can use the installed library the same way:

```cmake
find_package(superAwesome REQUIRED)
target_link_libraries(myApp PRIVATE superAwesome::superAwesomeLibrary)
```
