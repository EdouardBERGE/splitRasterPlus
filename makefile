
splitsdl : splitsdl.c library.c libgfx.c
	cc splitsdl.c -DOS_LINUX -O2 -pthread -lm -lrt -lSDL2 -lpng -o splitsdl




