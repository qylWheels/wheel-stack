# wheel-stack
一个实现了栈的轮子

<br>

## **一、接口使用方法**
- **创建一个栈**
    - 函数原型：`stack_T stack_new(int size);`
    - 用例：
        ```C 
        //创建一个名为a的栈，大小为15
        stack_T a = stack_new(15); 
        ```
- **入栈操作**
    - 函数原型：`void stack_push(stack_T stk, void *x);`
    - 用例（承上）
        ```C
        int i = 114;
        int j = 514;
        stack_push(a, &i);  // 将i入栈
        stack_push(a, &j);  // 将j入栈
        ```
    - 注意：栈的实例必须由`new_stack()`函数生成，否则将触发断言。
    - 建议：一个栈中只存储同类型的数据。
<br></br>
- **出栈操作**
    - 函数原型：`void *stack_pop(stack_T stk);`
    - 用例（承上）
        ```C
        int m = *(int *)stack_pop(a);    // m = 514
        int n = *(int *)stack_pop(a);    // n = 114
        ```
    - 注意
        - `stack_pop()`函数返回的是`void *`，须进行强制类型转换。
        - 栈的实例必须由`new_stack()`函数生成，否则将触发断言。
<br></br>
- **判断栈是否为空**
    - 函数原型：`int stack_is_empty(stack_T stk);`
    - 用例（承上）
        ```C
        int empty = stack_is_empty(a);  // empty = 1
        ```
    - 注意：栈的实例必须由`new_stack()`函数生成，否则将触发断言。
<br></br>
- **清空栈**
    - 函数原型：`void stack_free(stack_T *stk);`
    - 用例（承上）
        ```C
        stack_free(&a);  // 栈a将不再可用
        ```
    - 注意：栈的实例必须由`new_stack()`函数生成，否则将触发断言。
<br></br>
## **二、缺陷**
- 让人难绷的语法` int m = *(int *)stack_pop(a);`
- 如果你将一个`int`类型入栈，但取出来时强制类型转换成了`double *`，程序也不会提醒你错了。目前还没找到合适的方法检查这一错误。
- 入和出的并不是数据本身，而是指向数据的指针。例如
    ```C
    int i = 1919;
    stack_push(a, &i);
    i = 810;
    printf("%d", *(int *)stack_pop(a));   // 输出的是810而不是1919
    ```
## **三、具体实现**
- 懒得写，自己看代码罢:P