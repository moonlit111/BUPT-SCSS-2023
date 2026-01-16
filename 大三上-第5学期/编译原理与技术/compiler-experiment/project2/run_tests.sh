#!/bin/bash

# 遍历 test 文件夹中的所有文件
for file in test/*; do
    # 检查文件是否以 .bpl 结尾
    if [[ "$file" == *.bpl ]]; then
        filename=$(basename "$file" .bpl)
        ./bin/bplc "$file" > "test/${filename}.out"
    fi
done
