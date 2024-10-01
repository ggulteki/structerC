#include "include/structerc.h"

int main(void) {
    // const char *name = "John Doe";

    // DynamicArray *array = create_dynamic_array(10, sizeof(char *));
    // printf("Array created with capacity: %zu\n", array->capacity);

    // char *name_copy = malloc(strlen(name) + 1);
    // if (name_copy == NULL) {
    //     fprintf(stderr, "Failed to allocate memory for name copy.\n");
    //     free(array);
    //     return 1;
    // }
    // strcpy(name_copy, name);
    // add(array, &name_copy);
    // printf("Added %s to the array\n", *(char **)get(array, 0));
    // free_array(array);

    DynamicArray *array = create_dynamic_array(3, sizeof(int));
    printf("Array created with capacity: %zu\n", array->capacity);
    
    int size = 4;
    
    int *numbers_1 = malloc(size * sizeof(int));
    if (numbers_1 == NULL) {
        fprintf(stderr, "Failed to allocate memory for array.\n");
        return 1;
    }
    int *numbers_2 = malloc(size * sizeof(int));
    if (numbers_2 == NULL) {
        fprintf(stderr, "Failed to allocate memory for array.\n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        numbers_1[i] = i;
    }

    for (int i = 0; i < size; i++) {
        numbers_2[i] = i;
    }
    
    add(array, &numbers_1[0]);
    add(array, &numbers_2[0]);

    printf("Array data: %d\n", *(int *)get(array, 0));
    printf("Array data: %d\n", *(int *)get(array, 1));

    free_array(array);
    free(numbers_1);
    free(numbers_2);
    return 0;
}