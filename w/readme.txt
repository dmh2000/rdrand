HOW TO SETUP FOR WINDOWS

I have not yet mastered how to get the gyp bindings to work in windows. the main problem is to either assemble rdrand64.asm 
or include rdrand64.obj. 

So to set up in windows using the prebuilt module,
copy rdrand\w\build to rdrand\build. this will put the build\release\irand.node in the right place.

If you want to use the auto install with binding.gyp, look at the include binding.gyp.vs64. 
	move it to root of rdrand. 
	execute node-gyp configure 
	execute node-gyp build
	the build will fail with undefined references to rdrandx64 and rdrandx32
	from the command line, assemble rdrand64.asm using the 64 bit assembler >ml64 /c rdrand64.asm
	using visual studio, open build\binding.sln
	set the configuration to x64 build
	open the project properties
	to the linker -> input field, add ..\w\rdrand64.obj
	build again. should succeed