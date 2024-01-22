#pragma once

#include <memory>

#include <Random123/philox.h>
#include <Random123/MicroURNG.hpp>

class random123RNG {
    r123::Philox4x32::ctr_type c;
    r123::Philox4x32::key_type k;
    std::shared_ptr<r123::MicroURNG<r123::Philox4x32>> longmurng;

    public:
    random123RNG();
    std::shared_ptr<r123::MicroURNG<r123::Philox4x32>> get_random_generator() {
        return longmurng;
    }
};
