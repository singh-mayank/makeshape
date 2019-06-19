# MakeShape

Example using Octree:
```
    makeshape::spatial::Octree oc(4);
    // build
    {
        const auto m = makeshape::spatial::load_cube();
        oc.build(m.const_vertices());
        printf("Octree Nodes: %zu\n", oc.num_nodes());
    }
    // display
    const auto edges = oc.get_edges();
    application.set_edges(edges);
```
![Octree on a model of Cow](https://raw.githubusercontent.com/singh-mayank/makeshape/master/imgs/octree_cow.png)
