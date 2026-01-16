# Makefile for HM Type Inference System
# Hindley-Milner 多态类型推导系统

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -I./include
LDFLAGS =

# 目录
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# 源文件
SRCS = $(SRC_DIR)/type_utils.c \
       $(SRC_DIR)/env.c \
       $(SRC_DIR)/subst.c \
       $(SRC_DIR)/unify.c \
       $(SRC_DIR)/infer.c \
       $(SRC_DIR)/ast.c \
       $(SRC_DIR)/main.c

# 目标文件
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# 最终可执行文件
TARGET = $(BIN_DIR)/hm_infer

# Flex/Bison 生成的文件
LEX_SRC = $(SRC_DIR)/lexer.l
YACC_SRC = $(SRC_DIR)/parser.y
LEX_OUT = $(BUILD_DIR)/lex.yy.c
YACC_OUT = $(BUILD_DIR)/parser.tab.c
YACC_HDR = $(BUILD_DIR)/parser.tab.h

# 默认目标
all: dirs $(TARGET)

# 创建目录
dirs:
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

# 链接
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 编译源文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# 生成词法分析器
$(LEX_OUT): $(LEX_SRC)
	flex -o $@ $<

# 生成语法分析器
$(YACC_OUT) $(YACC_HDR): $(YACC_SRC)
	bison -d -o $(YACC_OUT) $<

# 带解析器的完整构建
parser: dirs $(LEX_OUT) $(YACC_OUT)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/hm_parser \
		$(BUILD_DIR)/lex.yy.c \
		$(BUILD_DIR)/parser.tab.c \
		$(filter-out $(BUILD_DIR)/main.o,$(OBJS))

# 运行程序
run: $(TARGET)
	$(TARGET)

# 清理
clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)

# 简单编译（不使用 Makefile 目录结构）
simple:
	$(CC) $(CFLAGS) -o hm_infer.exe \
		$(SRC_DIR)/type_utils.c \
		$(SRC_DIR)/env.c \
		$(SRC_DIR)/subst.c \
		$(SRC_DIR)/unify.c \
		$(SRC_DIR)/infer.c \
		$(SRC_DIR)/ast.c \
		$(SRC_DIR)/main.c

.PHONY: all dirs clean run parser simple

