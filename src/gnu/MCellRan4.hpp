#pragma once

/*
The copyrighted code from  Numerical Recipes Software has been removed
and replaced by an independent implementation found in the random.cpp file
in function Ranint4
from http://www.inference.phy.cam.ac.uk/bayesys/BayesSys.tar.gz
by John Skilling
http://www.inference.phy.cam.ac.uk/bayesys/
The code fragment was further modified by Michael Hines to change prototypes
and produce output identical to the old version. This code is now
placed under the General GNU Public License, version 2. The random.cpp file
contained the header:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Filename:  random.cpp
//
// Purpose:   Random utility procedures for BayeSys3.
//
// History:   Random.cpp 17 Nov 1994 - 13 Sep 2003
//
// Acknowledgments:
//   "Numerical Recipes", Press et al, for ideas
//   "Handbook of Mathematical Functions", Abramowitz and Stegun, for formulas
//    Peter J Acklam website, for inverse normal code
//-----------------------------------------------------------------------------
    Copyright (c) 1994-2003 Maximum Entropy Data Consultants Ltd,
                            114c Milton Road, Cambridge CB4 1XE, England

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "RNG.h"

// The decision that has to be made is whether each generator instance
// should have its own seed or only one seed for all. We choose separate
// seed for each but if arg not present or 0 then seed chosen by system.

// the addition of ilow > 0 means that value is used for the lowindex
// instead of the mcell_ran4_init global 32 bit lowindex.

uint32_t mcell_iran4(uint32_t* idx1);
double mcell_ran4a(uint32_t* idx1);
void mcell_ran4_init(uint32_t);
double mcell_ran4(uint32_t* idx1, double* x, unsigned int n, double range);
double mcell_get_lowindex();

class MCellRan4: public RNG {
  public:
    MCellRan4(uint32_t ihigh = 0, uint32_t ilow = 0);
    virtual ~MCellRan4() = default;

    virtual void reset();

    virtual uint32_t asLong();
    virtual double asDouble();

    uint32_t ihigh_;
    uint32_t orig_;
    uint32_t ilow_;

  private:
    static uint32_t cnt_;
};


