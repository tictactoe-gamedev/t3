#include "helpers.h"
#include "ecs.h"

void T3C_Sprite_OnDestroy(T3_Component *component);

void T3C_SpriteRenderer_OnAddComponent(T3_Component *component);

void T3C_SpriteRenderer_OnLoop(T3_Component *component);

T3_Component *T3C_Sprite_Init(T3C_Texture *texture, SDL_Rect rect, T3_Vector2 anchorPoint) {
    T3_Component *component;
    T3_HELPER_MALLOC_SAFE(T3C_Sprite, sprite);
    sprite->SourceTexture = texture;
    sprite->Rect = rect;
    sprite->AnchorPoint = anchorPoint;

    component = T3_Component_Init(true);
    component->Type = T3C_TYPE_SPRITE;
    component->Data = sprite;
    component->OnDestroy = T3C_Sprite_OnDestroy;
    return component;
}

void T3C_Sprite_OnDestroy(T3_Component *component) {
    free(component->Data);
    free(component);
}

T3_Component *T3C_SpriteRenderer_Init(void) {
    T3_Component *component;
    T3_HELPER_MALLOC_SAFE(T3C_SpriteRenderer, spriteRenderer);
    spriteRenderer->Position = NULL;
    spriteRenderer->Sprite = NULL;
    spriteRenderer->Camera = NULL;
    spriteRenderer->Flip = SDL_FLIP_NONE;

    component = T3_Component_Init(true);
    component->Type = T3C_TYPE_SPRITE_RENDERER;
    component->Data = spriteRenderer;
    component->OnDestroy = T3C_Sprite_OnDestroy;
    component->OnAddComponent = T3C_SpriteRenderer_OnAddComponent;
    component->OnLoop = T3C_SpriteRenderer_OnLoop;
    return component;
}

T3_Component *T3C_SpriteRenderer_Init_With_Camera(T3C_Camera *camera) {
    T3_Component *component;
    T3_HELPER_MALLOC_SAFE(T3C_SpriteRenderer, spriteRenderer);
    spriteRenderer->Position = NULL;
    spriteRenderer->Sprite = NULL;
    spriteRenderer->Camera = camera;
    spriteRenderer->Flip = SDL_FLIP_NONE;

    component = T3_Component_Init(true);
    component->Type = T3C_TYPE_SPRITE_RENDERER;
    component->Data = spriteRenderer;
    component->OnDestroy = T3C_Sprite_OnDestroy;
    component->OnAddComponent = T3C_SpriteRenderer_OnAddComponent;
    component->OnLoop = T3C_SpriteRenderer_OnLoop;
    return component;
}

void T3C_SpriteRenderer_OnAddComponent(T3_Component *component) {
    T3_Component *positionComponent = T3_Entity_GetComponent(component->Owner, T3C_TYPE_POSITION);
    T3_Component *spriteComponent = T3_Entity_GetComponent(component->Owner, T3C_TYPE_SPRITE);
    T3C_SpriteRenderer *renderer = (T3C_SpriteRenderer *) component->Data;
    T3_Helper_Error_If(positionComponent == NULL, __FILE__, __LINE__,
                       "Can't add sprite renderer. No position component on entity!");
    T3_Helper_Error_If(spriteComponent == NULL, __FILE__, __LINE__,
                       "Can't add sprite renderer. No sprite component on entity!");

    renderer->Sprite = (T3C_Sprite *) spriteComponent->Data;
    renderer->Position = (T3C_Position *) positionComponent->Data;
}

void T3C_SpriteRenderer_OnLoop(T3_Component *component) {
    T3C_SpriteRenderer *renderer = (T3C_SpriteRenderer *) component->Data;
    T3C_Sprite *sprite;
    SDL_Rect spriteRect;
    SDL_Texture *sourceText;
    T3_Vector2 pivotPoint;
    SDL_Point pivotConverted;
    T3_Vector2 pixelPosition;
    SDL_Rect clipped;

    if (renderer->Camera == NULL) {
        return;
    }

    sprite = renderer->Sprite;
    spriteRect = sprite->Rect;
    sourceText = sprite->SourceTexture->Texture;
    pivotPoint.x = sprite->AnchorPoint.x * spriteRect.w;
    pivotPoint.y = sprite->AnchorPoint.y * spriteRect.h;
    pivotConverted.x = pivotPoint.x;
    pivotConverted.y = pivotPoint.y;


    pixelPosition = T3C_Position_ToPixel(renderer->Position, renderer->Camera);

    pixelPosition = T3_Vector2_Subtract(pixelPosition, pivotPoint);

    clipped.x = pixelPosition.x;
    clipped.y = pixelPosition.y;
    clipped.w = spriteRect.w;
    clipped.h = spriteRect.h;
    
    SDL_RenderCopyEx(T3_Globals_Get()->MainRenderer, sourceText, &spriteRect, &clipped, 0, &pivotConverted,
                     renderer->Flip);
}
