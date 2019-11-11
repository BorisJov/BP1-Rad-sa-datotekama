#ifndef KEYOPS_H_INCLUDED
#define KEYOPS_H_INCLUDED

#include <math.h>

unsigned int middle_square_method(const unsigned int init_key)
{
    int n = ceil(log10(PRIMARY_ZONE_BAKET_NUM));
    int t = floor(KEY_MAX_DIGITS - 1.0*n/2);
    unsigned long long k = (long long) init_key * init_key;
    // round neophodan jer float -> int cast zeza
    unsigned int retVal = (int) floor(k/pow(10,t)) % (int) round(pow(10,n));
    //necu +1 jer hocu da imam 0-6 u prim. zoni
    retVal = floor(retVal * PRIMARY_ZONE_BAKET_NUM / pow(10,n));
    return retVal;
}

#endif // KEYOPS_H_INCLUDED
