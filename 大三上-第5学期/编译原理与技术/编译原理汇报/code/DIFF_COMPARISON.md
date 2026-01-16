# Python 与 C 语言实现的差异对比

## 概述

本文档说明 HM 多态类型推导系统（Algorithm W）在 Python 和 C 语言实现中的主要差异。
由于篇幅限制，汇报中只展示了 C 语言版本的代码。

## 一、核心差异对比

### 1. 类型系统表示

| 方面 | C 语言 | Python |
|------|--------|--------|
| 类型表示 | `struct Type` + `enum TypeKind` | 抽象基类 `Type` + 子类 |
| 类型变量 | `TVar` 结构体 | `TVar` dataclass |
| 多态方案 | `Scheme` 结构体 | `Scheme` dataclass |
| 替换 | `Subst` 结构体（数组） | `Subst` dataclass（字典） |
| 环境 | 链表 `EnvEntry*` | `Env` 类（字典） |

### 2. 内存管理

**C 语言**：需要手动管理内存
```c
Type* make_fun_type(Type *param, Type *result) {
    Type *t = (Type*)malloc(sizeof(Type));
    t->kind = T_FUN;
    t->left = param;
    t->right = result;
    return t;
}

void free_type(Type *t) {
    if (t == NULL) return;
    if (t->kind == T_FUN || t->kind == T_PAIR) {
        free_type(t->left);
        free_type(t->right);
    }
    free(t);
}
```

**Python**：自动垃圾回收
```python
@dataclass
class TFun(Type):
    param: Type
    result: Type
```

### 3. 模式匹配 / 类型判断

**C 语言**：switch-case + enum
```c
switch (expr->kind) {
    case EXPR_CONST_INT:
        return make_w_success(subst_empty(), make_type_int());
    case EXPR_VAR:
        ...
}
```

**Python**：isinstance 检查
```python
if isinstance(expr, ConstInt):
    return WResult(Subst.empty(), TInt())
elif isinstance(expr, Var):
    ...
```

### 4. 集合操作（自由变量计算）

**C 语言**：手动实现集合操作
```c
TVarSet tvarset_diff(TVarSet a, TVarSet b) {
    TVarSet result = { .count = 0 };
    for (int i = 0; i < a.count; i++) {
        if (!tvarset_contains(&b, a.vars[i])) {
            add_to_tvarset(&result, a.vars[i]);
        }
    }
    return result;
}
```

**Python**：使用内置集合
```python
def ftv(self) -> Set[int]:
    return self.body.ftv() - set(self.quantifiers)
```

### 5. 错误处理

**C 语言**：返回值 + 错误标志
```c
typedef struct {
    bool success;
    Subst subst;
    char *error_msg;
} UnifyResult;

if (!u.success) {
    free_type(alpha);
    return make_w_error(u.error_msg);
}
```

**Python**：异常处理
```python
class UnificationError(Exception):
    pass

try:
    s3 = unify(func_type, expected)
except UnificationError as e:
    raise TypeInferenceError(f"In application {expr}: {e}")
```

## 二、代码结构对比

| C 语言文件 | Python 文件 | 功能 |
|-----------|-------------|------|
| `types.h` | `hm_types.py` | 类型定义 |
| `type_utils.h/c` | `hm_types.py` | 类型操作 |
| `env.h/c` | `hm_types.py` | 环境操作 |
| `subst.h/c` | `hm_types.py` | 替换操作 |
| `unify.h/c` | `unify.py` | 合一算法 |
| `infer.h/c` | `infer.py` | Algorithm W |
| `ast.h/c` | `ast_nodes.py` | AST 定义 |
| `lexer.l` | - | 词法分析 |
| `parser.y` | - | 语法分析 |
| `main.c` | `main.py` | 演示程序 |

## 三、为什么汇报只展示 C 语言版本

1. **编译原理课程特性**：C 语言更接近编译器实际实现
2. **展示底层细节**：手动内存管理、显式类型、指针操作
3. **配套工具链**：Flex/Bison 词法语法分析
4. **与课程教材一致**：大多数编译原理教材使用 C/C++

## 四、Python 版本的优势

1. **代码简洁**：更少的样板代码
2. **类型提示**：Python 3 类型注解提高可读性
3. **快速原型**：适合实验和调试
4. **教学演示**：更容易理解算法本质

