#ifndef CALCULATE_H
#define CALCULATE_H

#include <str.hpp>

extern unsigned char angle_type;

extern signed char calculate(const optr_hash a,
			     long double &ans,
			     const long double &x,
			     const long double y = 0);

#endif
