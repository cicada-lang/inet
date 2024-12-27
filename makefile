cc = gcc
ldflags = -lX11 -lm
cflags = -g -Wall -Wwrite-strings -Wextra -Werror -Wpedantic -O3 -std=c2x -D_POSIX_C_SOURCE=199309L

src = $(shell find src -name '*.c')
headers = $(shell find src -name '*.h')
lib = $(patsubst src/%,lib/%,$(patsubst %.c,%.o,$(src)))
app = inet-forth
bin = bin/$(app)

.PHONY: all
all: bin/$(app)

.PHONY: run
run: bin/$(app)
	./bin/$(app)

.PHONY: test
test: self-test run-examples

.PHONY: self-test
self-test: bin/$(app)
	./bin/$(app) self-test

.PHONY: run-examples
run-examples: bin/$(app)
	bash run-examples.sh

bin/$(app): $(lib) lib/$(app).o
	mkdir -p $(dir $@); $(cc) $^ $(ldflags) -o $@

lib/%.o: src/%.c $(headers)
	mkdir -p $(dir $@); $(cc) -c $(cflags) $< -o $@

.PHONY: clean
clean:
	rm -rf lib bin
