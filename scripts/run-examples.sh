#!/usr/bin/env bash

for example in $(find examples -name '*.test.inet'); do
    echo "[snapshot-test] $example"
    ./bin/inet run $example
done

for example in $(find examples -name '*.error.inet'); do
    echo "[snapshot-error] $example"
    ./bin/inet run $example || true
done
