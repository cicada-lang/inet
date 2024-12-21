#!/usr/bin/env bash

app=./bin/inet
ext=inet

for example in $(find examples -name "*.${ext}" -not -name "*.test.${ext}" -not -name "*.error.${ext}" -not -name "*.play.${ext}"); do
    echo "[run] $example"
    ${app} run $example
done

for example in $(find examples -name "*.test.${ext}"); do
    echo "[test] $example"
    ${app} run $example > $example.out
done

for example in $(find examples -name "*.error.${ext}"); do
    echo "[error] $example"
    ${app} run $example 2> $example.err || true
done
