# MakeShape

Example using KDTree:
```
    makeshape::spatial::KDTree ktree(8);
    ktree.build(pts);
    const auto edges = ktree.get_edges();
    application.set_edges(edges);
```
![KDTree on a model of Bunny](https://raw.githubusercontent.com/singh-mayank/makeshape/master/imgs/kdtree_bunny.png)
