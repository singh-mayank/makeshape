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
¦   ¦   CMakeLists.txt
¦   ¦   least_sq_rigid_motion.cc
¦   ¦   least_sq_rigid_motion.hh
¦   ¦
¦   +---unittests
¦           CMakeLists.txt
¦           unittest_least_sq.cc
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
    ¦       CMakeLists.txt
    ¦       dual_contouring.cc
    ¦       dual_contouring.hh
    ¦
    +---marching_cubes
            CMakeLists.txt
            marching_cubes.cc
            marching_cubes.hh

```
