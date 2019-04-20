# MakeShape

Generated a triangle mesh from a set of points in space.

## Compile

Compile this project using the standard cmake routine:
```
    mkdir build
    cd build
    cmake ..
    make
```
This should find and build the dependencies and create a `makeshape` binary.

## Run

From within the `build` directory just issue:
```
    ./makeshape
```
A glfw app should launch displaying a 3D cube.

## Dependencies

The only dependencies are stl, eigen, [libigl](http://libigl.github.io/libigl/) and
the dependencies of the `igl::opengl::glfw::Viewer`.

We recommend you to install libigl using git via:
```
    git clone https://github.com/libigl/libigl.git
    cd libigl/
    git submodule update --init --recursive
    cd ..
```
If you have installed libigl at `/path/to/libigl/` then a good place to clone
this library is `/path/to/makeshape/`.
