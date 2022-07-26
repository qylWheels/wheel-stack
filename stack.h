
/**
 * 文件名：stack.h
 * 作者：秋叶零
 * 创建日期：2022年7月24日
 * 修改日期：2022年7月26日
 */

#ifndef _STACK_H_
#define _STACK_H_

#define _MAX_UUID_LENGTH  256

// 栈中的元素
struct elem {
    void *x;
    struct elem *next;
};

// stack的数据结构
#define T stack_T
struct T {
    int count;				// 栈中元素个数
    int size;				// 栈的大小
    char uuid[_MAX_UUID_LENGTH];	// 栈的唯一标识符
    struct elem *head;			// 栈底元素
};
typedef struct T *T;

// uuid列表（内部使用，不提供对外接口）
struct _UUIDList {
    char uuid[_MAX_UUID_LENGTH];
    struct _UUIDList *next;
} *_uuid_list_head = (struct _UUIDList *)0;

// 对外提供的接口
extern T     stack_new       (int size);
extern void  stack_push      (T stk, void *x);
extern void *stack_pop       (T stk);
extern int   stack_is_empty  (T stk);
extern void  stack_free      (T *stk);

// 内部函数
extern void _stack_add_uuid     (const char *uuid);
extern void _stack_delete_uuid  (const char *uuid);
extern int _stack_check_uuid    (const char *uuid);

#undef T
#endif // _STACK_H_
