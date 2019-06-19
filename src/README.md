# MakeShape
```
src/
├── app
│   ├── app.cc
│   ├── app.hh
│   └── CMakeLists.txt
├── CMakeLists.txt
├── common
│   ├── CMakeLists.txt
│   ├── common.cc
│   └── common.hh
├── icp
│   ├── CMakeLists.txt
│   ├── icp.cc
│   └── icp.hh
├── README.md
├── shapes
│   └── CMakeLists.txt
├── spatial
│   ├── aabb.cc
│   ├── aabb.hh
│   ├── CMakeLists.txt
│   ├── edges.hh
│   ├── octree.cc
│   ├── octree.hh
│   ├── trimesh.cc
│   ├── trimesh.hh
│   └── unittests
│       ├── CMakeLists.txt
│       └── unittest_octree.cc
├── surface_reconstruction
│   └── CMakeLists.txt
└── triangulate
    ├── CMakeLists.txt
    └── dual_contouring
        ├── CMakeLists.txt
        ├── dual_contouring.cc
        └── dual_contouring.hh
```
### TODO
- [ ] Intersection queries for AABB/AABB, and BSphere/BSphere
- [ ] Ray/Triangle, and Ray/Plane intersection
- [ ] Ray/Plane distance, Point/Triangle closest/distance
- [x] Octree with distance query (neighbours within radius)
    - [ ] Octree neighbours - needs unittests
- [ ] Unittest for Octree distance query
- [ ] Least-Squares Rigid Motion Using SVD
