#!/bin/bash

echo Build beginning...
gcc  -g -std=c99 main.c -o natah -lncurses -lrt -lutf8proc
echo Build complete!
