/**
 * infer.h - Algorithm W 类型推导
 */

#ifndef HM_INFER_H
#define HM_INFER_H

#include "types.h"

/*=============================================================
 * 泛化与实例化
 *=============================================================*/

/**
 * 泛化（Generalize）
 * generalize(Γ, τ) = ∀α1...αn. τ
 * 其中 {α1...αn} = ftv(τ) - ftv(Γ)
 * 
 * @param env 当前类型环境
 * @param t 要泛化的类型
 * @return 泛化后的类型方案
 */
Scheme* generalize(Env env, Type *t);

/**
 * 实例化（Instantiate）
 * instantiate(∀α1...αn. τ) = [α1 := β1, ..., αn := βn]τ
 * 其中 β1...βn 是新鲜的类型变量
 * 
 * @param scheme 类型方案
 * @return 实例化后的单态类型
 */
Type* instantiate(Scheme *scheme);

/*=============================================================
 * Algorithm W
 *=============================================================*/

/**
 * Algorithm W - HM 多态类型推导的核心算法
 * 
 * W(Γ, e) = (S, τ) 其中:
 *   - S 是在推导过程中产生的替换
 *   - τ 是推导出的类型
 * 
 * @param env 类型环境 Γ
 * @param expr 表达式 e
 * @return WResult 包含替换和类型
 */
WResult W(Env env, Expr *expr);

/**
 * 类型推导的高层接口
 * 从空环境开始推导表达式的类型
 */
WResult infer_type(Expr *expr);

/**
 * 带预定义环境的类型推导
 */
WResult infer_type_with_env(Env env, Expr *expr);

#endif // HM_INFER_H

