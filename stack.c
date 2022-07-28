
/**
 * 文件名：stack.c
 * 作者：秋叶零
 * 日期：2022年7月28日
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

// 内部函数声明
void _stack_add_uuid(const char *uuid);
void _stack_delete_uuid(const char *uuid);
int _stack_check_uuid(const char *uuid);

// 栈中的元素（内部使用，不提供对外接口）
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
} *_uuid_list_head = NULL;

T stack_new(int size) {
    assert(size > 0);

    T stk = (T)malloc(sizeof(struct stack_T));
    stk->count = 0;
    stk->size = size;
    stk->head = NULL;

    FILE *fp = fopen("/proc/sys/kernel/random/uuid", "r");
    fgets(stk->uuid, _MAX_UUID_LENGTH, fp);
    _stack_add_uuid(stk->uuid);

    fclose(fp);

    return stk;
}

void stack_push(T stk, void *x) {
    assert(stk != NULL);
    assert(x != NULL);
    assert(_stack_check_uuid(stk->uuid));
    assert(stk->count < stk->size);

    stk->count++;
    
    struct elem *new_elem = (struct elem *)malloc(sizeof(struct elem));
    new_elem->x = x;
    new_elem->next = stk->head;
    stk->head = new_elem;

    return;
}

void *stack_pop(T stk) {
    assert(stk != NULL);
    assert(_stack_check_uuid(stk->uuid));
    assert(stk->count > 0);

    stk->count--;

    struct elem *del = stk->head;
    void *x = del->x;
    stk->head = del->next;
    free(del);
    del = NULL;

    return x;
}

int stack_is_empty(T stk) {
    assert(stk != NULL);
    assert(_stack_check_uuid(stk->uuid));

    return stk->count == 0;
}

void stack_free(T *stk) {
    assert(stk != NULL);
    assert(_stack_check_uuid((*stk)->uuid));

    _stack_delete_uuid((*stk)->uuid);

    struct elem *prev = (*stk)->head, *next;
    if(prev == NULL) {
        return;
    }
    while(prev->next != NULL) {
        next = prev->next;
        free(prev);
        prev = next;
    }
    free(prev);
    free(*stk);

    return;
}

// 以下以“_”开头的函数均为内部函数，不提供对外接口，以隐藏细节
void _stack_add_uuid(const char *uuid) {
    assert(uuid != NULL);

    struct _UUIDList *new_uuid = (struct _UUIDList *)malloc(sizeof(struct _UUIDList));
    strncpy(new_uuid->uuid, uuid, _MAX_UUID_LENGTH);

    new_uuid->next = _uuid_list_head;
    _uuid_list_head = new_uuid;

    return;
}

void _stack_delete_uuid(const char *uuid) {
    assert(uuid != NULL);

    struct _UUIDList *prev, *del = _uuid_list_head;

    if(del == NULL) {
        return;
    }

    if(del->next == NULL) {
        free(del);
        _uuid_list_head = NULL;
    }

    while(del != NULL) {
        prev = del;
        del = del->next;
        if(del != NULL && strcmp(del->uuid, uuid)) {
            prev->next = del->next;
            free(del);
        }
    }

    return;
}

int _stack_check_uuid(const char *uuid) {
    assert(uuid != NULL);

    struct _UUIDList *p = _uuid_list_head;

    while(p != NULL) {
        if(strcmp(p->uuid, uuid) == 0) {
            return 1;
        }
        p = p->next;
    }

    return 0;
}

#undef T
