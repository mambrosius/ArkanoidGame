
#include <stdio.h>
#include "lut.h"
#include "trigonometry.h"

void initVector(vector_t *vector_p){
    vector_p -> x = 1 << 14;
    vector_p -> y = 2 << 14;
}

long expand(long i) {
    // converts an 18:14 to 16:16
    return i << 2;
}

long multiply(long a, long b) {
    
    return (a * b) >> 14;
}

long degConversion(long x) {
    
    return multiply((x << 14) / 360, 512);
}

long sinus(long x) {
    long deg = degConversion(x); // converting from degrees to 512 format
    return SIN[0x1ff & deg];
}

long cosinus(long x) {
    long deg = degConversion(x); // converting from degrees to 512 format
    return SIN[0x1ff & (deg + 128)];
}

void printFix(long i) {
    i = expand(i);
    // prints a signed 16:16 fixed point number
    if ((i & 0x80000000) != 0) {    // handle negative numbers
        printf("-");
        i = ~i + 1;
    }
    printf("%ld.%04ld", i >> 16, 10000 * (unsigned long)(i & 0xffff) >> 16);
}

void rotate(vector_t *vector_p, long x){
    
    long tempx = multiply(vector_p -> x, cosinus(x)) - multiply(vector_p -> y, sinus(x));
    long tempy = multiply(vector_p -> x, sinus(x)) + multiply(vector_p -> y, cosinus(x));
    vector_p -> x = tempx;
    vector_p -> y = tempy;
}