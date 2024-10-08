/*
 * @Author: ggulteki 
 * @Date: 2024-10-08 20:41:31 
 * @Last Modified by:   ggulteki 
 * @Last Modified time: 2024-10-08 20:41:31 
 */

#ifndef STRUCTERC_H  
#define STRUCTERC_H

#include <stdint.h>
#include <stddef.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
bool grow_size(DynamicArray *array, size_t new_capacity);       
void destroy_dynamic_array(DynamicArray *array);
bool resize_dynamic_array(DynamicArray *array, size_t new_size);
size_t get_dynamic_array_size(const DynamicArray *array);
size_t get_dynamic_array_capacity(const DynamicArray *array);
void free_array(DynamicArray *array);
bool shrink_size(DynamicArray *array, size_t new_capacity);
void array_control(DynamicArray *array);

#endif