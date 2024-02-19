#include <stdlib.h>

/*----- HELPERS -----*/
#define INCLUDE_DIRECTORY(arg)  " -I "arg
#define LINK(arg)  arg " "
#define SRC(arg) arg " "

/*----- BASE CONFIG -----*/
#define EXECUTABLE_NAME                                     "t3"

/*----- PATHS -----*/
#define ENGINE_ROOT                                         "/media/kemal/TB1/Projects/CLionProjects/t3"
#define PROJECT_ROOT                                        ENGINE_ROOT "/project-root"
#define T3_CORE                                             ENGINE_ROOT "/core"
#define T3_CORE_SOURCE                                      T3_CORE "/source"
#define T3_ECS                                              T3_CORE_SOURCE "/ecs"
#define T3_ADT                                              T3_CORE_SOURCE "/adt"
#define T3_HELPERS                                          T3_CORE_SOURCE "/helpers"
#define T3_COMPONENTS                                       T3_ECS "/components"

/*----- INCLUDES -----*/
#define INCLUDE_DIRECTORIES                                 INCLUDE_DIRECTORY(ENGINE_ROOT)                              \
                                                            INCLUDE_DIRECTORY(T3_CORE)                                  \

/*----- LINKER -----*/
#define LINKER                                              LINK("-lSDL2")                                              \
                                                            LINK("-lSDL2_image")                                        \
                                                                                                                        
#ifdef __linux__
#define LINKER_PLATFORM                                     LINK("-lm")
#else
#define LINKER_PLATFORM                                     
#endif

/*----- SOURCES -----*/
#define SOURCE_FILES                                        SRC(ENGINE_ROOT "/main.c")                                  \
                                                            SRC(T3_CORE_SOURCE "/t3-types.c")                           \
                                                            SRC(T3_CORE_SOURCE "/vector2.c")                            \
                                                            SRC(T3_CORE_SOURCE "/globals.c")                            \
                                                            SRC(T3_HELPERS "/logging.c")                                \
                                                            SRC(T3_HELPERS "/randomisation.c")                          \
                                                            SRC(T3_ADT "/linked_list.c")                                \
                                                            SRC(T3_ADT "/node.c")                                       \
                                                            SRC(T3_ADT "/list.c")                                       \
                                                            SRC(T3_ADT "/queue.c")                                      \
                                                            SRC(T3_ADT "/stack.c")                                      \
                                                            SRC(T3_ECS "/entity.c")                                     \
                                                            SRC(T3_ECS "/component.c")                                  \
                                                            SRC(T3_ECS "/game-loop.c")                                  \
                                                            SRC(T3_COMPONENTS "/position.c")                            \
                                                            SRC(T3_COMPONENTS "/scene.c")                               \
                                                            SRC(T3_COMPONENTS "/camera.c")                              \
                                                            SRC(T3_COMPONENTS "/texture.c")                             \
                                                            SRC(T3_COMPONENTS "/sprite.c")                              \
                                                            SRC(PROJECT_ROOT "/start.c")                                \


#define OPT_RUN_STATIC_ANALYZER                             "--analyze "
#define OPT_STATIC_ANALYZER_OUTPUT_FORMAT                   "--analyzer-output html "    //(html|plist|plist-multi-file|plist-html|sarif|sarif-html|text)


int main(int argc, char *args[]) {

    const char *sources = SOURCE_FILES;

    /** Comment any options you don't want to apply */
    const char *cmd = "clang "
                      INCLUDE_DIRECTORIES
                      " "
                      LINKER " " LINKER_PLATFORM
                      " -o " EXECUTABLE_NAME
                      " " SOURCE_FILES;

    int compilationStatus = system(cmd);

    if (compilationStatus == 0) {
#ifdef __linux__
        system("./" EXECUTABLE_NAME);
#else 
        system(EXECUTABLE_NAME ".exe");
#endif
    }

    return 0;
}