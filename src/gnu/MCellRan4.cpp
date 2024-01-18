#include "MCellRan4.hpp"

static uint32_t lowindex = 0;

static uint32_t nrnRan4int(uint32_t* idx1, uint32_t idx2) {
    uint32_t u, v, w, m, n;
    /* 64-bit hash */
    n = (*idx1)++;
    m = idx2;

    w = n ^ 0xbaa96887;
    v = w >> 16;
    w &= 0xffff;
    u = ~((v - w) * (v + w));
    /*m ^= (((u >> 16) | (u << 16)) ^ 0xb4f0c4a7) + w * v;*/
    m ^= (((u >> 16) | (u << 16)) ^ 0x4b0f3b58) + w * v;

    w = m ^ 0x1e17d32c;
    v = w >> 16;
    w &= 0xffff;
    u = ~((v - w) * (v + w));
    /*n ^= (((u >> 16) | (u << 16)) ^ 0x178b0f3c) + w * v;*/
    n ^= (((u >> 16) | (u << 16)) ^ 0xe874f0c3) + w * v;
    return n;
}

/*
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function:  Randouble (hines now nrnRan4dbl
//
// Purpose:   Random double-precision floating-point sample.
//            The 2^52 allowed values are odd multiples of 2^-53,
//            symmetrically placed in strict interior of (0,1).
//
// Notes: (1) Tuned to 52-bit mantissa in "double" format.
//        (2) Uses one call to Ranint to get 64 random bits, with extra
//            random integer available in Rand[3].
//        (3) All floating-point random calls are directed through this code,
//            except Rangauss which uses the extra random integer in Rand[3].
//
// History:   John Skilling   6 May 1995, 3 Dec 1995, 24 Aug 1996
//                           20 Oct 2002, 17 Dec 2002
//-----------------------------------------------------------------------------
//
*/
static const double SHIFT32 = 1.0 / 4294967296.0; /* 2^-32 */
static double nrnRan4dbl(uint32_t* idx1, uint32_t idx2) {
    uint32_t hi, lo, extra;
    hi = (uint32_t) nrnRan4int(idx1, idx2); /*top 32 bits*/
                                            /*
                                            //    lo = (extra                               // low bits
                                            //                  & 0xfffff000) ^ 0x00000800;   // switch lowest (2^-53) bit ON
                                            //    return  ((double)hi + (double)lo * SHIFT32) * SHIFT32;
                                            */
    return ((double) hi) * SHIFT32;
}

uint32_t mcell_iran4(uint32_t* high) {
    return nrnRan4int(high, lowindex);
}

double mcell_ran4a(uint32_t* high) {
    return nrnRan4dbl(high, lowindex);
}

void mcell_ran4_init(uint32_t low) {
    lowindex = low;
}

double mcell_ran4(uint32_t* high, double* x, unsigned int n, double range) {
    for (int i = 0; i < n; i++) {
        x[i] = range * nrnRan4dbl(high, lowindex);
    }
    return x[0];
}

double mcell_get_lowindex() {
    return lowindex;
}

uint32_t MCellRan4::cnt_ = 0;

MCellRan4::MCellRan4(uint32_t ihigh, uint32_t ilow) {
    ++cnt_;
    ilow_ = ilow;
    ihigh_ = ihigh;
    if (ihigh_ == 0) {
        ihigh_ = cnt_;
        ihigh_ = (uint32_t) asLong();
    }
    orig_ = ihigh_;
}

void MCellRan4::reset() {
    ihigh_ = orig_;
}

uint32_t MCellRan4::asLong() {
    return (uint32_t) (ilow_ == 0 ? mcell_iran4(&ihigh_) : nrnRan4int(&ihigh_, ilow_));
}

double MCellRan4::asDouble() {
    return (ilow_ == 0 ? mcell_ran4a(&ihigh_) : nrnRan4dbl(&ihigh_, ilow_));
}
