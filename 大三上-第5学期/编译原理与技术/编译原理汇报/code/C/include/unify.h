/**
 * unify.h - 类型合一（Unification）
 */

#ifndef HM_UNIFY_H
#define HM_UNIFY_H

#include "types.h"

/*=============================================================
 * 合一结果
 *=============================================================*/
typedef struct {
    bool success;
    Subst subst;
    char *error_msg;
} UnifyResult;

/*=============================================================
 * 合一操作
 *=============================================================*/

/**
 * 合一两个类型
 * unify(τ1, τ2) 返回最一般合一子（MGU）S，使得 S(τ1) = S(τ2)
 * 
 * @param t1 第一个类型
 * @param t2 第二个类型
 * @return UnifyResult 包含成功标志和替换
 */
UnifyResult unify(Type *t1, Type *t2);

/**
 * 出现检查（Occurs Check）
 * 检查类型变量 α 是否出现在类型 τ 中
 * 用于防止无限类型如 α = α -> β
 */
bool occurs_check(TVar tv, Type *t);

#endif // HM_UNIFY_H

