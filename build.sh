#!/bin/bash

set -xe 

clang -Wall -Werror -o ray_app rayapp/ray_app.c -lraylib -I ./