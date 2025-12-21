#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXNUM 100

typedef int ElemType;

typedef struct {
    ElemType stack[MAXNUM];
    int top;
} SqStack;

void InitStack(SqStack **p) {
    *p = (SqStack*)malloc(sizeof(SqStack));  // 申请空间
    (*p)->top = -1;  // 栈顶指针初始化为-1,表示空栈
    printf("顺序栈初始化成功!\n");
}

// 判断栈是否为空
bool IsEmpty(SqStack *p) {
    return p->top == -1;
}

// 判断栈是否已满
bool IsFull(SqStack *p) {
    return p->top == MAXNUM - 1;
}

// 入栈函数
void Push(SqStack *p, ElemType x) {
    if (IsFull(p)) {
        printf("栈已满,无法插入元素 %d!\n", x);
        return;
    }
    p->top = p->top + 1;      // 栈顶+1
    p->stack[p->top] = x;     // 数据入栈
    printf("元素 %d 入栈成功!\n", x);
}

// 出栈函数
ElemType Pop(SqStack *p) {
    if (IsEmpty(p)) {
        printf("栈为空,无法出栈!\n");
        return -1;
    }
    ElemType x = p->stack[p->top];  // 将栈顶元素赋给x
    p->top = p->top - 1;            // 栈顶-1
    printf("元素 %d 出栈成功!\n", x);
    return x;
}

// 获取栈顶元素函数(不删除)
ElemType GetTop(SqStack *p) {
    if (IsEmpty(p)) {
        printf("栈为空,无栈顶元素!\n");
        return -1;
    }
    ElemType x = p->stack[p->top];
    printf("栈顶元素是: %d\n", x);
    return x;
}

// 遍历顺序栈函数
void OutStack(SqStack *p) {
    if (IsEmpty(p)) {
        printf("栈为空,无元素可遍历!\n");
        return;
    }
    printf("\n当前栈中元素(从栈顶到栈底):\n");
    printf("--------------------------------\n");
    for (int i = p->top; i >= 0; i--) {
        printf("第 %d 个数据元素是: %6d\n", i + 1, p->stack[i]);
    }
    printf("--------------------------------\n");
}

// 置空顺序栈函数
void SetEmpty(SqStack *p) {
    p->top = -1;
    printf("顺序栈已置空!\n");
}

// 获取栈中元素个数
int GetLength(SqStack *p) {
    return p->top + 1;
}

// 销毁栈
void DestroyStack(SqStack **p) {
    if (*p != NULL) {
        free(*p);
        *p = NULL;
        printf("顺序栈已销毁!\n");
    }
}

// 打印菜单
void PrintMenu() {
    printf("\n========== 顺序栈基本运算 ==========\n");
    printf("1. 初始化栈\n");
    printf("2. 入栈\n");
    printf("3. 出栈\n");
    printf("4. 获取栈顶元素\n");
    printf("5. 遍历栈\n");
    printf("6. 置空栈\n");
    printf("7. 获取栈长度\n");
    printf("0. 退出程序\n");
    printf("====================================\n");
    printf("请选择操作: ");
}

int main(){
    SqStack *stack = NULL;
    int choice;
    ElemType value;

    while (1) {
        PrintMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (stack != NULL) {
                    printf("栈已存在,将先销毁旧栈!\n");
                    DestroyStack(&stack);
                }
                InitStack(&stack);
                break;

            case 2:
                if (stack == NULL) {
                    printf("请先初始化栈!\n");
                    break;
                }
                printf("请输入要入栈的元素: ");
                scanf("%d", &value);
                Push(stack, value);
                break;

            case 3:
                if (stack == NULL) {
                    printf("请先初始化栈!\n");
                    break;
                }
                Pop(stack);
                break;

            case 4:
                if (stack == NULL) {
                    printf("请先初始化栈!\n");
                    break;
                }
                GetTop(stack);
                break;

            case 5:
                if (stack == NULL) {
                    printf("请先初始化栈!\n");
                    break;
                }
                OutStack(stack);
                break;

            case 6:
                if (stack == NULL) {
                    printf("请先初始化栈!\n");
                    break;
                }
                SetEmpty(stack);
                break;

            case 7:
                if (stack == NULL) {
                    printf("请先初始化栈!\n");
                    break;
                }
                printf("栈中元素个数: %d\n", GetLength(stack));
                break;

            case 0:
                if (stack != NULL) {
                    DestroyStack(&stack);
                }
                printf("程序已退出!\n");
                system("pause");
                return 0;

            default:
                printf("无效选择,请重新输入!\n");
        }
    }
}