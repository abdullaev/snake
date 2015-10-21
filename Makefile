CC=gcc
CFLAGS=
LDFLAGS=-std=gnu99
SOURCES=./src/main.c ./src/game.c ./src/interface.c ./src/utils.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=./out/snake.out

build: $(SOURCES) $(EXECUTABLE)
	
update-levels:
	cp -R ./res/levels ./out/res

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@