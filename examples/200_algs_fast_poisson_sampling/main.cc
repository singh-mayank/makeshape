// Copyright MakeShape. 2019, All rights reserved.

#include "app.hh"
#include "fast_poisson_sampling.hh"

#include <cxxopts.hpp>


namespace {
void write_to_file(const std::string &filename, 
        const std::vector<Eigen::Vector2d> &points) {
    std::ofstream file_out;
    file_out.open(filename);
    for (const auto &each : points) {
        file_out << each.x() << "," << each.y() << "\n";
    }
    file_out.close();
}
}


//
// launch application
// 
int main(int argc, char *argv[])
{
    cxxopts::Options options("Fast Poisson Sampling example", 
            "Generates a set of random samples on a 2d plane (XY), with bounds [0.0, 1.0]");
    // add command line options
    {
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
    }
    // parse options
    const auto result = options.parse(argc, argv);
    if (result.count("help")) {
        printf("%s\n", options.help().c_str());
        return 0;
    }
    const double dist_bet_samples = result["dist"].as<double>();
    const int n_samples = result["samples"].as<int>();
    const bool debug = result["debug"].as<bool>();
    const std::string filename = result["output_filename"].as<std::string>();

    // compute samples
    const auto sampled_pts = makeshape::algs::sample_points_on_plane(dist_bet_samples, n_samples);
    
    // print
    if (debug) {
        printf("Fast Poisson Sampling on 2d plane, with bounds [0.0, 1.0]\n");
        printf("\t # of samples: %i | Distance between samples: %f\n", n_samples, dist_bet_samples);
        printf("\t Computed [ %zu ] samples\n", sampled_pts.size());
        if (!filename.empty()) {
            write_to_file(filename, sampled_pts);
        }
    }
    return 0;
}
