
/**
 * 文件名：stack.c
 * 作者：秋叶零
 * 日期：2022年7月24日
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#define T stack_T

void _stack_init_uuid_list() {
    _uuid_list = (struct _UuidList *)malloc(sizeof(struct _UuidList));
    _uuid_list->count = 0;
    _uuid_list->size = _UUID_COUNT;
    _uuid_list->uuid = (char **)malloc(sizeof(char *) * _UUID_COUNT);
    return;
}

#undef T
