// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"
#include "fast_poisson_sampling.hh"

#include <cxxopts.hpp>

//
// launch application
// 
int main(int argc, char *argv[])
{
    cxxopts::Options options("Fast Poisson Sampling example", 
            "Generates a set of random samples on a 2d plane (XY), with bounds [0.0, 1.0]");
    options.add_options()
        ("h,help", "Print help", 
         cxxopts::value<bool>()->default_value("false"))
        ("d,debug", "Enable debugging", 
         cxxopts::value<bool>()->default_value("false"))
        ("n,samples", "Number of samples, defaulted to 30", 
         cxxopts::value<int>()->default_value("30"))
        ("m,dist", "Distance between samples, defaulted to 0.04", 
         cxxopts::value<double>()->default_value("0.04"))
        ("f,output_filename", "Write points to filename", 
         cxxopts::value<std::string>()->default_value(""))
        ;
    const auto result = options.parse(argc, argv);
    // print help
    if (result.count("help")) {
        printf("%s\n", options.help().c_str());
        return 0;
    }
    // compute samples
    const double DISTANCE_BETWEEN_SAMPLES = result["dist"].as<double>();
    const int N_SAMPLES = result["samples"].as<int>();
    printf("Fast Poisson Sampling on 2d plane, with bounds [0.0, 1.0]\n");
    printf("\t N_SAMPLES: %i | Distance between samples: %f\n", 
            N_SAMPLES, 
            DISTANCE_BETWEEN_SAMPLES);
    const auto sampled_pts = makeshape::algs::sample_plane(DISTANCE_BETWEEN_SAMPLES, N_SAMPLES);
    printf("\t Computed [ %zu ] samples\n", sampled_pts.size());
    // write to file, if needed
    const bool debug = result["debug"].as<bool>();
    const std::string filename = result["output_filename"].as<std::string>();
    if (debug && filename != "") {
        std::ofstream myfile;
        myfile.open(filename);
        for (const auto &each : sampled_pts) {
            myfile << each.x() << "," << each.y() << "\n";
        }
        myfile.close();
    }
    return 0;
}
