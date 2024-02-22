#include <stdlib.h>
#include <stdio.h>

/*----- HELPERS -----*/
#define INCLUDE_DIRECTORY(arg)  " -I "arg
#define LINK(arg)  arg " "
#define SRC(arg) arg " "
#define FLAG_ENABLED(flag) flag " "
#define FLAG_DISABLED(flag)

/*----- BASE CONFIG -----*/
#if __linux__
#define EXECUTABLE_NAME                                     "t3"
#else
#define EXECUTABLE_NAME                                     "t3.exe"
#endif

/*----- PATHS -----*/
#define ENGINE_ROOT                                         "/media/kemal/TB1/Projects/CLionProjects/t3"
#define PROJECT_ROOT                                        ENGINE_ROOT "/project-root"
#define T3_CORE                                             ENGINE_ROOT "/core"
#define T3_CORE_SOURCE                                      T3_CORE "/source"
#define T3_ECS                                              T3_CORE_SOURCE "/ecs"
#define T3_ADT                                              T3_CORE_SOURCE "/adt"
#define T3_HELPERS                                          T3_CORE_SOURCE "/helpers"
#define T3_COMPONENTS                                       T3_ECS "/components"


#if __linux__
#define SDL_INCLUDE_DIRECTORY                               "/usr/include/SDL2"
#define SDL_IMAGE_INCLUDE_DIRECTORY                         "/usr/include/SDL2"
#else
#define SDL_INCLUDE_DIRECTORY                               "C:/SDL2/include"
#define SDL_INCLUDE_DIRECTORY                               "C:/SDL2_Image/include"
#endif

/*----- INCLUDES -----*/
#define INCLUDE_DIRECTORIES                                 INCLUDE_DIRECTORY(ENGINE_ROOT)                              \
                                                            INCLUDE_DIRECTORY(T3_CORE)                                  \
                                                            INCLUDE_DIRECTORY(SDL_INCLUDE_DIRECTORY)                    \
                                                            INCLUDE_DIRECTORY(SDL_IMAGE_INCLUDE_DIRECTORY)              \
                                                                                                                        \

#if __linux__
#define LINKER                                              LINK("-lSDL2")                                              \
                                                            LINK("-lSDL2_image")                                        \
                                                            LINK("-lm")                                                 \

#else
#define LINKER                                              LINK("-L C:/SDL2/lib/x64 -lSDL2")                           \
                                                            LINK("-L C:/SDL2_Image/lib/x64 -lSDL2_image")               \
                                                                                                                        
#endif


/*----- SOURCES -----*/
#define SOURCE_FILES                                        SRC(ENGINE_ROOT "/main.c")                                  \
                                                            SRC(T3_CORE_SOURCE "/t3-types.c")                           \
                                                            SRC(T3_CORE_SOURCE "/t3-math.c")                            \
                                                            SRC(T3_CORE_SOURCE "/globals.c")                            \
                                                            SRC(T3_CORE_SOURCE "/t3-input.c")                           \
                                                            SRC(T3_HELPERS "/logging.c")                                \
                                                            SRC(T3_HELPERS "/randomisation.c")                          \
                                                            SRC(T3_HELPERS "/t3-memory.c")                              \
                                                            SRC(T3_HELPERS "/sdl-rect-helper.c")                        \
                                                            SRC(T3_ADT "/linked_list.c")                                \
                                                            SRC(T3_ADT "/node.c")                                       \
                                                            SRC(T3_ADT "/list.c")                                       \
                                                            SRC(T3_ADT "/queue.c")                                      \
                                                            SRC(T3_ADT "/stack.c")                                      \
                                                            SRC(T3_ECS "/entity.c")                                     \
                                                            SRC(T3_ECS "/component.c")                                  \
                                                            SRC(T3_ECS "/game-loop.c")                                  \
                                                            SRC(T3_COMPONENTS "/position.c")                            \
                                                            SRC(T3_COMPONENTS "/rotation.c")                            \
                                                            SRC(T3_COMPONENTS "/scene.c")                               \
                                                            SRC(T3_COMPONENTS "/camera.c")                              \
                                                            SRC(T3_COMPONENTS "/texture.c")                             \
                                                            SRC(T3_COMPONENTS "/sprite.c")                              \
                                                            SRC(PROJECT_ROOT "/start.c")                                \


#define COMPILER_FLAGS                                      FLAG_ENABLED("-std=c89")                                    \
                                                            FLAG_ENABLED("-pedantic-errors")                            \
                                                            FLAG_ENABLED("-MJ compile_commands.json")                   \
                                                            FLAG_ENABLED("-Wall")                                       \
                                                            FLAG_ENABLED("-g")                                          \
                                                            FLAG_ENABLED("-O0")                                         \

#define RUN_FLAGS                                           FLAG_ENABLED("valgrind ")          \
                                                            FLAG_DISABLED("--memcheck:leak-check=full")                           \
                                                            FLAG_DISABLED("--tool=cachegrind")                           \
                                                            FLAG_ENABLED("--tool=callgrind")                            \
                                                            FLAG_ENABLED("--dump-instr=yes")                            \
                                                            FLAG_ENABLED("--simulate-cache=yes")                            \
                                                            FLAG_ENABLED("--collect-jumps=yes")                            \
                                                            FLAG_DISABLED("--tool=helgrind")                             \
                                                            FLAG_DISABLED("--tool=drd")                                  \
                                                            FLAG_DISABLED("--tool=massif")                               \
                                                            FLAG_DISABLED("--tool=dhat")                                 \
                                                            FLAG_DISABLED("--tool=lackey")                               \

int main(int argc, char *args[]) {

    /** Comment any options you don't want to apply */
    const char *cmd = "clang " COMPILER_FLAGS " "
                      INCLUDE_DIRECTORIES
                      " "
                      LINKER
                      " -o build/" EXECUTABLE_NAME
                      " " SOURCE_FILES;

    int compilationStatus = system(cmd);

    if (compilationStatus == 0) {
#ifdef __linux__
        system(RUN_FLAGS "./build/" EXECUTABLE_NAME);
#else
        system(".\\build\\" EXECUTABLE_NAME);
#endif
    }

    /**
     *  compile_commands.json helps us to use IDEs without CMAKE or any other build tool.
     *  compile_commands.json produced by clang has an extra , at the end and no [ ] so we're editing it. 
     */

    FILE *inputFile = fopen("compile_commands.json", "r");
    FILE *outputFile = fopen("compile_commands_tmp.json", "w+");

    fputc('[', outputFile);


    char current = fgetc(inputFile);
    int waiting = 0;
    while (current != EOF) {
        if (current == '}') {
            waiting = 1;
            fputc(current, outputFile);
        } else if (current == ',' && waiting == 1) {
            //skip without putting char   
        } else if (current == '{' && waiting == 1) {
            fputc(',', outputFile);
            fputc(current, outputFile);
            waiting = 0;
        } else {
            fputc(current, outputFile);
        }

        current = fgetc(inputFile);
    }

    fputc(']', outputFile);
    fclose(inputFile);
    remove("compile_commands.json");
    rename("compile_commands_tmp.json", "compile_commands.json");
    fclose(outputFile);

    return 0;
}