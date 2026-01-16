/**
 * subst.h - 替换（Substitution）操作
 */

#ifndef HM_SUBST_H
#define HM_SUBST_H

#include "types.h"

/*=============================================================
 * 替换操作
 *=============================================================*/

/**
 * 创建空替换
 */
Subst subst_empty(void);

/**
 * 创建单一替换 [α := τ]
 */
Subst subst_single(TVar tv, Type *t);

/**
 * 将替换应用到类型上
 * S(τ)
 */
Type* apply_subst_type(Subst *s, Type *t);

/**
 * 将替换应用到类型方案上
 * S(σ) - 注意不替换被量化的变量
 */
Scheme* apply_subst_scheme(Subst *s, Scheme *scheme);

/**
 * 将替换应用到环境上
 * S(Γ)
 */
Env apply_subst_env(Subst *s, Env env);

/**
 * 组合两个替换
 * compose(S2, S1) = S2 ∘ S1
 * 即先应用 S1，再应用 S2
 */
Subst subst_compose(Subst s2, Subst s1);

/**
 * 在替换中查找类型变量
 */
Type* subst_lookup(Subst *s, TVar tv);

/**
 * 打印替换
 */
void subst_print(Subst *s);

#endif // HM_SUBST_H

