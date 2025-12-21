#include <stdio.h>
#include <stdlib.h>

// 定义数据类型
typedef int ElemType;

// 定义链队列节点
typedef struct Qnode
{
    ElemType data;
    struct Qnode *next;
} Qnodetype;

// 定义链队列
typedef struct
{
    Qnodetype *front;  // 队头指针
    Qnodetype *rear;   // 队尾指针
} Lqueue;

// 函数声明
void creat(Lqueue *q);
void Lappend(Lqueue *q, int x);
ElemType Ldelete(Lqueue *q);
void display(Lqueue *q);
int isEmpty(Lqueue *q);

// 初始化并建立链队列
void creat(Lqueue *q)
{
    int i, n, x;
    Qnodetype *h;
    
    // 初始化申请空间
    h = (Qnodetype*)malloc(sizeof(Qnodetype));
    h->next = NULL;
    q->front = h;
    q->rear = h;
    
    printf("请输入要创建的队列元素个数: ");
    scanf("%d", &n);
    
    printf("请依次输入%d个元素: ", n);
    // 利用循环快速输入数据
    for(i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        Lappend(q, x);  // 利用入链队列函数快速输入数据
    }
    printf("链队列创建成功!\n");
}

// 入链队列函数
void Lappend(Lqueue *q, int x)
{
    Qnodetype *s;
    s = (Qnodetype*)malloc(sizeof(Qnodetype));
    s->data = x;
    s->next = NULL;
    q->rear->next = s;
    q->rear = s;
}

// 出链队列函数
ElemType Ldelete(Lqueue *q)
{
    Qnodetype *p;
    ElemType x;
    
    if(isEmpty(q))
    {
        printf("队列为空,无法出队!\n");
        return -1;
    }
    
    p = q->front->next;
    q->front->next = p->next;
    
    if(p->next == NULL)
        q->rear = q->front;
    
    x = p->data;
    free(p);  // 释放空间
    return x;
}

// 判断队列是否为空
int isEmpty(Lqueue *q)
{
    return q->front == q->rear;
}

// 遍历链队列函数
void display(Lqueue *q)
{
    Qnodetype *p;
    
    if(isEmpty(q))
    {
        printf("队列为空!\n");
        return;
    }
    
    p = q->front->next;
    printf("队列元素: ");
    while(p != NULL)  // 利用条件判断是否到队尾
    {
        printf("%d", p->data);
        if(p->next != NULL)
            printf(" --> ");
        p = p->next;
    }
    printf("\n");
}

// 主函数测试
int main()
{
    Lqueue q;
    int choice, value;
    
    printf("========== 链队列操作 ==========\n");
    
    // 初始化并建立链队列
    creat(&q);
    
    while(1)
    {
        printf("\n请选择操作:\n");
        printf("1. 入队\n");
        printf("2. 出队\n");
        printf("3. 遍历队列\n");
        printf("0. 退出\n");
        printf("请输入选择: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                printf("请输入要入队的元素: ");
                scanf("%d", &value);
                Lappend(&q, value);
                printf("元素 %d 入队成功!\n", value);
                break;
                
            case 2:
                value = Ldelete(&q);
                if(value != -1)
                    printf("出队元素: %d\n", value);
                break;
                
            case 3:
                display(&q);
                break;
                
            case 0:
                printf("程序退出!\n");
                system("pause");
                return 0;
                
            default:
                printf("无效选择,请重新输入!\n");
        }
    }
    
    return 0;
}
