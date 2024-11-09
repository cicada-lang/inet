cc = clang
ldflags =
cflags = -g -Wall -Wwrite-strings -Wextra -Werror -O2 -std=c11 -pedantic

src = $(shell find src -name '*.c')
lib = $(patsubst src/%,lib/%,$(patsubst %.c,%.o,$(src)))
bin = bin/inet

.PHONY: all
all: bin/inet

.PHONY: run
run: bin/inet
	./bin/inet

.PHONY: test
test: bin/inet
	./bin/inet self-test #&& ./bin/inet run tests/*

bin/inet: $(lib) lib/inet.o
	mkdir -p $(dir $@); $(cc) $(ldflags) $^ -o $@

lib/%.o: src/%.c
	mkdir -p $(dir $@); $(cc) -c $(cflags) $< -o $@

.PHONY: clean
clean:
	rm -f *.o
	rm -rf lib bin
