#ifndef FARRAY_H
#define FARRAY_H

#include "array.h"

void assoc_float(void *  array_entry, int newidx ,void *  init_value);

Array * farray_new(int cnt_i);
Array * farray2D_new(int cnt_i, int cnt_j);

void farray_init(Array *  array, float init_value);

ArrayError farray_get(Array *  array, int index,float *  result);
ArrayError farray2D_get(Array *  array, int i, int j, float *  result);

ArrayError farray_set(Array *  array, int index, float value);
ArrayError farray2D_set(Array *  array, int i, int j, float value);

#endif
