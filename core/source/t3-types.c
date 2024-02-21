#include "t3-types.h"

const char * T3_TypeOf(T3C_Type typeID){
    switch (typeID) {
        case 0: case 1: return "Bool(int)";
        case 2: return "T3C_TYPE_POSITION";
        case 3: return "T3C_TYPE_SCENE";
        case 4: return "T3C_TYPE_CAMERA";
        case 5: return "T3C_TYPE_TEXTURE";
        case 6: return "T3C_TYPE_SPRITE";
        case 7: return "T3C_TYPE_SPRITE_RENDERER";
        default: return "Unknown Type";
    }
}
