// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"
#include "fast_poisson_sampling.hh"

//
// launch application
// 
int main(int argc, char *argv[])
{
    
    //constexpr double DISTANCE_BETWEEN_SAMPLES = 0.01;
    //constexpr int N_SAMPLES = 30;

    constexpr double DISTANCE_BETWEEN_SAMPLES = 0.1;
    constexpr int N_SAMPLES = 30    ;

    const auto sampled_pts = makeshape::algs::sample_plane(DISTANCE_BETWEEN_SAMPLES, N_SAMPLES);
    printf("Fast Poisson Sampling. Computed [ %zu ] samples\n", sampled_pts.size());

	{
		std::ofstream myfile;
		myfile.open("example.csv");
		for (const auto &each : sampled_pts) {
			myfile << each.x() << "," << each.y() << "\n";
		}
		myfile.close();
	}



    //makeshape::app::App application;
    //application.launch();

    return 0;
}
