#!/bin/bash

set -xe 

clang -Wall -Werror -g -O0 -o ray_app rayapp/ray_app.c -lraylib -I ./ -I ./rayapp

#emcc -o snake.html rayapp/ray_app.c -Os -Wall  -I. -I~/.bin/raylib/src -I~/.bin/raylib/src/external -lraylib -I ./ -I ./rayapp -L. -L~/.bin/raylib/src -L~/.bin/raylib/src/external -L/usr/local/include --shell-file ~/.bin/raylib/src/shell.html ~/.bin/raylib/libraylib.a -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB
#emcc -o game.html game.c -Os -Wall ./path-to/libraylib.a -I. -Ipath-to-raylib-h -L. -Lpath-to-libraylib-a -s USE_GLFW=3 -s ASYNCIFY --shell-file path-to/shell.html -DPLATFORM_WEB