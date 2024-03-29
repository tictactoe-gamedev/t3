#include "t3-helpers.h"
#include "t3-ecs.h"

void T3C_SpriteRenderer_Loop(T3_Component *self);

void T3C_Sprite_Loop(T3_Component *self);

T3_Component *T3C_Sprite_Init(T3C_Texture *texture, SDL_Rect rect, float anchorX, float anchorY) {
    T3C_Sprite *sprite = T3_Helper_Malloc_Safe(sizeof *sprite, T3_FILE, T3_LINE);
    sprite->SourceTexture = texture;
    sprite->Rect = rect;
    sprite->AnchorPoint = T3_Vector2_Init(anchorX, anchorY);

    T3_Component_Default(&sprite->component, true);
    sprite->component.Type = Sprite;
    sprite->component.GameLoopFunction = T3C_Sprite_Loop;
    T3_Helper_Binary_Flag(Set, &sprite->component.HasEvent, OnDestroy);
    return &sprite->component;
}

void T3C_Sprite_Loop(T3_Component *self) {
    if (T3_Helper_Binary_HasFlag(self->IsEventReady, OnDestroy)) {
        free((T3C_Sprite *) self);
    }
}

void T3C_Sprite_OnDestroy(T3_Component *component) {
    free((T3C_Sprite *) component);
}

T3_Component *T3C_SpriteRenderer_Init(void) {
    T3C_SpriteRenderer *spriteRenderer = T3_Helper_Malloc_Safe(sizeof *spriteRenderer, T3_FILE, T3_LINE);
    spriteRenderer->Position = NULL;
    spriteRenderer->Sprite = NULL;
    spriteRenderer->Camera = NULL;
    spriteRenderer->Flip = SDL_FLIP_NONE;

    T3_Component_Default(&spriteRenderer->component, true);
    spriteRenderer->component.Type = SpriteRenderer;
    T3_Helper_Binary_Flag(Set, &spriteRenderer->component.HasEvent, OnDestroy | OnAddComponent | OnLoop);
    return &spriteRenderer->component;
}

T3_Component *T3C_SpriteRenderer_Init_With_Camera(T3C_Camera *camera) {
    T3C_SpriteRenderer *spriteRenderer = T3_Helper_Malloc_Safe(sizeof *spriteRenderer, T3_FILE, T3_LINE);
    spriteRenderer->Position = NULL;
    spriteRenderer->Sprite = NULL;
    spriteRenderer->Camera = camera;
    spriteRenderer->Flip = SDL_FLIP_NONE;

    T3_Component_Default(&spriteRenderer->component, true);
    spriteRenderer->component.Type = SpriteRenderer;

    T3_Helper_Binary_Flag(Set, &spriteRenderer->component.HasEvent, OnDestroy | OnAddComponent | OnLoop);
    spriteRenderer->component.GameLoopFunction = T3C_SpriteRenderer_Loop;
    return &spriteRenderer->component;
}

void T3C_SpriteRenderer_Loop(T3_Component *self) {
    if (T3_Helper_Binary_HasFlag(self->IsEventReady, OnDestroy)) {
        free((T3C_Sprite *) self);
    } else if (T3_Helper_Binary_HasFlag(self->IsEventReady, OnAddComponent)) {
        T3_Component *positionComponent = T3_Entity_GetComponent(self->Owner, Position);
        T3_Component *spriteComponent = T3_Entity_GetComponent(self->Owner, Sprite);
        T3C_SpriteRenderer *renderer = (T3C_SpriteRenderer *) self;

        if (positionComponent == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "%s[%d]:%s", T3_FILE, T3_LINE,
                         "Can't add sprite renderer. No position component on entity!\n");
        }
        if (positionComponent == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "%s[%d]:%s", T3_FILE, T3_LINE,
                         "Can't add sprite renderer. No sprite component on entity!\n");
        }

        renderer->Sprite = (T3C_Sprite *) spriteComponent;
        renderer->Position = (T3C_Position *) positionComponent;
        T3_Helper_Binary_Flag(Clear, &self->IsEventReady, OnAddComponent);

    } else if (T3_Helper_Binary_HasFlag(self->IsEventReady, OnLoop)) {
        T3C_SpriteRenderer *renderer = (T3C_SpriteRenderer *) self;
        T3C_Sprite *sprite = renderer->Sprite;
        SDL_Rect spriteRect = sprite->Rect;
        SDL_Texture *sourceText = sprite->SourceTexture->Texture;
        T3_Vector2 pivotPoint;
        SDL_Point pivotConverted;
        SDL_Rect clipped;
        T3_Vector2 pixelPosition;
        pivotPoint.x = sprite->AnchorPoint.x * spriteRect.w;
        pivotPoint.y = sprite->AnchorPoint.y * spriteRect.h;

        pivotConverted.x = pivotPoint.x;
        pivotConverted.y = pivotPoint.y;

        if (renderer->Camera == NULL) {
            return;
        }

        pixelPosition = T3C_Position_ToPixel(renderer->Position, renderer->Camera);

        pixelPosition = T3_Vector2_Subtract(pixelPosition, pivotPoint);
        clipped.x = pixelPosition.x;
        clipped.y = pixelPosition.y;
        clipped.w = spriteRect.w;
        clipped.h = spriteRect.h;
        SDL_RenderCopyEx(T3_Globals_Get()->MainRenderer, sourceText, &spriteRect, &clipped, 0, &pivotConverted,
                         renderer->Flip);
    }
}

void T3C_SpriteRenderer_OnAddComponent(T3_Component *component) {
    T3_Component *positionComponent = T3_Entity_GetComponent(component->Owner, Position);
    T3_Component *spriteComponent = T3_Entity_GetComponent(component->Owner, Sprite);
    T3C_SpriteRenderer *renderer = (T3C_SpriteRenderer *) component;

    if (positionComponent == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "%s[%d]:%s", T3_FILE, T3_LINE,
                     "Can't add sprite renderer. No position component on entity!\n");
    }
    
    if (positionComponent == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "%s[%d]:%s", T3_FILE, T3_LINE,
                     "Can't add sprite renderer. No sprite component on entity!\n");
    }
    
    renderer->Sprite = (T3C_Sprite *) spriteComponent;
    renderer->Position = (T3C_Position *) positionComponent;
}

void T3C_SpriteRenderer_OnLoop(T3_Component *component) {
    T3C_SpriteRenderer *renderer = (T3C_SpriteRenderer *) component;
    T3C_Sprite *sprite = renderer->Sprite;
    SDL_Rect spriteRect = sprite->Rect;
    SDL_Texture *sourceText = sprite->SourceTexture->Texture;
    T3_Vector2 pivotPoint;
    SDL_Point pivotConverted;
    SDL_Rect clipped;
    T3_Vector2 pixelPosition;

    pivotPoint.x = sprite->AnchorPoint.x * spriteRect.w;
    pivotPoint.y = sprite->AnchorPoint.y * spriteRect.h;

    pivotConverted.x = pivotPoint.x;
    pivotConverted.y = pivotPoint.y;

    if (renderer->Camera == NULL) {
        return;
    }

    pixelPosition = T3C_Position_ToPixel(renderer->Position, renderer->Camera);

    pixelPosition = T3_Vector2_Subtract(pixelPosition, pivotPoint);
    clipped.x = pixelPosition.x;
    clipped.y = pixelPosition.y;
    clipped.w = spriteRect.w;
    clipped.h = spriteRect.h;
    SDL_RenderCopyEx(T3_Globals_Get()->MainRenderer, sourceText, &spriteRect, &clipped, 0, &pivotConverted,
                     renderer->Flip);
}

T3_Entity *T3E_Sprite_Init(const char *entityName,
                           SDL_Renderer *renderer,
                           T3C_Camera *renderCamera,
                           float posX, float posY,
                           const char *imagePath,
                           SDL_Rect spriteRect,
                           float anchorX, float anchorY,
                           uint32 initialChildrenCapacity,
                           uint32 extraComponentCapacity,
                           bool isEnabled,
                           T3_Entity *parent) {

    T3_Component *texture = T3C_Texture_Init_With_Load(renderer, imagePath);
    T3_Component *sprite = T3C_Sprite_Init((T3C_Texture *) texture, spriteRect, anchorX, anchorY);
    T3_Component *spriteRenderer = T3C_SpriteRenderer_Init_With_Camera(renderCamera);
    T3_Component *position = T3C_Position_Init(posX, posY);

    return T3_Entity_Init(entityName,
                          parent,
                          T3_List_Init(initialChildrenCapacity),
                          T3_List_Init_With_Elements(
                                  4 + extraComponentCapacity,
                                  4,
                                  position, texture, sprite, spriteRenderer),
                          isEnabled);
}
