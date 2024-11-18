cc = gcc
ldflags =
cflags = -g -Wall -Wwrite-strings -Wextra -Werror -O2 -std=c99 -pedantic

src = $(shell find src -name '*.c')
headers = $(shell find src -name '*.h')
examples = $(shell find examples -name '*.inet')
lib = $(patsubst src/%,lib/%,$(patsubst %.c,%.o,$(src)))
bin = bin/inet

.PHONY: all
all: bin/inet

.PHONY: run
run: bin/inet
	./bin/inet

.PHONY: test
test: self-test run-examples

.PHONY: self-test
self-test: bin/inet
	./bin/inet self-test

.PHONY: self-test
run-examples: bin/inet
	./bin/inet run $(examples)

bin/inet: $(lib) lib/inet.o
	mkdir -p $(dir $@); $(cc) $(ldflags) $^ -o $@

lib/%.o: src/%.c $(headers)
	mkdir -p $(dir $@); $(cc) -c $(cflags) $< -o $@

.PHONY: clean
clean:
	rm -rf lib bin
