#pragma once

#include "distributions.hpp"
#include "Random123RNG.hpp"

class Rand {
    public:
        Rand() = default;
        ~Rand() = default;
        NrnRandom123* gen;
        Distribution* d;
        void* userdata_{};
};
