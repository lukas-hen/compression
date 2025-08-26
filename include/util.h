#ifndef UTIL_H
#define UTIL_H

#include<stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b)

void swap(void *a, void *b, size_t size);

#endif