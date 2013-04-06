HOW TO:

### Windows ###

# setup #
1. install Windows SDK: http://msdn.microsoft.com/en-us/windows/bb980924
2. install Visual C++ 2010 Express: http://www.microsoft.com/express/Downloads/#2010-Visual-CPP

# editing #
3. do not modify the "LinkedMem" struct unless you want to use a different mumble-Link-plugin other than 1.2.0
4. do edit LinkAPI.cpp and LinkAPI.h

# compiling #
5. update make.bat to represent the SKD and VC installation directories
6.1 by default a dll is compiled (.lib file included)
6.2 (optional) to compile as static library:  add   /DLINKAPI_NO_DLL   to the cl.exe calls
7. run make.bat 
8. check the output if additional libraries (other than KERNEL32.DLL) are required 
9. check the output if all your imports are there
10. include required DLLs (by default non are required)

# testing (manually) #
11. use MumblePAHelper (http://mumble.dbclan.de/MumblePAHelper_VS2010.exe, https://github.com/mumble-voip/mumble-pahelper) to inspect the data written to LinkeMem
12. update tests\java\src\zsawyer\mumble\jna\LinkAPILibrary.java (I used JNAerator [https://code.google.com/p/jnaerator/] but there was quite some cleaning up to do)
13. upate and use ManualTester (tests/java/ManualTester) to load your library using JNA and have it submit data



### Linux ###

# setup #   
1. required for compiling 64-bit library on 32-bit system
    $ sudo ln -s /usr/lib64/libstdc++.so.6 /usr/lib64/libstdc++.so
    
# editing #
2. do not modify the "LinkedMem" struct unless you want to use a different mumble-Link-plugin other than 1.2.0
3. do edit LinkAPI.cpp and LinkAPI.h

# compiling #
4. might need to update the include path for 64-bit compiling 
5.1 by default a shared library is compiled
5.2 (optional) to compile as static library:  add   -DLINKAPI_NO_DLL   to the g++ calls and change the command line appropriately
6. run make.sh
7. check the output if all your imports are there

# testing (manually) #
11. use MumblePAHelper (https://github.com/mumble-voip/mumble-pahelper) to inspect the data written to LinkeMem
12. update tests\java\src\zsawyer\mumble\jna\LinkAPILibrary.java (I used JNAerator [https://code.google.com/p/jnaerator/] but there was quite some cleaning up to do)
13. upate and use ManualTester (tests/java/ManualTester) to load your library using JNA and have it submit data



### MAC OSX ###

# setup #
1. probably requires the Apple SDK
2. install g++ compiler

# editing #
4. do not modify the "LinkedMem" struct unless you want to use a different mumble-Link-plugin other than 1.2.0
4. do edit LinkAPI.cpp and LinkAPI.h

# compiling #
5.1 by default a dynamic library is compiled
5.2 (optional) to compile as static library:  add   -DLINKAPI_NO_DLL   to the g++ calls and change the command line appropriately
5. run make_osx.sh

# testing (manually) #
11. use MumblePAHelper (https://github.com/mumble-voip/mumble-pahelper) to inspect the data written to LinkeMem
12. update tests\java\src\zsawyer\mumble\jna\LinkAPILibrary.java (I used JNAerator [https://code.google.com/p/jnaerator/] but there was quite some cleaning up to do)
13. upate and use ManualTester (tests/java/ManualTester) to load your library using JNA and have it submit data
