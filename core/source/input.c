#include "t3-input.h"
#include "helpers.h"

T3_InputSystem *inputSystem;

void T3_InputSystem_Init(void) {
    T3_InputSystem  *ptr;
    T3_Helper_Assert(inputSystem == NULL, T3_FILE_LINE, "Input system is already initialized!");
    ptr = T3_Helper_Malloc_Safe(sizeof *ptr,T3_FILE_LINE);
    inputSystem = ptr;
    inputSystem->KeyStatesPrevious = (Uint8*) calloc(512, sizeof (Uint8));
    inputSystem->KeyStatesCurrent = (Uint8*) calloc(512, sizeof (Uint8));
}

void T3_InputSystem_Feed(SDL_Event *e){
    while (SDL_PollEvent(e)) {
        if (e->type == SDL_QUIT) {
            break;
        }
    }

    memcpy(inputSystem->KeyStatesPrevious,inputSystem->KeyStatesCurrent,sizeof(Uint8)*512);
    memcpy(inputSystem->KeyStatesCurrent,SDL_GetKeyboardState(NULL),sizeof(Uint8)*512);
}

bool T3_InputSystem_GetKeyDown(SDL_Scancode keycode) {
    return inputSystem->KeyStatesPrevious[keycode] == 0 && inputSystem->KeyStatesCurrent[keycode] == 1;
}

bool T3_InputSystem_GetKeyUp(SDL_Scancode keycode) {
    return inputSystem->KeyStatesPrevious[keycode] == 1 && inputSystem->KeyStatesCurrent[keycode] == 0;
}

bool T3_InputSystem_GetKeyHold(SDL_Scancode keycode) {
    return inputSystem->KeyStatesPrevious[keycode] == 1 && inputSystem->KeyStatesCurrent[keycode] == 1;
}
