#!/usr/bin/env bash

for example in $(find examples -name '*.inet'); do
    ./bin/inet run $example
done
