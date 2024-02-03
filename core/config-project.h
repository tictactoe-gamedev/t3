#ifndef T3_CONFIG_PROJECT_H
#define T3_CONFIG_PROJECT_H

#include "ecs.h"

#define DEVELOPMENT 1
#define PRODUCTION 2
#define CONFIG_BUILD_TYPE DEVELOPMENT

#define CONFIG_MINIMUM_LOG_LEVEL Info
//#define CONFIG_MINIMUM_LOG_LEVEL Warning
//#define CONFIG_MINIMUM_LOG_LEVEL Error

#define CONFIG_ENTRY_POINT_FUNCTION_NAME Main

/** EDITING THE REST OF THIS HEADER IS NOT ADVISED */

typedef struct {
    int Width;
    int Height;
} T3_Config_Resolution;

#define CONFIG_ENTRY_POINT_METHOD_SIGNATURE(__methodName) void  __methodName()

/** Entry point for game. That must return the root entity */
CONFIG_ENTRY_POINT_METHOD_SIGNATURE(CONFIG_ENTRY_POINT_FUNCTION_NAME);


#endif //T3_CONFIG_PROJECT_H