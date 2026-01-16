# HM 多态类型推导系统演示指南

## 一、项目结构

```
code/
├── C/                          # C 语言实现
│   ├── include/                # 头文件
│   │   ├── types.h             # 类型定义
│   │   ├── type_utils.h        # 类型工具函数
│   │   ├── env.h               # 环境操作
│   │   ├── subst.h             # 替换操作
│   │   ├── unify.h             # 合一算法
│   │   ├── infer.h             # Algorithm W
│   │   └── ast.h               # AST 定义
│   ├── src/                    # 源文件
│   │   ├── type_utils.c
│   │   ├── env.c
│   │   ├── subst.c
│   │   ├── unify.c
│   │   ├── infer.c
│   │   ├── ast.c
│   │   ├── main.c              # 演示主程序
│   │   ├── lexer.l             # Flex 词法分析器
│   │   └── parser.y            # Bison 语法分析器
│   ├── build.sh                # Linux 构建脚本
│   ├── build.bat               # Windows 构建脚本
│   └── Makefile
├── Python/                     # Python 实现
│   ├── hm_types.py             # 类型定义
│   ├── ast_nodes.py            # AST 节点
│   ├── unify.py                # 合一算法
│   ├── infer.py                # Algorithm W
│   └── main.py                 # 演示主程序
├── DIFF_COMPARISON.md          # C/Python 差异对比
└── DEMO.md                     # 本文件
```

---

## 二、C 语言版本演示

### 2.1 环境要求

- GCC 编译器（支持 C11 标准）
- Linux / macOS / WSL

### 2.2 编译步骤

```bash
# 步骤 1：进入 C 目录
cd C

# 步骤 2：编译（选择其一）

# 方法一：使用构建脚本
chmod +x build.sh
./build.sh

# 方法二：直接使用 gcc
gcc -Wall -Wextra -std=c11 -g -I./include -o hm_infer \
    src/type_utils.c \
    src/env.c \
    src/subst.c \
    src/unify.c \
    src/infer.c \
    src/ast.c \
    src/main.c
```

### 2.3 运行程序

```bash
# 如果使用 build.sh
./bin/hm_infer

# 如果直接 gcc 编译
./hm_infer
```

### 2.4 预期输出

```
╔═══════════════════════════════════════════════════════════════╗
║     Hindley-Milner 多态类型推导系统 (Algorithm W)              ║
║     Polymorphic Type Inference with SDT                       ║
╚═══════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════
  示例一：恒等函数 (Identity Function)
═══════════════════════════════════════════════════════════════
源代码: let id = λx. x in id
期望类型: 'a -> 'a (多态恒等函数)

【let id = λx.x in id】
Expression: (let id = (λx. x) in id)
AST:
LET id =
  LAMBDA x =>
    VAR(x)
IN
  VAR(id)

✓ Type inference succeeded!
  Inferred type: 'a -> 'a

═══════════════════════════════════════════════════════════════
  示例二：K 组合子 (Const Function)
═══════════════════════════════════════════════════════════════
源代码: let const = λx. λy. x in const
期望类型: 'a -> 'b -> 'a (K combinator)

【let const = λx.λy.x in const】
Expression: (let const = (λx. (λy. x)) in const)

✓ Type inference succeeded!
  Inferred type: 'a -> 'b -> 'a

═══════════════════════════════════════════════════════════════
  示例三：多态应用 (Polymorphic Application)
═══════════════════════════════════════════════════════════════
源代码: let id = λx. x in (id 5, id true)
期望类型: (Int, Bool)

注意：单态类型系统会在此失败（Int = Bool 冲突）
      HM 多态系统通过实例化避免类型污染

【let id = λx.x in (id 5, id true)】
Expression: (let id = (λx. x) in ((id 5), (id true)))

✓ Type inference succeeded!
  Inferred type: (Int, Bool)

═══════════════════════════════════════════════════════════════
  演示完成！
═══════════════════════════════════════════════════════════════
```

---

## 三、Python 版本演示

### 3.1 环境要求

- Python 3.7+

### 3.2 运行步骤

```bash
# 步骤 1：进入 Python 目录
cd Python

# 步骤 2：运行主程序
python3 main.py
```

### 3.3 预期输出

与 C 版本类似，会显示三个示例的类型推导结果。

---

## 四、三个示例解读

| 示例 | 表达式 | 推导类型 | 说明 |
|:----:|--------|----------|------|
| 1 | `let id = λx.x in id` | `'a -> 'a` | 恒等函数，多态 |
| 2 | `let const = λx.λy.x in const` | `'a -> 'b -> 'a` | K 组合子 |
| 3 | `let id = λx.x in (id 5, id true)` | `(Int, Bool)` | **多态关键证明** |

### 示例三的重要性

```
单态系统：
  id 5    → id : Int -> Int
  id true → 错误！Int ≠ Bool

HM 多态系统：
  泛化：   id : ∀α. α -> α
  id 5    → 实例化为 β -> β，β = Int，返回 Int
  id true → 实例化为 γ -> γ，γ = Bool，返回 Bool
  结果：   (Int, Bool) ✓
```

---

## 五、调试方法

如果程序崩溃，使用 GDB 调试：

```bash
# 编译带调试信息
gcc -Wall -Wextra -std=c11 -g -I./include -o hm_infer src/*.c

# GDB 调试
gdb ./hm_infer
(gdb) run
(gdb) bt        # 崩溃时查看调用栈
(gdb) quit
```

