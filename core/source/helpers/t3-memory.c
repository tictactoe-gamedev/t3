#include "helpers.h"

void *T3_Helper_Malloc_Safe(size_t size, const char *filename, int lineNumber) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        T3_Helper_Log(Error, filename, lineNumber, "Malloc failed!");
    }
    return ptr;
}
