#include "t3-input.h"
#include "t3-helpers.h"

T3_InputSystem *inputSystem;

void T3_InputSystem_Init (void) {
    T3_InputSystem *ptr;
    T3_Helper_Assert (inputSystem == NULL, T3_FILE_LINE, "Input system is already initialized!");
    ptr = T3_Helper_Malloc_Safe (sizeof *ptr, T3_FILE_LINE);
    inputSystem = ptr;
    inputSystem->KeyStatesPrevious = (Uint8 *) calloc (512, sizeof (Uint8));
    inputSystem->KeyStatesCurrent = (Uint8 *) calloc (512, sizeof (Uint8));
}

void T3_InputSystem_Feed (SDL_Event *e) {
    int x;
    int y;

    while (SDL_PollEvent (e)) {
        if (e->type == SDL_QUIT) {
            break;
        }
    }

    inputSystem->MouseStatePrevious = inputSystem->MouseStateCurrent;
    inputSystem->MousePositionPrevious = inputSystem->MousePositionCurrent;
    inputSystem->MouseStateCurrent = SDL_GetMouseState (&x, &y);

    T3_Vector2_EqualsXY (&inputSystem->MousePositionCurrent, x, y);
    memcpy (inputSystem->KeyStatesPrevious, inputSystem->KeyStatesCurrent, sizeof (Uint8) * 512);
    memcpy (inputSystem->KeyStatesCurrent, SDL_GetKeyboardState (NULL), sizeof (Uint8) * 512);
}

bool T3_InputSystem_GetKeyDown (SDL_Scancode keycode) {
    return inputSystem->KeyStatesPrevious[keycode] == 0 && inputSystem->KeyStatesCurrent[keycode] == 1;
}

bool T3_InputSystem_GetKeyUp (SDL_Scancode keycode) {
    return inputSystem->KeyStatesPrevious[keycode] == 1 && inputSystem->KeyStatesCurrent[keycode] == 0;
}

bool T3_InputSystem_GetKeyHold (SDL_Scancode keycode) {
    return inputSystem->KeyStatesPrevious[keycode] == 1 && inputSystem->KeyStatesCurrent[keycode] == 1;
}

T3_Vector2 T3_InputSystem_GetMousePixelPosition (void) {
    return inputSystem->MousePositionCurrent;
}

T3_Vector2 T3_InputSystem_GetMouseDeltaPosition (void) {
    return T3_Vector2_Subtract (inputSystem->MousePositionCurrent, inputSystem->MousePositionPrevious);
}

bool T3_InputSystem_GetMouseUp (T3_Input_Mouse_Button button) {
    
    bool prev = false;/* T3_Helper_Binary_Has_Flag (SDL_BUTTON(button), inputSystem->MouseStatePrevious);*/
    bool current =false; /*T3_Helper_Binary_Has_Flag (SDL_BUTTON (button), inputSystem->MouseStateCurrent);*/

    return prev && !current;
}

bool T3_InputSystem_GetMouseDown (T3_Input_Mouse_Button button) {
    bool prev =false; /*T3_Helper_Binary_Has_Flag (SDL_BUTTON (button), inputSystem->MouseStatePrevious);*/
    bool current = false;/*T3_Helper_Binary_Has_Flag (SDL_BUTTON (button), inputSystem->MouseStateCurrent);*/

    return !prev && current;
}

bool T3_InputSystem_GetMouseHold (T3_Input_Mouse_Button button) {
    bool prev = false;/*T3_Helper_Binary_Has_Flag (SDL_BUTTON (button), inputSystem->MouseStatePrevious);*/
    bool current = false;/*T3_Helper_Binary_Has_Flag (SDL_BUTTON (button), inputSystem->MouseStateCurrent);*/

    return prev && current;
}

T3_Vector2 T3_InputSystem_GetMouseScenePosition (T3C_Camera *camera, int screenWidth, int screenHeight) {
    T3_Vector2 mouseCurrentPixel = inputSystem->MousePositionCurrent;
    T3_Vector2 diff = T3_Vector2_Init (screenWidth / 2.0f, screenHeight / 2.0f);
    T3_Vector2 result = T3_Vector2_Subtract (mouseCurrentPixel, diff);
    result.y = -result.y;
    return T3_Vector2_Add (camera->ScenePosition->pos, result);
}
