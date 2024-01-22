#include "Random123RNG.hpp"

static char initialized = 0;

random123RNG::random123RNG() {
    if (!initialized) {
        initialized = true;
        c = {{}};
        k = {{}};
        longmurng = std::make_unique<r123::MicroURNG<r123::Philox4x32>>(c.incr(), k);
    }
}
