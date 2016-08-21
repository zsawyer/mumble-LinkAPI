#!/bin/bash

# UNTESTED!!

#rm -R build
mkdir build
rm build/*.so

# 32 bit
g++  -o build/libLinkAPI.so -shared -fPIC \
     -Wl,-soname,build/libLinkAPI.so  \
     -fvisibility=hidden \
     -fvisibility-inlines-hidden \
     ../../src/LinkAPI.c \
     -lrt \
     -lstdc++


# 64 bit
g++  -o build/libLinkAPI64.so -m64 -shared -fPIC \
     -Wl,-soname,build/libLinkAPI64.so  \
     -fvisibility=hidden \
     -fvisibility-inlines-hidden \
     ../../src/LinkAPI.c \
     -lstdc++ \
     -m64 \
     -lrt


# for inspection of the library exports       
# 32 bit
nm -C -D build/libLinkAPI.so
# 64 bit
nm -C -D build/libLinkAPI64.so
