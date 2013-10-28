#!/bin/bash


# 32 bit
#rm -R build
mkdir build

# g++ -dynamiclib -Wl,-headerpad_max_install_names,-undefined,dynamic_lookup,-compatibility_version,1.0,-current_version,1.0,-install_name,/usr/local/lib/libLinkAPI32.dylib \
    # -o build/libLinkAPI32.dylib \
    # -m32 \
    # ../../src/LinkAPI.cpp 



#--------------------------------------------------------------------------------


# 64 bit

# g++ -dynamiclib -Wl,-headerpad_max_install_names,-undefined,dynamic_lookup,-compatibility_version,1.0,-current_version,1.0,-install_name,/usr/local/lib/libLinkAPI64.dylib \
    # -o build/libLinkAPI64.dylib \
    # -m64 \
    # ../../src/LinkAPI.cpp 


# create universal build (merge)

#lipo -create -output build_osx_universal/libLinkAPI.dylib build/libLinkAPI32.dylib build/libLinkAPI64.dylib


# create universal build (at once)
g++ \
    -arch ppc \
    -arch ppc64 \
    -arch i386 \
    -arch x86_64 \
    -dynamiclib \
      ../../src/LinkAPI.cpp \
    -o build/libLinkAPI.dylib \    
    -install_name libLinkAPI.dylib 

        
# check if it worked

lipo -info build/libLinkAPI.dylib
