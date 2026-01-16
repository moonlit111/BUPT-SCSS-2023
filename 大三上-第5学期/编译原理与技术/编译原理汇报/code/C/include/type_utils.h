/**
 * type_utils.h - 类型操作工具函数声明
 */

#ifndef HM_TYPE_UTILS_H
#define HM_TYPE_UTILS_H

#include "types.h"

/*=============================================================
 * 类型构造器 (Type Constructors)
 *=============================================================*/
Type* make_type_var(TVar tv);
Type* make_type_int(void);
Type* make_type_bool(void);
Type* make_fun_type(Type *param, Type *result);
Type* make_pair_type(Type *fst, Type *snd);

/*=============================================================
 * 类型变量生成
 *=============================================================*/
TVar fresh_tvar(void);
Type* fresh_type_var(void);
void reset_tvar_counter(void);

/*=============================================================
 * 类型复制与比较
 *=============================================================*/
Type* copy_type(Type *t);
bool tvar_equal(TVar a, TVar b);
bool type_equal(Type *a, Type *b);

/*=============================================================
 * 类型方案操作
 *=============================================================*/
Scheme* make_mono_scheme(Type *t);
Scheme* make_poly_scheme(int count, TVar *qvars, Type *body);
Scheme* copy_scheme(Scheme *s);
void free_scheme(Scheme *s);

/*=============================================================
 * 类型中自由变量操作
 *=============================================================*/
typedef struct {
    int count;
    TVar vars[MAX_SUBST_SIZE];
} TVarSet;

TVarSet ftv_type(Type *t);           // 类型中的自由类型变量
TVarSet ftv_scheme(Scheme *s);       // 类型方案中的自由类型变量
TVarSet ftv_env(Env env);            // 环境中的自由类型变量

TVarSet tvarset_union(TVarSet a, TVarSet b);
TVarSet tvarset_diff(TVarSet a, TVarSet b);
bool tvarset_contains(TVarSet *set, TVar tv);

/*=============================================================
 * 类型打印
 *=============================================================*/
void print_type(Type *t);
void print_scheme(Scheme *s);
void print_subst(Subst *s);
char* type_to_string(Type *t);

/*=============================================================
 * 内存管理
 *=============================================================*/
void free_type(Type *t);

#endif // HM_TYPE_UTILS_H

