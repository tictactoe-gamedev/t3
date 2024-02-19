# Welcome to t3

* [Introduction](#introduction)
* [Who is t3 for?](#who-is-t3-for)
* [Installation Instructions](#installation-instructions)

## Introduction
t3 is a Game Development Framework for people who want to build games with
C. It's goal is to enable you to develop games **easily**,but with a
**lower level control** compared to engines. Actually, it's first purpose
is improve your game development skills.

## Who is t3 for?
* You are ready to get your hands dirty.
* You need something simple and modular.
* You want a framework that doesn't need vodoo magic and ancient knowledge.
* You don't want to be forced to learn some companies strict rules to do things. This will be your 'thing'.
* You need damn clear documentation.

## Installation Instructions
* Clone the repository.
* If you have the prerequisites, go to `t3-build.c` file. Set your `ENGINE_ROOT` path there.
* Make sure `INCLUDE_DIRECTORIES` macro has correct paths for your environment.
* Make sure `LINKER` macro is appropriate for your environment.
* Go to your cmd / terminal / etc and inside project root type `cd`.  type `clang -o t3-build t3-build.c`
* run t3-build with .`/t3-build` or `t3-build.exe` . Your project build will be inside `ENGINE_ROOT/Build`

## What is next?
* Go to t3 [overview](overview.md) to start development.
