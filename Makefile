CXXFLAGS = -O3 -ffast-math
INCLUDE =  -I/usr/include -I./third-party
LIBS = -lm -lSDL2

bin/Accelerine: src/main.c src/game.c src/image.c
	gcc $^ -o $@ $(CXXFLAGS) $(INCLUDE) $(LIBS)