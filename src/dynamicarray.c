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

// Add a value to the end of the array
bool add(DynamicArray *array, const void *value) {
    // Check if the array or value is NULL
    if (array == NULL || value == NULL) {
        fprintf(stderr, "Invalid input.\n");
        return false;
    }

    // Check if the array is full
    if (array->size >= array->capacity) {
        grow_size(array, array->capacity * 2);
    } else {
        // If the array is not full, add the value to the end
        memcpy((char *)array->data + array->size * array->type_size, value, array->type_size);
        array->size++;
    }

    return true;
}

// Get a value from the array
const void* get(const DynamicArray *array, size_t index) {
    if (array == NULL || index >= array->size) {
        fprintf(stderr, "Invalid input.\n");
        return NULL;
    }
    return (const void*)((char *)array->data + index * array->type_size);
}

// Grow the size of the array
bool grow_size(DynamicArray *array, size_t new_capacity) {
    array->capacity = new_capacity;
    array->data = realloc(array->data, array->capacity * array->type_size);
    if (array->data == NULL) {
        fprintf(stderr, "Memory allocation for data failed.\n");
        return false;
    }
    return true;
}