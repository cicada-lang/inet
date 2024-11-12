cc = gcc
ldflags =
cflags = -g -Wall -Wwrite-strings -Wextra -Werror -O2 -std=c99 -pedantic

src = $(shell find src -name '*.c')
header = $(shell find src -name '*.h')
lib = $(patsubst src/%,lib/%,$(patsubst %.c,%.o,$(src)))
bin = bin/inet

.PHONY: all
all: bin/inet

.PHONY: run
run: bin/inet
	./bin/inet

.PHONY: test
test: bin/inet
	./bin/inet self-test # && ./bin/inet run tests/*

bin/inet: $(lib) lib/inet.o
	mkdir -p $(dir $@); $(cc) $(ldflags) $^ -o $@

lib/%.o: src/%.c $(header)
	mkdir -p $(dir $@); $(cc) -c $(cflags) $< -o $@

.PHONY: clean
clean:
	rm -f *.o
	rm -rf lib bin
