/**
 * env.h - 类型环境操作
 */

#ifndef HM_ENV_H
#define HM_ENV_H

#include "types.h"

/*=============================================================
 * 环境操作
 *=============================================================*/

/**
 * 创建空环境
 */
Env env_empty(void);

/**
 * 在环境中查找变量的类型方案
 * @param env 类型环境
 * @param name 变量名
 * @return 类型方案指针，未找到返回 NULL
 */
Scheme* env_lookup(Env env, const char *name);

/**
 * 扩展环境：添加新的变量绑定
 * @param env 原环境
 * @param name 变量名
 * @param scheme 类型方案
 * @return 新环境（不修改原环境）
 */
Env env_extend(Env env, const char *name, Scheme *scheme);

/**
 * 复制环境
 */
Env env_copy(Env env);

/**
 * 只释放一个环境节点（不释放 next 链）
 * 用于释放 env_extend 创建的节点
 */
void env_free_single(Env env);

/**
 * 释放整个环境链（完全释放）
 */
void env_free(Env env);

/**
 * 打印环境
 */
void env_print(Env env);

#endif // HM_ENV_H

