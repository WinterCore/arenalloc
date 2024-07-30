OS := $(shell uname)
CFLAGS = -std=c11 -Wall -Wextra

.PHONY: clean debug all


debug: CFLAGS += -ggdb -DDEBUG
debug: Arenalloc

SRC_TEST=$(shell find . -name "*test.c")
SRC_C=$(shell find . -name "*.c" ! -path "*test.c")
SRC_ALL=$(shell find . -name "*.c" -o -name "*.h" ! -path "*test.c")

release: CFLAGS += -DNDEBUG

TEST_SRC_C=$(shell find . -name "*.c" ! -path "*test.c" ! -path "*main.c")

$(basename $(SRC_TEST)): $(SRC_TEST) $(SRC_ALL)
	cc $(CFLAGS) -o $@ $(TEST_SRC_C) $(addsuffix .c,$@) $(LDFLAGS)

test: $(basename $(SRC_TEST))
	@for t in $(basename $(SRC_TEST)); do \
		$$t; \
	done
	@echo "Tests ran successfully"


Arenalloc: $(SRC_ALL)
	cc $(CFLAGS) -o Arenalloc $(SRC_C) $(LDFLAGS)

all: Arenalloc

clean:
	rm -rf Arenalloc ./src/*.o ./src/**/*.o ./src/**/*test ./*.dSYM
