# MakeShape

Utilities for 3d shape manipulation.

## Implements:

#### Papers
* [ Least-Squares Rigid Motion Using SVD, by Olga Sorkine-Hornung and Michael Rabinovich ](https://igl.ethz.ch/projects/ARAP/svd_rot.pdf)
* [ Dual Marching Cubes: Primal Contouring of Dual Grids ](https://www.cs.rice.edu/~jwarren/papers/dmc.pdf)
  * [ Manifold Contouring of an Adaptively Sampled Distance Field ](http://publications.lib.chalmers.se/records/fulltext/123811.pdf)
* 
 
#### Algorithms:
* Octree for neighbourhood queries.
* [Marching Cubes](https://dl.acm.org/citation.cfm?id=37422) (borrowed as-is via Paul Bourke, available at http://paulbourke.net/geometry/polygonise/).
* Intersections: AABB/BSphere, AABB/AABB, BSphere/BSphere, Ray/Plane, Ray/Triangle.

## Compile

Compile this project using the standard cmake routine:
```
    mkdir builds
    cd builds
    cmake ..
    make
```
This should find and build the dependencies and create a `makeshape` binary.

## Run

From within the `build` directory just issue:
```
    ./bin/makeshape
```
A glfw app should launch displaying a 3D cube,  or
```
    ./bin/makeshape ./data/bunny.obj
```

## Dependencies

The only dependencies are stl, eigen, [libigl](http://libigl.github.io/libigl/) and the 
dependencies of the `igl::opengl::glfw::Viewer`.

Clone, and build `libigl` like so:
```
    git clone https://github.com/libigl/libigl.git
    cd libigl/
    git submodule update --init --recursive
    mkdir builds
    cd builds
    cmake ..
    make
```
If you have installed libigl at `/path/to/libigl/` then a good place to clone this library 
is `/path/to/makeshape/`.

## Recommendation
We recommend using `ninja` instead of `make`. Download install `ninja` from here [
https://ninja-build.org/ ]
