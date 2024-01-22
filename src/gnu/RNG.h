#pragma once
/*
 * int32_t and uint32_t have been defined by the configure procedure.  Just
 * use these in place of the ones that libg++ used to provide. 
 */
#include <cstdint>

//
// Base class for Random Number Generators. See ACG and MLCG for instances.
//
class UniformRandomBitGenerator {
public:
    UniformRandomBitGenerator();
    virtual ~UniformRandomBitGenerator();
    virtual std::uint32_t min();
    virtual std::uint32_t max();
    virtual std::uint32_t operator()();
};
