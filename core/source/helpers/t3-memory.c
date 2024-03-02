#include <SDL_log.h>
#include "t3-helpers.h"

void *T3_Helper_Malloc_Safe(size_t size, const char *filename, int lineNumber) {
    void *ptr = SDL_malloc(size);
    if (ptr == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s[%d]: %s", filename, lineNumber, "Malloc failed!");
    }
    return ptr;
}

bool T3_Helper_Has_Padding(const char *structName, size_t totalSize, uint32 memberCount, ...) {
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
    SDL_Log("%s[%d]: %s has a padding of %lu", T3_FILE, T3_LINE, structName, totalSize - totalByMembers);
    return totalSize == totalByMembers;
#endif
}

