/*
 * @Author: ggulteki 
 * @Date: 2024-10-08 20:40:27 
 * @Last Modified by: ggulteki
 * @Last Modified time: 2024-10-08 21:21:20
 */

#include "../include/structerc.h"

// Create a dynamic array
DynamicArray *create_dynamic_array(size_t capacity, size_t type_size) {
    if (type_size < 1) { // Check if the type size is valid
        return NULL;
    }

    if (capacity < 1) { // Check if the capacity is valid
        capacity = 10;
    }
    
    DynamicArray *array = malloc(sizeof(DynamicArray)); // Allocate memory for the DynamicArray structure
    if (array == NULL) {
        fprintf(stderr, "Memory allocation for DynamicArray failed.\n");
        return NULL;
    }

    array->data = malloc(capacity * type_size); // Allocate memory for the actual data storage
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
    if (array == NULL || value == NULL) { // Check if the array or value is NULL
        fprintf(stderr, "Invalid input.\n");
        return false;
    }

    if (array->size >= array->capacity) { // Check if the array is full
        grow_size(array, array->capacity * 2);
    } else {
        memcpy((char *)array->data + array->size * array->type_size, value, array->type_size); // If the array is not full, add the value to the end
        array->size++;
    }
    
    array_control(array);

    return true;
}

// Get a value from the array
const void* get(const DynamicArray *array, size_t index) {
    if (array == NULL || index >= array->size) {
        fprintf(stderr, "Invalid index.\n");
        return NULL;
    }

    return (const void*)((char *)array->data + index * array->type_size); // Return the value at the index
}

// Grow the size of the array
bool grow_size(DynamicArray *array, size_t new_capacity) {
    array->capacity = new_capacity; // Set the new capacity
    array->data = realloc(array->data, array->capacity * array->type_size);
    if (array->data == NULL) {
        fprintf(stderr, "Memory allocation for data failed.\n");
        return false;
    }

    array_control(array);

    return true;
}

// Free the array
void free_array(DynamicArray *array) {
    if (array == NULL) {
        fprintf(stderr, "No array to free.\n");
        return;
    }
    
    void **data_ptr = (void **)array->data; // Cast the data pointer to a pointer to a pointer to void

    for (size_t i = 0; i < array->size; i++) { // Free the data in the array
        fprintf(stderr, "test %p\n", data_ptr[i]);
        free(data_ptr[i]);
    }
    
    free(array->data); // Free the array itself 
    fprintf(stderr, "Freeing %p\n", array->data);  
    free(array); // Free the DynamicArray struct
    fprintf(stderr, "Freeing %p\n", array);
}

// Check if the array is too big or too small and shrink or grow it
void array_control(DynamicArray *array) {
    if (array->size < array->capacity / 4 && array->capacity > 10) {
        shrink_size(array, array->capacity / 2); // Shrink the array if the size is less than 1/4 of the capacity and the capacity is greater than 10
        fprintf(stderr, "Shrinking array to %zu\n", array->capacity);
    } else if (array->capacity - array->size < 5) {
        grow_size(array, array->capacity * 1.5); // Grow the array if the size is less than 5
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
    array_control(array);
   
    return true;
}

// Set a value at a specific index
bool set(DynamicArray *array, size_t index, const void *value) {
    if (array == NULL || index >= array->size) {
        fprintf(stderr, "Invalid index.\n");
        return false;
    }
    memcpy((char *)array->data + index * array->type_size, value, array->type_size); // Set the value at the index
    array_control(array);

    return true;
}

// Remove an element at a specific index
bool remove_at(DynamicArray *array, size_t index) {
    if (array == NULL || index >= array->size) {
        fprintf(stderr, "Invalid index.\n");
        return false;
    }

    memmove((char *)array->data + index * array->type_size, (char *)array->data + (index + 1) * array->type_size, (array->size - index - 1) * array->type_size); // Shift the elements to the left
    array->size--;
    array_control(array);
    
    return true;
}

// Clear the array
bool clear(DynamicArray *array) {
    if (array == NULL) {
        fprintf(stderr, "No array to clear.\n");
        return false;
    }

    for (size_t i = 0; i < array->size; i++) { // Free the data in the array
        free((char *)array->data + i * array->type_size);
    }

    array->size = 0;
    array_control(array);
    
    return true;
}