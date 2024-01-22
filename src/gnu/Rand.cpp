#include "Rand.hpp"
#include "ACG.h"
#include "distributions.hpp"

Rand::Rand(unsigned long seed, int size, void* userdata)
: gen(new ACG(seed, size))
, d(new Uniform(0., 1.))
, type_(0)
, userdata_(userdata) {
}

Rand::~Rand() {
    delete gen;
    delete d;
}
