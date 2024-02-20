#ifndef T3_T3_INPUT_H
#define T3_T3_INPUT_H

#include "globals.h"
#include <SDL_events.h>
#include <SDL_keycode.h>

typedef enum T3_KeyState {
    KeyDown, KeyHold, KeyUp
} T3_KeyState;

typedef struct T3_InputSystem {
    Uint8 *KeyStatesPrevious;
    Uint8 *KeyStatesCurrent;
} T3_InputSystem;

void T3_InputSystem_Init(void);

void T3_InputSystem_Feed(SDL_Event *e);

bool T3_InputSystem_GetKeyDown(SDL_Scancode keycode);

bool T3_InputSystem_GetKeyUp(SDL_Scancode keycode);

bool T3_InputSystem_GetKeyHold(SDL_Scancode keycode);

#endif 
