/**
 * type_utils.c - 类型操作工具函数实现
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/type_utils.h"

/*=============================================================
 * 全局类型变量计数器
 *=============================================================*/
static int tvar_counter = 0;

void reset_tvar_counter(void) {
    tvar_counter = 0;
}

TVar fresh_tvar(void) {
    TVar tv = { .id = tvar_counter++ };
    return tv;
}

Type* fresh_type_var(void) {
    return make_type_var(fresh_tvar());
}

/*=============================================================
 * 类型构造器
 *=============================================================*/
Type* make_type_var(TVar tv) {
    Type *t = (Type*)malloc(sizeof(Type));
    t->kind = T_VAR;
    t->tvar = tv;
    return t;
}

Type* make_type_int(void) {
    Type *t = (Type*)malloc(sizeof(Type));
    t->kind = T_INT;
    return t;
}

Type* make_type_bool(void) {
    Type *t = (Type*)malloc(sizeof(Type));
    t->kind = T_BOOL;
    return t;
}

Type* make_fun_type(Type *param, Type *result) {
    Type *t = (Type*)malloc(sizeof(Type));
    t->kind = T_FUN;
    t->left = param;
    t->right = result;
    return t;
}

Type* make_pair_type(Type *fst, Type *snd) {
    Type *t = (Type*)malloc(sizeof(Type));
    t->kind = T_PAIR;
    t->left = fst;
    t->right = snd;
    return t;
}

/*=============================================================
 * 类型复制
 *=============================================================*/
Type* copy_type(Type *t) {
    if (t == NULL) return NULL;

    Type *copy = (Type*)malloc(sizeof(Type));
    copy->kind = t->kind;

    switch (t->kind) {
        case T_VAR:
            copy->tvar = t->tvar;
            break;
        case T_INT:
        case T_BOOL:
            break;
        case T_FUN:
        case T_PAIR:
            copy->left = copy_type(t->left);
            copy->right = copy_type(t->right);
            break;
    }
    return copy;
}

bool tvar_equal(TVar a, TVar b) {
    return a.id == b.id;
}

bool type_equal(Type *a, Type *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (a->kind != b->kind) return false;

    switch (a->kind) {
        case T_VAR:
            return tvar_equal(a->tvar, b->tvar);
        case T_INT:
        case T_BOOL:
            return true;
        case T_FUN:
        case T_PAIR:
            return type_equal(a->left, b->left) &&
                   type_equal(a->right, b->right);
    }
    return false;
}

/*=============================================================
 * 类型方案操作
 *=============================================================*/
Scheme* make_mono_scheme(Type *t) {
    Scheme *s = (Scheme*)malloc(sizeof(Scheme));
    s->quantifier_count = 0;
    s->body = copy_type(t);
    return s;
}

Scheme* make_poly_scheme(int count, TVar *qvars, Type *body) {
    Scheme *s = (Scheme*)malloc(sizeof(Scheme));
    s->quantifier_count = count;
    for (int i = 0; i < count && i < MAX_QUANTIFIERS; i++) {
        s->quantifiers[i] = qvars[i];
    }
    s->body = copy_type(body);
    return s;
}

Scheme* copy_scheme(Scheme *s) {
    if (s == NULL) return NULL;
    return make_poly_scheme(s->quantifier_count, s->quantifiers, s->body);
}

void free_scheme(Scheme *s) {
    if (s) {
        free_type(s->body);
        free(s);
    }
}

/*=============================================================
 * 自由类型变量操作
 *=============================================================*/
static void add_to_tvarset(TVarSet *set, TVar tv) {
    for (int i = 0; i < set->count; i++) {
        if (tvar_equal(set->vars[i], tv)) return;
    }
    if (set->count < MAX_SUBST_SIZE) {
        set->vars[set->count++] = tv;
    }
}

bool tvarset_contains(TVarSet *set, TVar tv) {
    for (int i = 0; i < set->count; i++) {
        if (tvar_equal(set->vars[i], tv)) return true;
    }
    return false;
}

TVarSet tvarset_union(TVarSet a, TVarSet b) {
    TVarSet result = a;
    for (int i = 0; i < b.count; i++) {
        add_to_tvarset(&result, b.vars[i]);
    }
    return result;
}

TVarSet tvarset_diff(TVarSet a, TVarSet b) {
    TVarSet result = { .count = 0 };
    for (int i = 0; i < a.count; i++) {
        if (!tvarset_contains(&b, a.vars[i])) {
            add_to_tvarset(&result, a.vars[i]);
        }
    }
    return result;
}

TVarSet ftv_type(Type *t) {
    TVarSet set = { .count = 0 };
    if (t == NULL) return set;

    switch (t->kind) {
        case T_VAR:
            add_to_tvarset(&set, t->tvar);
            break;
        case T_INT:
        case T_BOOL:
            break;
        case T_FUN:
        case T_PAIR: {
            TVarSet left_ftv = ftv_type(t->left);
            TVarSet right_ftv = ftv_type(t->right);
            set = tvarset_union(left_ftv, right_ftv);
            break;
        }
    }
    return set;
}

TVarSet ftv_scheme(Scheme *s) {
    TVarSet set = { .count = 0 };
    if (s == NULL) return set;

    TVarSet body_ftv = ftv_type(s->body);
    // 减去被量化的变量
    TVarSet quantified = { .count = s->quantifier_count };
    for (int i = 0; i < s->quantifier_count; i++) {
        quantified.vars[i] = s->quantifiers[i];
    }
    return tvarset_diff(body_ftv, quantified);
}

TVarSet ftv_env(Env env) {
    TVarSet set = { .count = 0 };
    EnvEntry *entry = env;
    while (entry != NULL) {
        TVarSet scheme_ftv = ftv_scheme(entry->scheme);
        set = tvarset_union(set, scheme_ftv);
        entry = entry->next;
    }
    return set;
}


/*=============================================================
 * 类型打印
 *=============================================================*/
static char* tvar_to_name(int id) {
    static char buf[16];
    if (id < 26) {
        buf[0] = '\'';
        buf[1] = 'a' + id;
        buf[2] = '\0';
    } else {
        sprintf(buf, "'t%d", id);
    }
    return buf;
}

static void type_to_string_helper(Type *t, char *buf, int *pos, int max_len) {
    if (t == NULL || *pos >= max_len - 1) {
        if (*pos < max_len) buf[*pos] = '\0';
        return;
    }

    switch (t->kind) {
        case T_VAR: {
            char *name = tvar_to_name(t->tvar.id);
            int len = strlen(name);
            if (*pos + len < max_len) {
                strcpy(buf + *pos, name);
                *pos += len;
            }
            break;
        }
        case T_INT:
            if (*pos + 3 < max_len) {
                strcpy(buf + *pos, "Int");
                *pos += 3;
            }
            break;
        case T_BOOL:
            if (*pos + 4 < max_len) {
                strcpy(buf + *pos, "Bool");
                *pos += 4;
            }
            break;
        case T_FUN:
            if (t->left != NULL && t->left->kind == T_FUN) {
                buf[(*pos)++] = '(';
                type_to_string_helper(t->left, buf, pos, max_len);
                buf[(*pos)++] = ')';
            } else {
                type_to_string_helper(t->left, buf, pos, max_len);
            }
            if (*pos + 4 < max_len) {
                strcpy(buf + *pos, " -> ");
                *pos += 4;
            }
            type_to_string_helper(t->right, buf, pos, max_len);
            break;
        case T_PAIR:
            buf[(*pos)++] = '(';
            type_to_string_helper(t->left, buf, pos, max_len);
            if (*pos + 3 < max_len) {
                strcpy(buf + *pos, ", ");
                *pos += 2;
            }
            type_to_string_helper(t->right, buf, pos, max_len);
            buf[(*pos)++] = ')';
            break;
    }
    buf[*pos] = '\0';
}

char* type_to_string(Type *t) {
    static char buf[256];
    int pos = 0;
    type_to_string_helper(t, buf, &pos, 256);
    return buf;
}

void print_type(Type *t) {
    printf("%s", type_to_string(t));
}

void print_scheme(Scheme *s) {
    if (s == NULL) {
        printf("(null scheme)");
        return;
    }
    if (s->quantifier_count > 0) {
        printf("forall ");
        for (int i = 0; i < s->quantifier_count; i++) {
            printf("%s", tvar_to_name(s->quantifiers[i].id));
            if (i < s->quantifier_count - 1) printf(" ");
        }
        printf(". ");
    }
    print_type(s->body);
}

/*=============================================================
 * 内存管理
 *=============================================================*/
void free_type(Type *t) {
    if (t == NULL) return;
    if (t->kind == T_FUN || t->kind == T_PAIR) {
        free_type(t->left);
        free_type(t->right);
    }
    free(t);
}

