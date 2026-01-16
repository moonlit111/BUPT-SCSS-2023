/**
 * env.c - 类型环境操作实现
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/type_utils.h"
#include "../include/env.h"

Env env_empty(void) {
    return NULL;
}

Scheme* env_lookup(Env env, const char *name) {
    EnvEntry *entry = env;
    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            return entry->scheme;
        }
        entry = entry->next;
    }
    return NULL;
}

Env env_extend(Env env, const char *name, Scheme *scheme) {
    EnvEntry *entry = (EnvEntry*)malloc(sizeof(EnvEntry));
    strncpy(entry->name, name, 63);
    entry->name[63] = '\0';
    entry->scheme = copy_scheme(scheme);
    entry->next = env;  // 注意：这只是引用，不是复制
    return entry;
}

Env env_copy(Env env) {
    if (env == NULL) return NULL;

    EnvEntry *copy = (EnvEntry*)malloc(sizeof(EnvEntry));
    strncpy(copy->name, env->name, 63);
    copy->name[63] = '\0';
    copy->scheme = copy_scheme(env->scheme);
    copy->next = env_copy(env->next);
    return copy;
}

// 只释放一个环境节点（不释放 next 链）
void env_free_single(Env env) {
    if (env != NULL) {
        free_scheme(env->scheme);
        free(env);
    }
}

// 释放整个环境链（完全释放，用于最终清理）
void env_free(Env env) {
    while (env != NULL) {
        EnvEntry *next = env->next;
        free_scheme(env->scheme);
        free(env);
        env = next;
    }
}

void env_print(Env env) {
    printf("Environment {\n");
    EnvEntry *entry = env;
    while (entry != NULL) {
        printf("  %s : ", entry->name);
        print_scheme(entry->scheme);
        printf("\n");
        entry = entry->next;
    }
    printf("}\n");
}

