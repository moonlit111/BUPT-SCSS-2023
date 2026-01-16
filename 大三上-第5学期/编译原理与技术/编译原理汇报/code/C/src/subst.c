/**
 * subst.c - 替换操作实现
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/type_utils.h"
#include "../include/env.h"
#include "../include/subst.h"

Subst subst_empty(void) {
    Subst s = { .count = 0 };
    return s;
}

Subst subst_single(TVar tv, Type *t) {
    Subst s = { .count = 1 };
    s.vars[0] = tv;
    s.types[0] = copy_type(t);
    return s;
}

Type* subst_lookup(Subst *s, TVar tv) {
    for (int i = 0; i < s->count; i++) {
        if (tvar_equal(s->vars[i], tv)) {
            return s->types[i];
        }
    }
    return NULL;
}

Type* apply_subst_type(Subst *s, Type *t) {
    if (t == NULL) return NULL;
    
    switch (t->kind) {
        case T_VAR: {
            Type *found = subst_lookup(s, t->tvar);
            if (found != NULL) {
                return copy_type(found);
            }
            return copy_type(t);
        }
        case T_INT:
            return make_type_int();
        case T_BOOL:
            return make_type_bool();
        case T_FUN:
            return make_fun_type(
                apply_subst_type(s, t->left),
                apply_subst_type(s, t->right)
            );
        case T_PAIR:
            return make_pair_type(
                apply_subst_type(s, t->left),
                apply_subst_type(s, t->right)
            );
    }
    return NULL;
}

Scheme* apply_subst_scheme(Subst *s, Scheme *scheme) {
    if (scheme == NULL) return NULL;
    
    // 创建新替换，排除被量化的变量
    Subst filtered = { .count = 0 };
    for (int i = 0; i < s->count; i++) {
        bool is_quantified = false;
        for (int j = 0; j < scheme->quantifier_count; j++) {
            if (tvar_equal(s->vars[i], scheme->quantifiers[j])) {
                is_quantified = true;
                break;
            }
        }
        if (!is_quantified && filtered.count < MAX_SUBST_SIZE) {
            filtered.vars[filtered.count] = s->vars[i];
            filtered.types[filtered.count] = s->types[i];
            filtered.count++;
        }
    }
    
    Type *new_body = apply_subst_type(&filtered, scheme->body);
    Scheme *result = make_poly_scheme(scheme->quantifier_count, scheme->quantifiers, new_body);
    free_type(new_body);  // make_poly_scheme 会复制，所以释放原件
    return result;
}

Env apply_subst_env(Subst *s, Env env) {
    if (env == NULL) return NULL;
    
    EnvEntry *new_entry = (EnvEntry*)malloc(sizeof(EnvEntry));
    strncpy(new_entry->name, env->name, 63);
    new_entry->name[63] = '\0';
    new_entry->scheme = apply_subst_scheme(s, env->scheme);
    new_entry->next = apply_subst_env(s, env->next);
    
    return new_entry;
}

Subst subst_compose(Subst s2, Subst s1) {
    Subst result = { .count = 0 };
    
    // 首先添加 S2(S1) 的结果
    for (int i = 0; i < s1.count && result.count < MAX_SUBST_SIZE; i++) {
        result.vars[result.count] = s1.vars[i];
        result.types[result.count] = apply_subst_type(&s2, s1.types[i]);
        result.count++;
    }
    
    // 添加 S2 中不在 S1 域中的映射
    for (int i = 0; i < s2.count && result.count < MAX_SUBST_SIZE; i++) {
        bool in_s1 = false;
        for (int j = 0; j < s1.count; j++) {
            if (tvar_equal(s2.vars[i], s1.vars[j])) {
                in_s1 = true;
                break;
            }
        }
        if (!in_s1) {
            result.vars[result.count] = s2.vars[i];
            result.types[result.count] = copy_type(s2.types[i]);
            result.count++;
        }
    }
    
    return result;
}

void subst_print(Subst *s) {
    printf("Subst {");
    for (int i = 0; i < s->count; i++) {
        printf(" 't%d := ", s->vars[i].id);
        print_type(s->types[i]);
        if (i < s->count - 1) printf(",");
    }
    printf(" }\n");
}

