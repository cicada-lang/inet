#!/usr/bin/env bash

for example in $(find examples -name '*.inet' -not -name '*.test.inet' -not -name '*.error.inet'); do
    echo "[run] $example"
    ./bin/inet run $example
done

for example in $(find examples -name '*.test.inet'); do
    echo "[test] $example"
    ./bin/inet run $example > $example.out
done

for example in $(find examples -name '*.error.inet'); do
    echo "[error] $example"
    ./bin/inet run $example 2> $example.err || true
done
