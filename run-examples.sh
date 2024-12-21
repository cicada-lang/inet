#!/usr/bin/env bash

app=inet
ext=inet

for example in $(find examples -name "*.${ext}" -not -name "*.test.${ext}" -not -name "*.error.${ext}" -not -name "*.play.${ext}"); do
    echo "[run] $example"
    ./bin/${app} run $example
done

for example in $(find examples -name "*.test.${ext}"); do
    echo "[test] $example"
    ./bin/${app} run $example > $example.out
done

for example in $(find examples -name "*.error.${ext}"); do
    echo "[error] $example"
    ./bin/${app} run $example 2> $example.err || true
done
