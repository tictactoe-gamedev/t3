# Welcome to t3

* [Introduction](#introduction)
* [Who is t3 for?](#who-is-t3-for)
* [Installation Instructions](#installation-instructions)

## Introduction
t3 is a Game Development Framework for people who want to build games with 
C and C++. Its goal is to enable you to develop games **easily**,but with a 
**lower level control** compared to engines. Actually, it's first purpose
is improve your game development skills. 

## Who is t3 for?
* You are ready to get your hands dirty. 
* You need something simple and modular. 
* You want a framework that doesn't need vodoo magic and ancient knowledge.
* You don't want to be forced to learn some companies strict rules to do things. This will be your 'thing'.
* You need damn clear documentation. 

## Linux Installation Instructions
* Clone the repository.
* Learn how you can install [SDL 2.28.5](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5) from  [Lazy Foo's SDL Tutorials](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)
* Learn how to install [SDL_image 2.8.1](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.8.1) from [Lazy Foo's SDL image Tutorials](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php)
* Change the `CMakeList.txt` at the root of the project. Make it work with your location of libraries and includes.
* Run the project. If you're able to see a 400x400 window, then you've made it.

## Windows Installation Instructions
* Clone the repository.
* Learn how you can install [SDL 2.28.5](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5) from  [Lazy Foo's SDL Tutorials](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)
* For MinGW compiler download the "SDL2-devel-2.28.5-mingw.zip" file and extract only the files in the "i686-w64-mingw32" folder in "your-root-folder-path/SDL_Build".
* Learn how to install [SDL_image 2.8.1](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.8.1) from [Lazy Foo's SDL image Tutorials](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php)
* For MinGW compiler download the "SDL2_image-devel-2.8.1-mingw.zip" file and extract only the files in the "i686-w64-mingw32" folder in "your-root-folder-path/SDL_Image_Build".
* Change the `CMakeList.txt` at the root of the project. Make it work with your location of libraries and includes.
* Run the project. If you're able to see a 400x400 window, then you've made it.

## What is next?
* Go to t3 [overview](overview.md) to start development.
