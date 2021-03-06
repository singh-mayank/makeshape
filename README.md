# MakeShape

Utilities for 3d shape manipulation.

## Implements:

#### Associated publications:
- [x] [ Least-Squares Rigid Motion Using SVD, by Olga Sorkine-Hornung and Michael Rabinovich ](https://igl.ethz.ch/projects/ARAP/svd_rot.pdf)
- [ ] [ Dual Marching Cubes: Primal Contouring of Dual Grids ](https://www.cs.rice.edu/~jwarren/papers/dmc.pdf)
  - [ ] [ Manifold Contouring of an Adaptively Sampled Distance Field ](http://publications.lib.chalmers.se/records/fulltext/123811.pdf)
- [x] [ A Spatial Data Structure for Fast Poisson-Disk Sample Generation ](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.78.3366&rep=rep1&type=pdf)
  - [x] [ Fast Poisson Disk Sampling in Arbitrary Dimensions ](https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf)
- [ ] Surface Reconstruction
  - [ ] Poisson
  - [ ] Wavelets
  - [ ] [ PolyFit: Polygonal Surface Reconstruction from Point Clouds ](https://3d.bk.tudelft.nl/liangliang/publications/2017/polyfit/polyfit.html)
 
#### Algorithms:
- [x] [Octree](https://en.wikipedia.org/wiki/Octree) (search points in a radius `r`)
- [x] [KDtree](https://www.ri.cmu.edu/pub_files/pub1/moore_andrew_1991_1/moore_andrew_1991_1.pdf) (search nearest neighbour to point `p`)
  - [ ] Revisit kdtree with [a better implementation](http://cmp.felk.cvut.cz/ftp/articles/kybic/Kybic-CAK-2010-40.pdf) 
- [x] [Marching Cubes](https://dl.acm.org/citation.cfm?id=37422) (borrowed as-is via Paul Bourke, available at http://paulbourke.net/geometry/polygonise/).
- [ ] Intersections: 
  - [ ] AABB/BSphere
  - [ ] AABB/AABB, 
  - [ ] BSphere/BSphere, 
  - [ ] Ray/Plane, 
  - [ ] Ray/Triangle.
- [ ] Minimum distance between point and triangle
- [ ] Point cloud (explicit) to signed distance field (implicit)

#### ToDo:
- [x] Visualize KDTree
- [ ] Visualize distance field on regular grid

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
