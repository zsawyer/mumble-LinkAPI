mumble-LinkAPI
==============

a generic interface (library) to provide positional audio information to mumble using the link plugin


The difference to a regular plugin is that instead of developing a native plugin and submitting it to mumble, one can use the provided library and call upon the native methods directly.

This is initially intended to work mainly for JNA (https://github.com/twall/jna) but is not limited to it. It should work with anything that is able to call native methods directly (i.e. BridJ, Scripts, AutoIt etc.), simply provide this library. 
Alternatively you can bake this library into your C-compatible code. 

For more information about the different data that can be committed see http://mumble.sourceforge.net/Link

Please review the [LinkAPI.h](https://github.com/zsawyer/mumble-LinkAPI/blob/master/src/LinkAPI.h) for a set of exported functions which can be called.
