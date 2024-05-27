
#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
	ARRAY_ERR_UNDERFLOW = -1,
	ARRAY_ERR_OVERFLOW = 0,
	ARRAY_ERR_OK = 1
} ArrayError;

typedef struct {
	int cnt;
	int size;
} Dimension;

typedef struct {
	Dimension * config;
	int size;
	size_t entrysize;
	void * entries;
} Array;

typedef struct {
	size_t entrysize;
	int length;
	int index;
	Array * array;
} ArrayIterator;

typedef struct {
	size_t entrysize;
	int length;
	int index_x;
	int index_y;
	Array * array;
} ArrayIterator2D;

Array * array_new(int dimensions, int dimension_size, size_t entry_size);
Array * array1D_new(int cnt_i, size_t entry_size);
Array * array2D_new(int cnt_i, int cnt_j, size_t entry_size);

Array * array_copy_deep(Array *  array);

void array_init(Array *  array, void *  init_value, void (*assoc_func)(void *  array_entry, int newidx ,void *  init_value));

ArrayError array_get(Array *  array, int index, void (*assoc_func)(void *  result, int newidx ,void *  value),void *  result);
ArrayError array2D_get(Array *  array, int i, int j, void (*assoc_func)(void *  result, int newidx ,void *  value), void *  result);

ArrayError array_set(Array *  array, int index, void *  value, void (*assoc_func)(void *  array_entry, int newidx ,void *  value));
ArrayError array2D_set(Array *  array, int i, int j, void *  value, void (*assoc_func)(void *  array_entry, int newidx ,void *  value));

ArrayIterator * array_iterator_new(Array *  array);
bool array_iterator_has_next(ArrayIterator *  iterator);
void * array_iterator_next(ArrayIterator *  iterator);
void array_iterator_free(ArrayIterator *  iterator);

ArrayIterator2D * array_iterator2D_new(Array *  array);
bool array_iterator2D_has_next(ArrayIterator2D *  iterator);
void * array_iterator2D_next(ArrayIterator2D *  iterator);
void array_iterator2D_free(ArrayIterator2D *  iterator);

void array_free(Array *  array);

#endif
