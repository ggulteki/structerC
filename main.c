

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "include/structerc.h"

int main(void) {
    DynamicArray *array = create_dynamic_array(10, sizeof(int));
    printf("Array created with capacity: %zu\n", array->capacity);
    free(array);
    return 0;
}