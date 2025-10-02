#!/usr/bin/env sh

bear -- gcc -o demo demo.c -O `GraphicsMagickWand-config --cppflags --ldflags --libs`
