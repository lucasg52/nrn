#include "Rand.hpp"
#include "ACG.h"
#include "Normal.h"

Rand::Rand(unsigned long seed, int size, void* userdata)
: gen(new ACG(seed, size))
, rand(new Normal(0., 1., gen))
, type_(0)
, userdata_(userdata) {
}

Rand::~Rand() {
    delete gen;
    delete rand;
}
