#include "isoc99.h"

#include <cmath>
#include <cstdlib>

/* trying to safely determine if a pointer is a pointer to a double where the
double value would be in a specific range without causing floating exceptions
Of course this founders in general on the dereferencing of invalid memory
so it can only be used when pd is valid over sizeof(double).
*/

int nrn_isdouble(double* pd, double min, double max) {
    if (!pd) {
        return 0;
    }
#if defined(fpclassify)
    int i = fpclassify(*pd);
    if (i == FP_NORMAL || i == FP_ZERO) {
        return *pd >= min && *pd <= max;
    } else {
        return 0;
    }
#else
    return *pd >= min && *pd <= max;
#endif
}
