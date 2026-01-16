/**
 * types.h - HM 多态类型推导系统的类型定义
 * Hindley-Milner Type Inference System
 */

#ifndef HM_TYPES_H
#define HM_TYPES_H

#include <stdbool.h>

/*=============================================================
 * 类型变量 (Type Variable)
 *=============================================================*/
typedef struct {
    int id;           // 类型变量唯一标识符
} TVar;

/*=============================================================
 * 类型 (Type / Monotype τ)
 *=============================================================*/
typedef enum {
    T_VAR,            // 类型变量 α, β, ...
    T_INT,            // Int
    T_BOOL,           // Bool
    T_FUN,            // 函数类型 τ1 -> τ2
    T_PAIR            // 二元组类型 (τ1, τ2)
} TypeKind;

typedef struct Type {
    TypeKind kind;
    union {
        TVar tvar;                    // T_VAR
        struct {                      // T_FUN / T_PAIR
            struct Type *left;        // 参数/第一元素
            struct Type *right;       // 返回值/第二元素
        };
    };
} Type;

/*=============================================================
 * 多态类型方案 (Polytype / Type Scheme σ)
 * σ = ∀α1...αn. τ
 *=============================================================*/
#define MAX_QUANTIFIERS 16

typedef struct {
    int quantifier_count;             // 量化变量个数
    TVar quantifiers[MAX_QUANTIFIERS];// 量化的类型变量
    Type *body;                       // 类型体 τ
} Scheme;

/*=============================================================
 * 替换 (Substitution S: TVar -> Type)
 *=============================================================*/
#define MAX_SUBST_SIZE 64

typedef struct {
    int count;
    TVar vars[MAX_SUBST_SIZE];
    Type *types[MAX_SUBST_SIZE];
} Subst;

/*=============================================================
 * 类型环境 (Type Environment Γ)
 * Γ: VarName -> Scheme
 *=============================================================*/
typedef struct EnvEntry {
    char name[64];                    // 变量名
    Scheme *scheme;                   // 类型方案
    struct EnvEntry *next;
} EnvEntry;

typedef EnvEntry* Env;

/*=============================================================
 * 表达式 AST (Expression)
 *=============================================================*/
typedef enum {
    EXPR_CONST_INT,      // 整数常量
    EXPR_CONST_BOOL,     // 布尔常量
    EXPR_VAR,            // 变量 x
    EXPR_LAMBDA,         // λx. e
    EXPR_APP,            // e1 e2
    EXPR_LET,            // let x = e1 in e2
    EXPR_PAIR            // (e1, e2)
} ExprKind;

typedef struct Expr {
    ExprKind kind;
    union {
        int int_val;                  // EXPR_CONST_INT
        bool bool_val;                // EXPR_CONST_BOOL
        char *var_name;               // EXPR_VAR
        struct {                      // EXPR_LAMBDA
            char *param_name;
            struct Expr *body;
        } lambda;
        struct {                      // EXPR_APP
            struct Expr *func;
            struct Expr *arg;
        } app;
        struct {                      // EXPR_LET
            char *let_name;
            struct Expr *bind_expr;
            struct Expr *let_body;
        } let;
        struct {                      // EXPR_PAIR
            struct Expr *fst;
            struct Expr *snd;
        } pair;
    };
} Expr;

/*=============================================================
 * Algorithm W 返回结果
 *=============================================================*/
typedef struct {
    Subst subst;        // 替换 S
    Type *type;         // 推导出的类型 τ
    bool success;       // 是否成功
    char *error_msg;    // 错误信息
} WResult;

#endif // HM_TYPES_H

