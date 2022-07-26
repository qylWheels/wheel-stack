
/**
 * 文件名：stack.c
 * 作者：秋叶零
 * 创建日期：2022年7月24日
 * 修改日期：2022年7月26日
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

#define T stack_T
typedef struct T *T;

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
    assert(_stack_check_uuid(stk));
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
    assert(_stack_check_uuid(stk));
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
    assert(_stack_check_uuid(stk));

    return stk->count == 0;
}

void stack_free(T *stk) {
    assert(stk != NULL);
    assert(_stack_check_uuid(stk));

    _stack_delete_uuid((*stk)->uuid);

    struct elem *prev = (*stk)->head, *next;
    while(prev->next != NULL) {
        next = prev->next;
        free(prev);
        prev = next;
    }
    free(prev);
    free(*stk);

    return;
}

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
        if(strcmp(p->uuid, uuid)) {
            return 1;
        }
        p = p->next;
    }

    return 0;
}

#undef T
