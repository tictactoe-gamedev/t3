#include "t3-helpers.h"
#include "t3-ecs.h"
#include <SDL_image.h>

void T3C_Texture_OnDestroy(T3_Component *self);

void T3C_Texture_Loop(T3_Component *self) {}

T3_Component *T3C_Texture_Init(void) {
    T3C_Texture *texture = T3_Helper_Malloc_Safe(sizeof *texture, T3_FILE, T3_LINE);
    texture->Texture = NULL;

    texture->OriginalHeight = 0;
    texture->OriginalWidth = 0;

    texture->Rect.x = 0;
    texture->Rect.y = 0;
    texture->Rect.w = 0;
    texture->Rect.h = 0;

    T3_Component_Default(&texture->component, true);

    texture->component.Type = Texture;
    T3_Helper_Binary_Flag(Set, &texture->component.HasEvent, OnDestroy);
    texture->component.GameLoopFunction = T3C_Texture_Loop;

    return &texture->component;
}

T3_Component *T3C_Texture_Init_With_Load(SDL_Renderer *renderer, const char *path) {
    T3C_Texture *texture = T3_Helper_Malloc_Safe(sizeof *texture, T3_FILE, T3_LINE);
    SDL_snprintf(texture->Path, 204, "%s", path);
    texture->Texture = IMG_LoadTexture(renderer, path);;

    SDL_QueryTexture(texture->Texture, NULL, NULL, &texture->OriginalWidth, &texture->OriginalHeight);

    texture->Rect.x = 0;
    texture->Rect.y = 0;

    T3_Component_Default(&texture->component, true);

    texture->component.Type = Texture;
    T3_Helper_Binary_Flag(Set, &texture->component.HasEvent, OnDestroy);
    if (texture->Texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "%s[%d]:%s %s\n", T3_FILE, T3_LINE,
                     "Couldn't load the image ", SDL_GetError());
    }

    if (texture->Texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "%s[%d]:%s %s\n", T3_FILE, T3_LINE, "Image load failed", SDL_GetError());
    }

    texture->component.GameLoopFunction = T3C_Texture_Loop;
    texture->Rect.w = texture->OriginalWidth;
    texture->Rect.h = texture->OriginalHeight;

    return &texture->component;
}

void T3C_Texture_OnDestroy(T3_Component *self) {
    T3C_Texture *texture = (T3C_Texture *) self;

    if (texture->Texture != NULL) {
        SDL_DestroyTexture(texture->Texture);
    }

    free(texture);
}

void T3C_Texture_Load(SDL_Renderer *renderer, T3C_Texture *texture, const char *path) {
    texture->Texture = IMG_LoadTexture(renderer, path);
    SDL_snprintf(texture->Path, 204, "%s", path);

    if (texture->Texture == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s[%d]: %s %s\n", T3_FILE, T3_LINE, "Image loading failed ", SDL_GetError());
    }

    SDL_QueryTexture(texture->Texture, NULL, NULL, &texture->OriginalWidth, &texture->OriginalHeight);
    texture->Rect.w = texture->OriginalWidth;
    texture->Rect.h = texture->OriginalHeight;
}

void T3C_Texture_SetSize(T3C_Texture *texture, int width, int height) {
    texture->Rect.w = width;
    texture->Rect.h = height;
}
