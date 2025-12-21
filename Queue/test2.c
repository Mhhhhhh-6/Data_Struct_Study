/**
 * ===========================================================================
 * 文件名: test2.c
 * 描述:   顺序队列的动态内存实现（带队列调整功能）
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件是test1.c的动态内存版本，实现了：
 *   1. 队列的动态初始化
 *   2. 判断队空
 *   3. 入队、出队操作
 *   4. 获取队头元素
 *   5. 队列调整（解决假溢出）
 *
 * 与test1.c的区别:
 *   test1.c: Queue作为结构体变量，静态数组
 *   test2.c: Queue*作为指针，动态分配内存
 *
 * 动态分配优势:
 *   - 更灵活的内存管理
 *   - 可以方便地在函数间传递队列指针
 *   - 适合需要多个队列实例的场景
 *
 * 注意事项:
 *   - 需要两次malloc（Queue结构 + data数组）
 *   - 使用完毕应释放内存（本例未实现）
 *
 * 核心算法说明:
 *   队列调整算法详见test1.c的queueFull函数注释
 *
 * 使用方法:
 *   编译: gcc test2.c -o test2
 *   运行: ./test2 (Linux/Mac) 或 test2.exe (Windows)
 *
 * 难度: ⭐⭐（基础数据结构 + 动态内存）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType;

/**
 * 顺序队列结构定义（动态内存版本）
 *
 * 与test1.c的区别:
 *   test1.c: ElemType data[MAXSIZE]; (静态数组)
 *   test2.c: ElemType *data;          (动态数组指针)
 */
typedef struct
{
	ElemType *data;  // 指向动态分配的队列数组
	int front;       // 队头指针
	int rear;        // 队尾指针
}Queue;

/**
 * 函数: initQueue
 * 功能: 初始化顺序队列（动态分配内存）
 *
 * 返回值: 返回指向新创建的队列结构的指针
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(MAXSIZE)
 *
 * 注意:
 *   需要两次malloc：Queue结构 + data数组
 */
Queue* initQueue()
{
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	q->front = 0;
	q->rear = 0;
	return q;
}

/**
 * 函数: isEmpty
 * 功能: 判断队列是否为空
 * 时间复杂度: O(1)
 */
int isEmpty(Queue *Q)
{
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * 函数: dequeue
 * 功能: 出队操作
 * 时间复杂度: O(1)
 */
ElemType dequeue(Queue *Q)
{
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 0;
	}
	ElemType e = Q->data[Q->front];
	Q->front++;
	return e;
}

/**
 * 函数: queueFull
 * 功能: 队列调整（解决假溢出）
 *
 * 算法详解: 见test1.c的queueFull函数详细注释
 *
 * 时间复杂度: O(n)
 */
int queueFull(Queue *Q)
{
	if (Q->front > 0)
	{
		int step = Q->front;
		for (int i = Q->front; i <= Q->rear; ++i)
		{
			Q->data[i - step] = Q->data[i];
		}
		Q->front = 0;
		Q->rear = Q->rear - step;
		return 1;
	}
	else
	{
		printf("真的满了\n");
		return 0;
	}
}

/**
 * 函数: equeue
 * 功能: 入队操作
 *
 * 时间复杂度:
 *   最好: O(1) - 不需要调整
 *   最坏: O(n) - 需要调整队列
 */
int equeue(Queue *Q, ElemType e)
{
	if (Q->rear >= MAXSIZE)
	{
		if(!queueFull(Q))
		{
			return 0;
		}
	}
	Q->data[Q->rear] = e;
	Q->rear++;
	return 1;
}

/**
 * 函数: getHead
 * 功能: 获取队头元素（不删除）
 * 时间复杂度: O(1)
 */
int getHead(Queue *Q, ElemType *e)
{
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 0;
	}
	*e = Q->data[Q->front];
	return 1;
}

/**
 * 主函数: 测试动态分配的顺序队列
 *
 * 与test1.c的区别:
 *   test1.c: Queue q; initQueue(&q);
 *   test2.c: Queue *q = initQueue();
 *
 * 内存管理提醒:
 *   使用完毕应添加:
 *   free(q->data);
 *   free(q);
 */
int main()
{
	// 初始化队列（返回队列指针）
	Queue *q = initQueue();

	// 入队5个元素
	equeue(q, 10);
	equeue(q, 20);
	equeue(q, 30);
	equeue(q, 40);
	equeue(q, 50);

	// 出队并打印
	printf("%d\n",dequeue(q));  // 输出: 10
	printf("%d\n",dequeue(q));  // 输出: 20

	// 获取队头元素并打印
	ElemType e;
	getHead(q, &e);
	printf("%d\n",e);  // 输出: 30

	// TODO: 应释放动态分配的内存
	// free(q->data);
	// free(q);

    system("pause");
	return 0;
}
