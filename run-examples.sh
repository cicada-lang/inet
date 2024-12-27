#!/usr/bin/env bash

bin=./bin/inet-forth
ext=fth

for example in $(find examples -name "*.${ext}" -not -name "*.test.${ext}" -not -name "*.error.${ext}" -not -name "*.play.${ext}"); do
    echo "[run] $example"
    ${bin} run $example
done

for example in $(find examples -name "*.test.${ext}"); do
    echo "[test] $example"
    ${bin} run $example > $example.out
done

for example in $(find examples -name "*.error.${ext}"); do
    echo "[error] $example"
    ${bin} run $example 2> $example.err || true
done
