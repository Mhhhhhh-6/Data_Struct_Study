/**
 * ===========================================================================
 * 文件名: test2.c
 * 描述:   顺序栈的动态内存实现
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了使用动态内存分配的顺序栈，包括：
 *   1. 栈的初始化（动态分配内存）
 *   2. 判断栈空
 *   3. 进栈（Push）操作
 *   4. 出栈（Pop）操作
 *   5. 获取栈顶元素
 *
 * 与test1.c的区别:
 *   test1.c: 使用静态分配的栈结构，Stack作为变量直接使用
 *   test2.c: 使用动态分配的栈结构，Stack作为指针使用
 *
 * 动态分配的优势:
 *   - 更灵活的内存管理
 *   - 可以在运行时动态调整栈的大小（本例固定为MAXSIZE）
 *   - 适合需要多个栈实例的场景
 *   - 可以方便地在函数间传递栈指针
 *
 * 注意事项:
 *   - 必须手动释放分配的内存，避免内存泄漏
 *   - 需要检查malloc是否成功
 *
 * 使用方法:
 *   编译: gcc test2.c -o test2
 *   运行: ./test2 (Linux/Mac) 或 test2.exe (Windows)
 *
 * 难度: ⭐⭐（基础数据结构 + 动态内存管理）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 栈的最大容量
#define MAXSIZE 100

// 栈元素类型定义
typedef int ElemType;

/**
 * 顺序栈结构定义（动态内存版本）
 *
 * 成员说明:
 *   - data: 指向动态分配的数组的指针
 *   - top: 栈顶指针，指示栈顶元素的位置
 *
 * 与test1.c中的Stack结构对比:
 *   test1.c: ElemType data[MAXSIZE]; (静态数组)
 *   test2.c: ElemType *data;          (动态数组指针)
 *
 * 内存布局:
 *   Stack结构本身: malloc分配
 *   data数组:      malloc分配
 */
typedef struct{
    ElemType *data;  // 指向动态分配的栈数组
    int top;         // 栈顶指针（-1表示空栈）
}Stack;

/**
 * 函数: initStack
 * 功能: 初始化顺序栈（动态分配内存）
 *
 * 参数: 无
 *
 * 返回值: 返回指向新创建的栈结构的指针
 *
 * 算法思路:
 *   1. 为Stack结构分配内存
 *   2. 为data数组分配MAXSIZE个元素的内存
 *   3. 将栈顶指针top设置为-1
 *   4. 返回栈指针
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(MAXSIZE) - 需要分配数组空间
 *
 * 注意事项:
 *   - 需要两次malloc：一次为Stack结构，一次为data数组
 *   - 实际应用中应检查malloc是否成功
 *   - 使用完毕后需要释放两次：data数组和Stack结构
 *
 * 改进建议:
 *   应添加错误检查:
 *   if (s == NULL || s->data == NULL) {
 *       return NULL;
 *   }
 */
Stack* initStack(void){
    // 为Stack结构分配内存
    Stack *s = (Stack*)malloc(sizeof(Stack));

    // 为data数组分配内存（MAXSIZE个元素）
    s->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);

    // 栈顶指针设置为-1，表示空栈
    s->top = -1;

    return s;
}

/**
 * 函数: isEmpty
 * 功能: 判断栈是否为空
 *
 * 参数:
 *   @param s - 指向栈结构的指针
 *
 * 返回值:
 *   1 - 栈为空
 *   0 - 栈不为空
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */
int isEmpty(Stack *s){
    if(s->top==-1){
        printf("空的");
        return 1;
    }else{
        return 0;
    }
}

/**
 * 函数: push
 * 功能: 进栈操作（将元素压入栈顶）
 *
 * 参数:
 *   @param s - 指向栈结构的指针
 *   @param e - 要入栈的元素
 *
 * 返回值:
 *   1 - 入栈成功
 *   0 - 入栈失败（栈满）
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 注意:
 *   操作逻辑与test1.c相同，区别在于s->data是动态分配的数组
 */
int push(Stack *s,ElemType e){
    // 检查栈是否已满
    if(s->top==MAXSIZE-1){
        printf("满了");
        return 0;
    }

    // top指针加1
    s->top++;

    // 将元素存入栈顶
    s->data[s->top]=e;

    return 1;
}

/**
 * 函数: pop
 * 功能: 出栈操作（弹出栈顶元素）
 *
 * 参数:
 *   @param s - 指向栈结构的指针
 *   @param e - 指向用于存储出栈元素的变量指针
 *
 * 返回值:
 *   1 - 出栈成功
 *   0 - 出栈失败（栈空）
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */
int pop(Stack *s,ElemType *e){
    // 检查栈是否为空
    if(s->top==-1){
        printf("空的");
        return 0;
    }

    // 取出栈顶元素
    *e=s->data[s->top];

    // top指针减1
    s->top--;

    return 1;
}

/**
 * 函数: getTop
 * 功能: 获取栈顶元素（不删除）
 *
 * 参数:
 *   @param s - 指向栈结构的指针
 *   @param e - 指向用于存储栈顶元素的变量指针
 *
 * 返回值:
 *   1 - 获取成功
 *   0 - 获取失败（栈空）
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */
int getTop(Stack *s,ElemType *e){
    // 检查栈是否为空
    if(s->top==-1){
        printf("空的");
        return 0;
    }

    // 获取栈顶元素
    *e=s->data[s->top];

    return 1;
}

/**
 * 主函数: 测试动态分配的顺序栈
 *
 * 测试流程:
 *   与test1.c相同，但使用动态分配的栈
 *   1. 初始化栈（返回栈指针）
 *   2. 依次压入10, 20, 30
 *   3. 弹出栈顶元素并打印（应输出30）
 *   4. 获取栈顶元素并打印（应输出20）
 *
 * 内存管理注意:
 *   本例未释放malloc分配的内存
 *   实际应用应添加:
 *   free(s->data);
 *   free(s);
 */
int main(){
    // 初始化栈（返回栈指针）
    Stack *s=initStack();

    // 压入三个元素
    push(s,10);
    push(s,20);
    push(s,30);

    // 出栈并打印
    ElemType e;
    pop(s,&e);
    printf("%d\n",e);  // 输出: 30

    // 获取栈顶元素并打印
    getTop(s,&e);
    printf("%d\n",e);  // 输出: 20

    // TODO: 应释放动态分配的内存
    // free(s->data);
    // free(s);

    system("pause");
    return 0;
}
