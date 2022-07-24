
/**
 * 文件名：stack.h
 * 作者：秋叶零
 * 日期：2022年7月24日
 */

#ifndef _STACK_H_
#define _STACK_H_

#define _MAX_UUID_LENGTH  256
#define _UUID_COUNT       32

// stack的数据结构
#define T stack_T
struct T {
    int count;
    int size;
    char uuid[_MAX_UUID_LENGTH];
    struct elem {
        void *x;
        struct elem *list;
    } *head;
};
typedef struct T *T;

// uuid列表（内部使用，不提供对外接口）
struct _UuidList {
    int count;
    int size;
    char **uuid;
} *_uuid_list = 0;

// 对外提供的接口
extern T    stack_new                   (int size);
extern void stack_push                  (T stk, void *x);
extern T    stack_pop                   (T stk);
extern int  stack_is_empty              (T stk);
extern void stack_free                  (T stk);

// 内部函数
extern void _stack_init_uuid_list       ();
extern int  _stack_check_uuid           (T stk, struct _UuidList *uuid_list);
extern void _stack_realloc_uuid_list    (struct _UuidList *uuid_list);
extern void _stack_free_uuid_list       (struct _UuidList *uuid_list);

#undef T
#endif
