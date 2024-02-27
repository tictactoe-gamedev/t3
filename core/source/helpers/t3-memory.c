#include "t3-helpers.h"

void *T3_Helper_Malloc_Safe (size_t size, const char *filename, int lineNumber) {
    void *ptr = malloc (size);
    if (ptr == NULL) {
        T3_Helper_Log (Error, filename, lineNumber, "Malloc failed!");
    }
    return ptr;
}

bool T3_Helper_Has_Padding (const char *structName, size_t totalSize, uint32 memberCount, ...) {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    uint32 i;
    size_t totalByMembers;
    va_list args;
    totalByMembers = 0;

    va_start(args, memberCount);
    for (i = 0; i < memberCount; ++i) {
        totalByMembers += va_arg(args, size_t);
    }
    va_end(args);
    T3_Helper_Log (Info, T3_FILE_LINE, "%s has a padding of %d", structName, totalSize - totalByMembers);
    return totalSize == totalByMembers;
#endif
}

