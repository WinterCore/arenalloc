OS := $(shell uname)
CFLAGS = -std=c11 -Wall -Wextra

.PHONY: clean debug all


debug: CFLAGS += -ggdb -DDEBUG
debug: Arenalloc

release: CFLAGS += -DNDEBUG

SRC_C=$(shell find . -name "*.c")
SRC_ALL=$(shell find . -name "*.c" -o -name '*.h')

Arenalloc: $(SRC)
	cc $(CFLAGS) -o Arenalloc $(SRC_C) $(LDFLAGS)

all: Arenalloc

clean:
	rm -rf Arenalloc ./src/*.o ./src/**/*.o
