// NOTE: this assumes neuronapi.h is on your CPLUS_INCLUDE_PATH
#include "neuronapi.h"
#include <dlfcn.h>

#include <array>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#include "./test_common.h"

using std::cout;
using std::endl;
using std::ofstream;

constexpr std::array<double, 3> EXPECTED_V{
#ifndef CORENEURON_ENABLED
    -0x1.04p+6,
    -0x1.b254ad82e20edp+5,
    -0x1.24a52af1ab463p+6,
#else
    -0x1.04p+6,
    -0x1.b0c75635b5bdbp+5,
    -0x1.24a84bedb7246p+6,
#endif
};

static const char* argv[] = {"hh_sim", "-nogui", "-nopython", nullptr};

int main(void) {
    Section* soma;
    Object* iclamp;
    Object* v;
    Object* t;
    char* temp_str;

    nrn_init(3, argv);

    // load the stdrun library
    nrn_function_call_s("load_file", "stdrun.hoc");

    // topology
    soma = nrn_section_new("soma");
    nrn_nseg_set(soma, 3);

    // define soma morphology with two 3d points
    nrn_section_push(soma);
    nrn_arg_t add_args_t[] = {ARG_DOUBLE, ARG_DOUBLE, ARG_DOUBLE, ARG_DOUBLE, NRN_ARGS_END};
    nrn_function_call("pt3dadd", add_args_t, 0, 0, 0, 10);
    nrn_function_call("pt3dadd", add_args_t, 10, 0, 0, 10);

    // ion channels
    nrn_mechanism_insert(soma, nrn_symbol("hh"));

    // current clamp at soma(0.5)
    nrn_double_push(0.5);
    iclamp = nrn_object_new(nrn_symbol("IClamp"), 1);
    nrn_property_set(iclamp, "amp", 0.3);
    nrn_property_set(iclamp, "del", 1);
    nrn_property_set(iclamp, "dur", 0.1);

    // setup recording
    v = nrn_object_new(nrn_symbol("Vector"), 0);
    nrn_rangevar_push(nrn_symbol("v"), soma, 0.5);
    nrn_double_push(5.);
    nrn_method_call(v, nrn_method_symbol(v, "record"), 2);
    nrn_object_unref(nrn_object_pop());  // record returns the vector

    nrn_function_call_d("finitialize", -65);

    nrn_function_call_d("continuerun", 10.5);

    if (!approximate(EXPECTED_V, v)) {
        return 1;
    }
}