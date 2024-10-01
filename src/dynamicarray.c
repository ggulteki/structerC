/*
*   Dynamic array implementation in C
*   
*   Author: ggulteki
* Date: 2024-10-02
*/

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

    // Check if the array is too big
    array_control(array);

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

// Free the array
void free_array(DynamicArray *array) {
    if (array == NULL) {
        fprintf(stderr, "No array to free.\n");
        return;
    }
    
    // Cast the data pointer to a pointer to a pointer to void  
    void **data_ptr = (void **)array->data;

    // Free the data in the array
    for (size_t i = 0; i < array->size; i++) {
        fprintf(stderr, "test %p\n", data_ptr[i]);
        free(data_ptr[i]);
    }
    
    // Free the array itself 
    free(array->data);
    fprintf(stderr, "Freeing %p\n", array->data);
    // Free the DynamicArray struct
    free(array);
    fprintf(stderr, "Freeing %p\n", array);

}

// Check if the array is too big or too small and shrink or grow it
void array_control(DynamicArray *array) {
    if (array->size < array->capacity / 4 && array->capacity > 10) {
        shrink_size(array, array->capacity / 2);
        fprintf(stderr, "Shrinking array to %zu\n", array->capacity);
    } else if (array->capacity - array->size < 5) {
        // Grow the array if the size is less than 5
        grow_size(array, array->capacity * 1.5);
        fprintf(stderr, "Growing array to %zu\n", array->capacity);
    }
    return;
}

// Shrink the size of the array
bool shrink_size(DynamicArray *array, size_t new_capacity) {
    array->capacity = new_capacity;
    array->data = realloc(array->data, array->capacity * array->type_size);
    
    if (array->data == NULL) {
        fprintf(stderr, "Memory allocation for data failed.\n");
        return false;
    }

    fprintf(stderr, "Shrinking array to %zu\n", array->capacity);
   
    return true;
}