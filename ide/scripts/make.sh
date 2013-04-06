#!/bin/bash

# UNTESTED!!

# 32 bit
rm -R build
mkdir build

g++  -o build/libLinkAPI.so -shared \
     -Wl,-soname,build/libLinkAPI.so  \
     -lrt \
     -fvisibility=hidden
     -fvisibility-inlines-hidden
     ../../LinkAPI.cpp \
        -lstdc++

# 64 bit

g++  -o build/libLinkAPI64.so -m64 -shared -fPIC \
     -Wl,-soname,build/libLinkAPI64.so  \
     -lrt \
     -fvisibility=hidden
     -fvisibility-inlines-hidden
     ../../LinkAPI.cpp \
       -lstdc++ \
       -m64 \
       -I/usr/include/c++/4.4/i686-linux-gnu


# for inspection of the library exports       
# 32 bit
nm -C -D libLinkAPI.so
# 64 bit
nm -C -D libLinkAPI64.so