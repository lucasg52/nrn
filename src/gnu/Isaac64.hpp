#pragma once

#include "RNG.h"

void* nrnisaac_new(void);
void nrnisaac_delete(void* rng);
void nrnisaac_init(void* rng, unsigned long int seed);
double nrnisaac_dbl_pick(void* rng);
uint32_t nrnisaac_uint32_pick(void* rng);

#define RANDSIZL (4) /* I recommend 8 for crypto, 4 for simulations */
#define RANDSIZ  (1 << RANDSIZL)
#define RANDMAX  (2 * RANDSIZ)

typedef unsigned long long ub8;
#if defined(uint32_t)
typedef uint32_t ub4;
#else
typedef unsigned int ub4;
#endif
typedef unsigned short int ub2;
typedef unsigned char ub1;

#define DBL32 (2.3283064365386962890625e-10)

struct isaac64_state {
    int randcnt;
    ub8 aa;
    ub8 bb;
    ub8 cc;
    ub8 randrsl[RANDSIZ];
    ub8 mm[RANDSIZ];
};

void isaac64_init(struct isaac64_state* rng, ub4 seed);

void isaac64_generate(struct isaac64_state* rng);

/*
------------------------------------------------------------------------------
Macros to get individual random numbers
------------------------------------------------------------------------------
*/

#define isaac64_uint32(rng)                                                \
    (rng->randcnt > 0 ? (*(((ub4*) (rng->randrsl)) + (rng->randcnt -= 1))) \
                      : (isaac64_generate(rng),                            \
                         rng->randcnt = RANDMAX - 1,                       \
                         *(((ub4*) (rng->randrsl)) + rng->randcnt)))

#define isaac64_dbl32(rng)                                                           \
    (rng->randcnt > 0 ? (DBL32 * (*(((ub4*) (rng->randrsl)) + (rng->randcnt -= 1)))) \
                      : (isaac64_generate(rng),                                      \
                         rng->randcnt = RANDMAX - 1,                                 \
                         DBL32 * (*(((ub4*) (rng->randrsl)) + rng->randcnt))))

class Isaac64: public RNG {
  public:
    Isaac64(uint32_t seed = 0);
    virtual ~Isaac64();
    virtual uint32_t asLong();
    virtual void reset();
    virtual double asDouble();
    uint32_t seed();
    void seed(uint32_t s);

  private:
    uint32_t seed_;
    void* rng_;
    static uint32_t cnt_;
};

