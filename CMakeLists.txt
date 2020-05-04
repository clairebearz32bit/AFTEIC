cmake_minimum_required(VERSION 3.16)
project(AFTEiC C)

set(CMAKE_C_STANDARD 99)

add_executable(AFTEiC afteic.c include.h src/ioutils.c lib/globals.h lib/ioutils.h src/display.c lib/display.h src/ioutils.c src/editor.c lib/editor.h)