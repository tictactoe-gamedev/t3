#ifndef T3_T3_INPUT_H
#define T3_T3_INPUT_H

#include "t3-math.h"
#include "t3-ecs.h"
#include <SDL_events.h>
#include <SDL_keycode.h>

typedef enum T3_Input_Mouse_Button {
    Left = 1,
    Middle = 2,
    Right = 3,
    Extra1 = 4,
    Extra2 = 5
} T3_Input_Mouse_Button;

typedef struct T3_InputSystem {
    Uint8 *KeyStatesPrevious;
    Uint8 *KeyStatesCurrent;
    Uint32 MouseStatePrevious;
    Uint32 MouseStateCurrent;
    T3_Vector2 MousePositionPrevious;
    T3_Vector2 MousePositionCurrent;
} T3_InputSystem;

void T3_InputSystem_Init(void);
void T3_InputSystem_Feed(SDL_Event *e);
bool T3_InputSystem_GetKeyDown(SDL_Scancode keycode);
bool T3_InputSystem_GetKeyUp(SDL_Scancode keycode);
bool T3_InputSystem_GetKeyHold(SDL_Scancode keycode);
bool T3_InputSystem_GetMouseUp(T3_Input_Mouse_Button button);
bool T3_InputSystem_GetMouseDown(T3_Input_Mouse_Button button);
bool T3_InputSystem_GetMouseHold(T3_Input_Mouse_Button button);
T3_Vector2 T3_InputSystem_GetMousePixelPosition(void);
T3_Vector2 T3_InputSystem_GetMouseScenePosition(T3C_Camera *camera, int screenWidth, int screenHeight);
T3_Vector2 T3_InputSystem_GetMouseDeltaPosition(void);

#endif 
