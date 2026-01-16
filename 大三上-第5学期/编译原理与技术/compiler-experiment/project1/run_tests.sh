#!/bin/bash

for file in test/*; do
    filename=$(basename "$file")
    ./bin/bplc "$file" > "test/${filename}.out"
done