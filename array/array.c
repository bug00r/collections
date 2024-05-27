#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

Array * 
array_new(int dimensions, int dimension_size, size_t entry_size){
	Array * newarray = malloc(sizeof(Array));
	newarray->entries = malloc(dimensions*dimension_size*entry_size);
	newarray->size = dimensions * dimension_size;
	newarray->entrysize = entry_size;
	Dimension * newdim = malloc(sizeof(Dimension));
	newdim->cnt = dimensions;
	newdim->size = dimension_size;
	newarray->config = newdim;
	return newarray;
}

Array * 
array1D_new(int cnt_i, size_t entry_size){
	return array_new(1, cnt_i, entry_size);
}

Array * 
array2D_new(int cnt_i, int cnt_j, size_t entry_size){
	return array_new(cnt_i, cnt_j, entry_size);
}

Array * 
array_copy_deep(Array *  array){
	Array * newarray = array_new(array->config->cnt, array->config->size, array->entrysize);
	memcpy(newarray->entries, array->entries, array->entrysize*array->size);
	return newarray;
}

void 
array_init(Array *  array, void *  init_value, void (*assoc_func)(void *  array_entry, int newidx ,void *  init_value)){
	int size = array->config->size;
	int cnt = array->config->cnt;
	for(int i = 0; i < cnt; ++i){
		for(int j = 0; j < size; ++j){
			int newidx = (i * size + j);
			(*assoc_func)(array->entries, newidx, init_value);
		}
	}
}

ArrayError 
array_get(Array *  array, int index, void (*assoc_func)(void *  result, int newidx ,void *  value), void *  result)
{
	if ( index < 0 ){
		return ARRAY_ERR_UNDERFLOW;
	} else if (index < array->size){
		(*assoc_func)(result, 0, array->entries+(index*array->entrysize));
		return ARRAY_ERR_OK;
	} else {
		return ARRAY_ERR_OVERFLOW;
	}
}

ArrayError 
array2D_get(Array *  array, int j, int i, void (*assoc_func)(void *  result, int newidx,void *  value), void *  result){
	return array_get( array, (i * array->config->cnt + j), (*assoc_func), result);
}

ArrayError 
array_set(Array *  array, int index, void *  value, void (*assoc_func)(void *  array_entry, int newidx ,void *  value)){
	if ( index < 0 ){
		return ARRAY_ERR_UNDERFLOW;
	} else if (index < array->size) {
		(*assoc_func)(array->entries+(index*array->entrysize), 0, value);
		return ARRAY_ERR_OK;
	} else {
		return ARRAY_ERR_OVERFLOW;
	}
}

ArrayError 
array2D_set(Array *  array, int j, int i, void *  value, void (*assoc_func)(void *  array_entry, int newidx ,void *  value)){
	return array_set( array, (i * array->config->cnt + j), value, (*assoc_func));
}

ArrayIterator * 
array_iterator_new(Array *  array){
	ArrayIterator * new_it = malloc(sizeof(ArrayIterator));
	new_it->index = 0;
	new_it->array = array;
	return new_it;
}

bool array_iterator_has_next(ArrayIterator *  iterator){
	return iterator->index < iterator->array->size;
}

void * 
array_iterator_next(ArrayIterator *  iterator){
	return iterator->array->entries + (iterator->index++*iterator->array->entrysize);
}

void 
array_iterator_free(ArrayIterator *  iterator){
	free(iterator);
}

ArrayIterator2D * 
array_iterator2D_new(Array *  array){
	ArrayIterator2D * new_it = malloc(sizeof(ArrayIterator2D));
	new_it->index_x = 0;
	new_it->index_y = 0;
	new_it->array = array;
	return new_it;
}

bool array_iterator2D_has_next(ArrayIterator2D *  iterator){
	return (iterator->index_y * iterator->array->config->size + iterator->index_x ) < iterator->array->size;
}

void * 
array_iterator2D_next(ArrayIterator2D *  iterator){
	void * entry = iterator->array->entries+((iterator->index_y * iterator->array->config->size + iterator->index_x )*iterator->array->entrysize);
	
	if ( iterator->index_x == iterator->array->config->size ){
		#ifdef debug
			printf("iterator index will resettet: curindex: %i y: %i\n", iterator->index_x, iterator->index_y);
		#endif
		iterator->index_x = 0;
		iterator->index_y++;
		#ifdef debug
			printf("after resettet: curindex: %i y: %i\n", iterator->index_x, iterator->index_y);
		#endif
	} else{
		iterator->index_x++;
	}
	return entry;
}

void 
array_iterator2D_free(ArrayIterator2D *  iterator){
	free(iterator);
}


void 
array_free(Array *  array){
	free(array->config);
	free(array->entries);
	free(array);
}

