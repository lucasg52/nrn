#include "hocdec.h"
#include "MCellRan4.hpp"

// hoc binding of gnu/MCellRan4.hpp
extern double chkarg();
extern int use_mcell_ran4_;

void hoc_mcran4() {
    uint32_t idx;
    double* xidx;
    double x;
    xidx = hoc_pgetarg(1);
    idx = (uint32_t) (*xidx);
    x = mcell_ran4a(&idx);
    *xidx = idx;
    hoc_ret();
    hoc_pushx(x);
}
void hoc_mcran4init() {
    double prev = mcell_get_lowindex();
    if (ifarg(1)) {
        uint32_t idx = (uint32_t) chkarg(1, 0., 4294967295.);
        mcell_ran4_init(idx);
    }
    hoc_ret();
    hoc_pushx(prev);
}
void hoc_usemcran4() {
    double prev = (double) use_mcell_ran4_;
    if (ifarg(1)) {
        use_mcell_ran4_ = (int) chkarg(1, 0., 1.);
    }
    hoc_ret();
    hoc_pushx(prev);
}
