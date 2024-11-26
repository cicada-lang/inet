cc = gcc
ldflags = -lX11
cflags = -g -Wall -Wwrite-strings -Wextra -Werror -O0 -std=c99 -pedantic

src = $(shell find src -name '*.c')
headers = $(shell find src -name '*.h')
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

.PHONY: run-examples
run-examples: bin/inet
	bash run-examples.sh

bin/inet: $(lib) lib/inet.o
	mkdir -p $(dir $@); $(cc) $^ $(ldflags) -o $@

lib/%.o: src/%.c $(headers)
	mkdir -p $(dir $@); $(cc) -c $(cflags) $< -o $@

.PHONY: clean
clean:
	rm -rf lib bin
