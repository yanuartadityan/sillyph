### SillyPH (Silly Particle Hydrodynamics :duh:)

It's a simple attempt to rewrite my bachelor thesis on C++ on CPU only. Though, I am hoping to optimise it somehow in the future.
Hence, it's a living repo and I will start with very simple things: To make the app works and screw performance!!

<p align="center">
  <img src="./assets/sillyph.png" width="60%">
</p>

### How to build:

Make sure you have both `git` and `cmake` in your environment. I only tested this in Ubuntu 22.04 so your experience may vary on other environments.

1. Clone the repo.
2. Update the submodules `$ git submodule update --init --recursive`.
3. Navigate to the repo and run `$ ./INSTALL_GLAD`.
4. Create a build directory `$ mkdir build && cd build`.
5. Run CMake `$ cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug|Release`. Use *Debug* for debugging and *Release* for optimized binary.
6. Build `$ make`.

### References:

There are already plenty of available source codes online which has more sophisticate optimizations here and there. But I do recommend that you starts from here these two:

* [Mueller SPH][1]
* [Marching Cubes Rendering][2]


[1]: https://matthias-research.github.io/pages/publications/sca03.pdf

[2]: https://en.wikipedia.org/wiki/Marching_cubes