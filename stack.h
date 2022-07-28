
/**
 * 文件名：stack.h
 * 作者：秋叶零
 * 日期：2022年7月28日
 */

#ifndef _STACK_H_
#define _STACK_H_

#define _MAX_UUID_LENGTH  256

// stack的数据结构（仅声明，不实现，隐藏细节）
#define T stack_T
struct T;
typedef struct T *T;

// 对外提供的接口
extern T     stack_new       (int size);
extern void  stack_push      (T stk, void *x);
extern void *stack_pop       (T stk);
extern int   stack_is_empty  (T stk);
extern void  stack_free      (T *stk);

#undef T
#endif // _STACK_H_
