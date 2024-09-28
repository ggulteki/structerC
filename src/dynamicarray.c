#include "../include/structerc.h"

DynamicArray* create_dynamic_array(size_t capacity, size_t type_size) {
    DynamicArray *array = (DynamicArray*)malloc(sizeof(DynamicArray));
    array->data = (void*)malloc(capacity * type_size);
    array->size = 0;
    array->capacity = capacity;
    return array;
}