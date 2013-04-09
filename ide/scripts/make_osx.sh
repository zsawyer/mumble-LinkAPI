#!/bin/bash


# 32 bit
#rm -R build
mkdir build

g++ -dynamiclib -Wl,-headerpad_max_install_names,-undefined,dynamic_lookup,-compatibility_version,1.0,-current_version,1.0,-install_name,/usr/local/lib/libLinkAPI.dylib \
    -o build/libLinkAPI.dylib \
    -m32 \
    ../../src/LinkAPI.cpp 



#--------------------------------------------------------------------------------


# 64 bit

g++ -dynamiclib -Wl,-headerpad_max_install_names,-undefined,dynamic_lookup,-compatibility_version,1.0,-current_version,1.0,-install_name,/usr/local/lib/libLinkAPI64.dylib \
    -o build/libLinkAPI64.dylib \
    -m64 \
    ../../src/LinkAPI.cpp 



