#!/bin/bash
# build.sh - HM 类型推导系统构建脚本（Linux/macOS）

set -e

echo "═══════════════════════════════════════════════════════════════"
echo "  Building HM Type Inference System"
echo "═══════════════════════════════════════════════════════════════"

# 创建目录
mkdir -p build bin

# 编译选项
CC="gcc"
CFLAGS="-Wall -Wextra -std=c11 -g -I./include"

# 源文件列表
SRCS=(
    "src/type_utils.c"
    "src/env.c"
    "src/subst.c"
    "src/unify.c"
    "src/infer.c"
    "src/ast.c"
    "src/main.c"
)

# 编译每个源文件
echo "Compiling source files..."
for src in "${SRCS[@]}"; do
    obj="build/$(basename ${src%.c}.o)"
    echo "  $src -> $obj"
    $CC $CFLAGS -c -o "$obj" "$src"
done

# 链接
echo "Linking..."
$CC $CFLAGS -o bin/hm_infer build/*.o

echo ""
echo "═══════════════════════════════════════════════════════════════"
echo "  Build successful! Executable: bin/hm_infer"
echo "═══════════════════════════════════════════════════════════════"
echo ""
echo "Run with: ./bin/hm_infer"

# 可选：运行程序
if [ "$1" == "--run" ]; then
    echo ""
    ./bin/hm_infer
fi

