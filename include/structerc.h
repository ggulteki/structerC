/*
 * structerc.h
 *
 * A simple dynamic array library in C
 *
 * Author: ggulteki
 * Date: $Date$
 */ 

#ifndef STRUCTERC_H  
#define STRUCTERC_H

#include <stdint.h>
#include <stddef.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct {
    // data of the array
    void *data;
    // size of the array
    size_t size;
    // capacity of the array
    size_t capacity;
    // type size of the array
    size_t type_size;
} DynamicArray;

// Function prototypes
DynamicArray* create_dynamic_array(size_t capacity, size_t type_size);
bool add(DynamicArray *array, const void *value);
bool remove_at(DynamicArray *array, size_t index);
void clear(DynamicArray *array);
bool contains(const DynamicArray *array, const void *value);
const void* get(const DynamicArray *array, size_t index);
bool set(DynamicArray *array, size_t index, const void *value);
size_t index_of(const DynamicArray *array, const void *value);
bool grow_size(DynamicArray *array);       
void destroy_dynamic_array(DynamicArray *array);
bool resize_dynamic_array(DynamicArray *array, size_t new_size);
size_t get_dynamic_array_size(const DynamicArray *array);
size_t get_dynamic_array_capacity(const DynamicArray *array);

#endif