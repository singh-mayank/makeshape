// Copyright MakeShape. 2019, All rights reserved.

#include "edges.hh"

#pragma once

namespace makeshape {
namespace spatial {

constexpr int CubeEdges::N_VERTICES;
constexpr int CubeEdges::N_EDGES;

Edges make_edges(const std::vector<CubeEdges> &ne) {
    // build edges
    Edges e;
    {
        constexpr size_t DIM = 3;
        // vertices
        e.P.resize(ne.size()*CubeEdges::N_VERTICES, DIM);
        for (size_t i = 0; i < ne.size(); ++i) {
            for(size_t j = 0; j < CubeEdges::N_VERTICES; ++j) {
                const size_t index = i * CubeEdges::N_VERTICES + j;
                for(size_t k = 0; k < DIM; ++k) {
                    e.P(index, k) = ne[i].v[j][k];
                }
            }
        }
        // edges 
        constexpr size_t VERTICES_PER_EDGE = 2;
        e.E.resize(ne.size()*CubeEdges::N_EDGES, VERTICES_PER_EDGE); // 2 vertices per edge
        for (size_t i = 0; i < ne.size(); ++i) {
            const size_t offset = i*CubeEdges::N_EDGES;
            for(size_t j = 0; j < CubeEdges::N_EDGES; ++j) {
                int row = static_cast<int>(offset + j);
                int ii = static_cast<int>(i * 8);
                e.E(row, 0) = ne[i].e[j].first + (ii);
                e.E(row, 1) = ne[i].e[j].second + (ii);
            }
        }
        // color
        e.C.resize(1, 3);
        e.C(0, 0) = 1;
        e.C(0, 1) = 1;
        e.C(0, 2) = 1;

        // TODO(mayank): Add a set of assets and remove this code
#if 0
        // print debug
        {
            for (size_t i = 0; i < ne.size(); ++i) {
                for(size_t j = 0; j < N_VERTICES; ++j) {
                    const size_t index = i*N_VERTICES + j;
                    printf("[%zu]: [%f, %f, %f]\n",
                            index,
                            e.P(index, 0),
                            e.P(index, 1),
                            e.P(index, 2));
                }
            }
        
            for (size_t i = 0; i < ne.size(); ++i) {
                for(size_t j = 0; j < N_EDGES; ++j) {
                    const size_t index = i*N_EDGES + j;
                    printf("[%zu]: [%i, %i]\n",
                            index,
                            e.E(index, 0),
                            e.E(index, 1));
                }
            }
        }
#endif
    }
    return e;
}

} // spatial 
} // makeshape
