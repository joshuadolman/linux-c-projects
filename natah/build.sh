#!/bin/bash

echo Build beginning...
gcc -std=c99 main.c -o natah -lncurses -lrt
echo Build complete!
