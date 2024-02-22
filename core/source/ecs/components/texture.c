#include "helpers.h"
#include "ecs.h"
#include <SDL_image.h>

void T3C_Texture_OnDestroy(T3_Component *self);

T3_Component *T3C_Texture_Init(void) {
    T3_Component *component;
    T3C_Texture *texture = T3_Helper_Malloc_Safe(sizeof *texture, T3_FILE_LINE);
    texture->Path = NULL;
    texture->Texture = NULL;

    texture->OriginalHeight = 0;
    texture->OriginalWidth = 0;

    texture->Rect.x = 0;
    texture->Rect.y = 0;
    texture->Rect.w = 0;
    texture->Rect.h = 0;

    component = T3_Component_Init(true);

    component->Type = Texture;
    component->Data = texture;
    component->OnDestroy = T3C_Texture_OnDestroy;

    return component;
}

T3_Component *T3C_Texture_Init_With_Load(SDL_Renderer *renderer, const char *path) {
    T3_Component *component;
    T3C_Texture *texture = T3_Helper_Malloc_Safe(sizeof *texture, T3_FILE_LINE);
    texture->Path = path;
    texture->Texture = IMG_LoadTexture(renderer, path);;

    SDL_QueryTexture(texture->Texture, NULL, NULL, &texture->OriginalWidth, &texture->OriginalHeight);
    
    texture->Rect.x = 0;
    texture->Rect.y = 0;
    
    component = T3_Component_Init(true);

    component->Type = Texture;
    component->Data = texture;
    component->OnDestroy = T3C_Texture_OnDestroy;

    T3_Helper_Error_If(texture->Texture == NULL, __FILE__, __LINE__, "Couldn't load the image %s", SDL_GetError());
    
    texture->Rect.w = texture->OriginalWidth;
    texture->Rect.h = texture->OriginalHeight;
    
    return component;
}


void T3C_Texture_OnDestroy(T3_Component *self) {
    T3C_Texture *texture = (T3C_Texture *) self->Data;

    if (texture->Texture != NULL) {
        SDL_DestroyTexture(texture->Texture);
    }

    free(texture);
    free(self);
}

void T3C_Texture_Load(SDL_Renderer *renderer, T3C_Texture *texture, const char *path) {
    texture->Texture = IMG_LoadTexture(renderer, path);
    texture->Path = path;
    T3_Helper_Error_If(texture->Texture == NULL, __FILE__, __LINE__, "Couldn't load the image %s", SDL_GetError());
    SDL_QueryTexture(texture->Texture, NULL, NULL, &texture->OriginalWidth, &texture->OriginalHeight);
    texture->Rect.w = texture->OriginalWidth;
    texture->Rect.h = texture->OriginalHeight;
}

void T3C_Texture_SetSize(T3C_Texture *texture, int width, int height) {
    texture->Rect.w = width;
    texture->Rect.h = height;
}
