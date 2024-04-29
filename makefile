
splitsdl : splitsdl.c library.c libgfx.c
	cc splitsdl.c -O2 -pthread -lm -lrt -lSDL2 -lpng -o splitsdl




