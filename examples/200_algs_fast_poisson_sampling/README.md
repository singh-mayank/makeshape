# MakeShape
## Fast Poisson Sampling

Point on a planar quad sized [0.0, 1.0], with the following parameters `samples = 30, distance_between_samples = 0.04`
```
    const auto sampled_pts = makeshape::algs::sample_points_on_plane(dist_bet_samples, n_samples);
```
![Plot of points](https://raw.githubusercontent.com/singh-mayank/makeshape/master/imgs/poisson_sampling_planar.png)
