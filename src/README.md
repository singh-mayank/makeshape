# MakeShape
```
src/
¦   CMakeLists.txt
¦   README.md
¦
+---app
¦       app.cc
¦       app.hh
¦       CMakeLists.txt
¦
+---common
¦       CMakeLists.txt
¦       common.cc
¦       common.hh
¦
+---icp
¦       CMakeLists.txt
¦       icp.cc
¦       icp.hh
¦
+---shapes
¦       CMakeLists.txt
¦
+---spatial
¦   ¦   aabb.cc
¦   ¦   aabb.hh
¦   ¦   bsphere.cc
¦   ¦   bsphere.hh
¦   ¦   CMakeLists.txt
¦   ¦   edges.hh
¦   ¦   intersections.cc
¦   ¦   intersections.hh
¦   ¦   octree.cc
¦   ¦   octree.hh
¦   ¦   trimesh.cc
¦   ¦   trimesh.hh
¦   ¦
¦   +---unittests
¦           CMakeLists.txt
¦           unittest_octree.cc
¦
+---surface_reconstruction
¦       CMakeLists.txt
¦
+---triangulate
    ¦   CMakeLists.txt
    ¦
    +---dual_contouring
            CMakeLists.txt
            dual_contouring.cc
            dual_contouring.hh

```
### TODO
- [ ] Intersection queries for AABB/AABB, and BSphere/BSphere
- [ ] Ray/Triangle, and Ray/Plane intersection
- [ ] Ray/Plane distance, Point/Triangle closest/distance
- [x] Octree with distance query (neighbours within radius)
    - [x] Octree neighbours - needs unittests
- [ ] Least-Squares Rigid Motion Using SVD
