#include "../include/structerc.h"

// Create a dynamic array
DynamicArray *create_dynamic_array(size_t capacity, size_t type_size) {
    // Check if the type size is valid
    if (type_size < 1) {
        return NULL;
    }

    // Check if the capacity is valid
    if (capacity < 1) {
        capacity = 10;
    }
    
    // Allocate memory for the DynamicArray structure
    DynamicArray *array = malloc(sizeof(DynamicArray));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation for DynamicArray failed.\n");
        return NULL;
    }

    // Allocate memory for the actual data storage
    array->data = malloc(capacity * type_size);
    if (array->data == NULL) {
        free(array); // Free the allocated DynamicArray structure on failure
        fprintf(stderr, "Memory allocation for data failed.\n");
        return NULL;  
    }

    array->size = 0;
    array->capacity = capacity;
    array->type_size = type_size;
    
    return array;
}