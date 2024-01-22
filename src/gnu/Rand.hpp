#pragma once

#include "RNG.h"
#include "Random.h"
#include "distributions.hpp"

// class for a random number generator based on the RNG class
// defaults to the ACG generator

// type_:
// 0: ACG
// 1: MLCG
// 2: MCellRan4
// 3: Isaac64
// 4: Random123
class Rand {
  public:
    Rand(unsigned long seed = 0, int size = 55, void* userdata = nullptr);
    ~Rand();
    RNG* gen;
    Distribution* d;
    int type_;
    void* userdata_;
};
