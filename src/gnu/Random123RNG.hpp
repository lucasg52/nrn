#pragma once

#include "RNG.h"
#include "nrnran123.h"

#include <cstdint>

static nrnran123_State* s_;
class NrnRandom123: public RNG {
  public:
    NrnRandom123(uint32_t id1, uint32_t id2, uint32_t id3 = 0);
    virtual ~NrnRandom123();
    virtual uint32_t asLong();
    virtual double asDouble();
    virtual void reset();
    nrnran123_State* s_;
};

