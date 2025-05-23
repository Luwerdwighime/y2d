#!/bin/sh
rm -rf build y2d
cmake -B build
cmake --build build -j8
mv build/y2d .
rm -rf build

