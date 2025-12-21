/**
 * ===========================================================================
 * 文件名: test1.c
 * 描述:   顺序队列的基本实现（带队列调整功能）
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了顺序队列（Sequential Queue）的核心操作，包括：
 *   1. 队列的初始化
 *   2. 判断队空
 *   3. 入队（Enqueue）操作
 *   4. 出队（Dequeue）操作
 *   5. 获取队头元素
 *   6. **队列调整（解决假溢出问题）** ← 本文件的关键特性
 *
 * 数据结构:
 *   采用数组实现的顺序队列
 *   使用front指针指示队头位置
 *   使用rear指针指示队尾位置
 *
 * 队列的特点:
 *   - 先进先出（FIFO - First In First Out）
 *   - 只能在队尾插入（enqueue），在队头删除（dequeue）
 *   - front == rear表示队列为空
 *
 * 假溢出问题:
 *   ┌──────────────────────────────────────────────┐
 *   │ 问题场景:                                     │
 *   │   初始: [10][20][30][40][50][ ][ ][ ]        │
 *   │         front=0, rear=5                       │
 *   │                                               │
 *   │   出队2次: [ ][ ][30][40][50][ ][ ][ ]       │
 *   │            front=2, rear=5                    │
 *   │                                               │
 *   │   再入队多个: [ ][ ][30][40][50][60][70][80]│
 *   │               front=2, rear=8 (假溢出!)      │
 *   │                                               │
 *   │   虽然前面有空间，但rear已到数组末尾         │
 *   │   这就是"假溢出"问题                         │
 *   └──────────────────────────────────────────────┘
 *
 * 解决方案:
 *   方案1: 循环队列（见test2.c等） - 常用
 *   方案2: 队列调整（本文件） - 当rear到达末尾时，整体前移
 *
 * 队列调整示例:
 *   调整前: [_][_][30][40][50][60][70][80]
 *          front=2, rear=8
 *
 *   调整后: [30][40][50][60][70][80][_][_]
 *          front=0, rear=6
 *
 * 应用场景:
 *   - 打印机任务队列
 *   - 消息队列
 *   - 广度优先搜索（BFS）
 *   - 银行排队系统
 *
 * 使用方法:
 *   编译: gcc test1.c -o test1
 *   运行: ./test1 (Linux/Mac) 或 test1.exe (Windows)
 *
 * 难度: ⭐⭐（基础数据结构 + 假溢出处理）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 队列的最大容量
#define MAXSIZE 100

// 队列元素类型定义
typedef int ElemType;

/**
 * 顺序队列结构定义
 *
 * 成员说明:
 *   - data[MAXSIZE]: 存储队列元素的数组
 *   - front: 队头指针，指示队头元素的位置
 *   - rear: 队尾指针，指示队尾元素的下一个位置
 *
 * 指针规则:
 *   - front == rear: 队列为空
 *   - rear - front: 队列中元素的个数
 *   - data[front]: 队头元素
 *   - data[rear-1]: 队尾元素
 *
 * 队列示意图:
 *   [ ][ ][10][20][30][ ][ ]
 *         ↑front    ↑rear
 *   队列包含: 10, 20, 30
 */
typedef struct
{
	ElemType data[MAXSIZE];  // 存储队列元素的数组
	int front;               // 队头指针
	int rear;                // 队尾指针
}Queue;

/**
 * 函数: initQueue
 * 功能: 初始化顺序队列
 *
 * 参数:
 *   @param Q - 指向队列结构的指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   将front和rear都设置为0，表示空队列
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */
void initQueue(Queue *Q)
{
	Q->front = 0;
	Q->rear = 0;
}

/**
 * 函数: isEmpty
 * 功能: 判断队列是否为空
 *
 * 参数:
 *   @param Q - 指向队列结构的指针
 *
 * 返回值:
 *   1 - 队列为空
 *   0 - 队列不为空
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
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
 * 功能: 出队操作（从队头删除元素）
 *
 * 参数:
 *   @param Q - 指向队列结构的指针
 *
 * 返回值: 返回队头元素，队列为空时返回0
 *
 * 算法思路:
 *   1. 检查队列是否为空
 *   2. 取出front位置的元素
 *   3. front指针加1
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 注意事项:
 *   - 出队后front增加，前面的空间不会被立即回收
 *   - 多次出队后会导致假溢出问题
 *   - 这正是需要queueFull函数调整的原因
 */
ElemType dequeue(Queue *Q)
{
	// 检查队列是否为空
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 0;
	}

	// 取出队头元素
	ElemType e = Q->data[Q->front];

	// front指针后移
	Q->front++;

	return e;
}

/**
 * 函数: queueFull
 * 功能: 队列调整（解决假溢出问题）
 *
 * 参数:
 *   @param Q - 指向队列结构的指针
 *
 * 返回值:
 *   1 - 调整成功
 *   0 - 调整失败（队列真的满了）
 *
 * 算法思路:
 *   1. 检查front是否大于0（前面是否有空间）
 *   2. 如果有空间，将所有元素向前移动front个位置
 *   3. 更新front为0，rear减去step
 *   4. 如果front==0，说明队列真的满了
 *
 * 时间复杂度: O(n) - 需要移动队列中的所有元素
 * 空间复杂度: O(1)
 *
 * 假溢出 vs 真溢出:
 *   假溢出: rear到达MAXSIZE，但front>0（前面有空间）
 *          → 调整队列，返回1
 *
 *   真溢出: rear到达MAXSIZE，且front==0（真的满了）
 *          → 无法调整，返回0
 *
 * 示例:
 *   调整前:
 *   [_][_][_][30][40][50][60][70][80][_]
 *   front=3, rear=9
 *
 *   step = front = 3
 *   移动过程:
 *   i=3: data[0] = data[3] = 30
 *   i=4: data[1] = data[4] = 40
 *   i=5: data[2] = data[5] = 50
 *   ...
 *
 *   调整后:
 *   [30][40][50][60][70][80][_][_][_][_]
 *   front=0, rear=6
 *
 * 缺点:
 *   - 时间复杂度O(n)，效率较低
 *   - 循环队列方案更优（O(1)，见test2.c）
 */
int queueFull(Queue *Q)
{
	// 检查前面是否有空间
	if (Q->front > 0)
	{
		// 计算需要前移的步数
		int step = Q->front;

		// 将所有元素前移step个位置
		for (int i = Q->front; i <= Q->rear; ++i)
		{
			Q->data[i - step] = Q->data[i];
		}

		// 更新front和rear
		Q->front = 0;
		Q->rear = Q->rear - step;

		return 1;  // 调整成功
	}
	else
	{
		// front==0，队列真的满了
		printf("真的满了\n");
		return 0;
	}
}

/**
 * 函数: equeue (enqueue)
 * 功能: 入队操作（在队尾插入元素）
 *
 * 参数:
 *   @param Q - 指向队列结构的指针
 *   @param e - 要入队的元素
 *
 * 返回值:
 *   1 - 入队成功
 *   0 - 入队失败（队列满）
 *
 * 算法思路:
 *   1. 检查rear是否到达MAXSIZE
 *   2. 如果到达，尝试调整队列
 *   3. 将元素e存入rear位置
 *   4. rear指针加1
 *
 * 时间复杂度:
 *   最好: O(1) - 不需要调整
 *   最坏: O(n) - 需要调整队列
 *
 * 注意:
 *   函数名equeue可能是enqueue的简写
 *   标准命名应为enqueue
 */
int equeue(Queue *Q, ElemType e)
{
	// 检查rear是否到达数组末尾
	if (Q->rear >= MAXSIZE)
	{
		// 尝试调整队列
		if(!queueFull(Q))
		{
			// 调整失败，队列真的满了
			return 0;
		}
	}

	// 将元素存入队尾
	Q->data[Q->rear] = e;

	// rear指针后移
	Q->rear++;

	return 1;
}

/**
 * 函数: getHead
 * 功能: 获取队头元素（不删除）
 *
 * 参数:
 *   @param Q - 指向队列结构的指针
 *   @param e - 指向用于存储队头元素的变量指针
 *
 * 返回值:
 *   1 - 获取成功
 *   0 - 获取失败（队列为空）
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 与dequeue的区别:
 *   - dequeue: 取出并删除队头元素（front加1）
 *   - getHead: 只查看队头元素，不删除（front不变）
 */
int getHead(Queue *Q, ElemType *e)
{
	// 检查队列是否为空
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 0;
	}

	// 获取队头元素
	*e = Q->data[Q->front];

	return 1;
}

/**
 * 主函数: 测试顺序队列的基本操作
 *
 * 测试流程:
 *   1. 初始化队列
 *   2. 依次入队10, 20, 30, 40, 50
 *   3. 出队两次并打印（应输出10, 20）
 *   4. 获取队头元素并打印（应输出30）
 *
 * 队列变化过程:
 *   初始: [ ][ ][ ][ ][ ]
 *         front=0, rear=0
 *
 *   入队5个: [10][20][30][40][50]
 *           front=0, rear=5
 *
 *   出队2次: [ ][ ][30][40][50]
 *           front=2, rear=5
 *           输出: 10, 20
 *
 *   getHead: [ ][ ][30][40][50]
 *           front=2, rear=5
 *           输出: 30
 *
 * 假溢出演示:
 *   如果继续入队到rear=MAXSIZE，会触发queueFull调整
 */
int main()
{
	// 初始化队列
	Queue q;
	initQueue(&q);

	// 入队5个元素
	equeue(&q, 10);
	equeue(&q, 20);
	equeue(&q, 30);
	equeue(&q, 40);
	equeue(&q, 50);

	// 出队并打印
	printf("%d\n",dequeue(&q));  // 输出: 10
	printf("%d\n",dequeue(&q));  // 输出: 20

	// 获取队头元素并打印
	ElemType e;
	getHead(&q, &e);
	printf("%d\n",e);  // 输出: 30

    system("pause");
	return 0;
}
