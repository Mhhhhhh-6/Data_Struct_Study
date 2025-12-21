/**
 * ===========================================================================
 * 文件名: test4.c
 * 描述:   链式队列的实现
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了链式队列（Linked Queue），包括：
 *   1. 队列的初始化（带头节点）
 *   2. 判断队空
 *   3. 入队、出队操作
 *   4. 获取队头元素
 *
 * 数据结构:
 *   采用单链表实现的链式队列
 *   使用front指针指向头节点
 *   使用rear指针指向队尾节点
 *
 * 四种队列实现对比:
 *   ┌────────┬─────────┬─────────┬────────┬────────┐
 *   │        │ test1/2 │ test3   │ test4  │ 特点   │
 *   ├────────┼─────────┼─────────┼────────┼────────┤
 *   │ 存储   │ 数组    │ 数组    │ 链表   │        │
 *   │ 假溢出 │ 调整O(n)│ 循环O(1)│ 无     │        │
 *   │ 大小   │ 固定    │ 固定    │ 无限制 │        │
 *   │ 空间   │ 预分配  │ 预分配  │ 按需   │        │
 *   └────────┴─────────┴─────────┴────────┴────────┘
 *
 * 链式队列特点:
 *   - 无固定大小限制，理论上可以无限增长
 *   - 不会出现队满的情况（除非系统内存耗尽）
 *   - 不存在假溢出问题
 *   - 每次操作需要malloc/free，开销较大
 *
 * 队列示意图:
 *   front → [head] → [10] → [20] → [30] ← rear
 *          (头节点)   ↑队头         ↑队尾
 *
 * 使用方法:
 *   编译: gcc test4.c -o test4
 *   运行: ./test4 (Linux/Mac) 或 test4.exe (Windows)
 *
 * 难度: ⭐⭐（链表 + 队列的结合）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

/**
 * 队列节点结构定义
 *
 * 与链式栈的节点结构相同
 * 区别在于：栈只需要一个头指针，队列需要front和rear两个指针
 */
typedef struct QueueNode
{
	ElemType data;             // 数据域
	struct QueueNode *next;    // 指针域
}QueueNode;

/**
 * 链式队列结构定义
 *
 * 成员说明:
 *   - front: 队头指针，指向头节点
 *   - rear: 队尾指针，指向队列的最后一个元素
 *
 * 指针规则:
 *   - front == rear: 队列为空（都指向头节点）
 *   - front->next: 指向队头元素
 *   - rear: 指向队尾元素
 */
typedef struct
{
	QueueNode *front;  // 队头指针
	QueueNode *rear;   // 队尾指针
}Queue;

/**
 * 函数: initQueue
 * 功能: 初始化链式队列（创建带头节点的空队列）
 *
 * 返回值: 返回指向队列结构的指针
 *
 * 算法思路:
 *   1. 为Queue结构分配内存
 *   2. 创建一个头节点
 *   3. front和rear都指向头节点（表示空队列）
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 注意:
 *   使用带头节点的链表，简化入队和出队操作
 */
Queue* initQueue()
{
	// 为Queue结构分配内存
	Queue *q = (Queue*)malloc(sizeof(Queue));

	// 创建头节点
	QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
	node->data = 0;     // 头节点不存储有效数据
	node->next = NULL;

	// front和rear都指向头节点
	q->front = node;
	q->rear = node;

	return q;
}

/**
 * 函数: isEmpty
 * 功能: 判断链式队列是否为空
 *
 * 判断条件: front == rear
 *
 * 时间复杂度: O(1)
 *
 * 注意:
 *   链式队列的空队列判断与顺序队列相同
 */
int isEmpty(Queue *q)
{
	if (q->front == q->rear)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * 函数: equeue
 * 功能: 入队操作（在队尾插入元素）
 *
 * 参数:
 *   @param q - 队列指针
 *   @param e - 要入队的元素
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 创建新节点
 *   2. 新节点的data赋值为e
 *   3. 新节点的next设置为NULL
 *   4. rear的next指向新节点
 *   5. rear指针移动到新节点
 *   （实际上就是链表的尾插法）
 *
 * 时间复杂度: O(1) - 因为有rear指针直接指向队尾
 * 空间复杂度: O(1)
 *
 * 示例:
 *   原队列: front → [head] → [10] → [20] ← rear
 *   equeue(q, 30)
 *   结果: front → [head] → [10] → [20] → [30] ← rear
 */
void equeue(Queue *q, ElemType e)
{
	// 1. 创建新节点
	QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
	node->data = e;
	node->next = NULL;

	// 2. 当前队尾的next指向新节点
	q->rear->next = node;

	// 3. rear指针移动到新节点
	q->rear = node;
}

/**
 * 函数: dequeue
 * 功能: 出队操作（从队头删除元素）
 *
 * 参数:
 *   @param q - 队列指针
 *   @param e - 指向用于存储出队元素的变量指针
 *
 * 返回值:
 *   1 - 出队成功
 *   0 - 出队失败（队空）
 *
 * 算法思路:
 *   1. 检查队列是否为空
 *   2. node指向队头元素（front->next）
 *   3. 取出队头元素的数据
 *   4. front->next指向node->next（跳过队头）
 *   5. 如果删除的是最后一个元素，更新rear指向front
 *   6. 释放node节点
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 关键点:
 *   - 如果队列中只有一个元素，出队后需要更新rear指向front
 *   - 必须释放删除的节点，避免内存泄漏
 *
 * 示例:
 *   原队列: front → [head] → [10] → [20] → [30] ← rear
 *   dequeue(q, &e)
 *   结果: front → [head] → [20] → [30] ← rear, e=10
 */
int dequeue(Queue *q, ElemType *e)
{
	// 1. 检查队列是否为空
	if (isEmpty(q))
	{
		printf("空的\n");
		return 0;
	}

	// 2. node指向队头元素
	QueueNode *node = q->front->next;

	// 3. 取出队头元素的数据
	*e = node->data;

	// 4. front->next指向下一个节点（移除队头）
	q->front->next = node->next;

	// 5. 特殊情况：如果队列中只有一个元素
	//    删除后队列为空，需要更新rear指向front
	if (q->rear == node)
	{
		q->rear = q->front;
	}

	// 6. 释放删除的节点
	free(node);

	return 1;
}

/**
 * 函数: getFront
 * 功能: 获取队头元素（不删除）
 *
 * 返回值: 返回队头元素，队列为空时返回0
 *
 * 时间复杂度: O(1)
 *
 * 与dequeue的区别:
 *   - dequeue: 取出并删除队头元素
 *   - getFront: 只查看队头元素，不删除
 */
ElemType getFront(Queue *q)
{
	if (isEmpty(q))
	{
		printf("空的\n");
		return 0;
	}
	return q->front->next->data;
}


/**
 * 主函数: 测试链式队列
 *
 * 链式队列优势演示:
 *   - 无固定大小限制
 *   - 不存在假溢出问题
 *   - 适合元素数量不确定的场景
 */
int main(int argc, char const *argv[])
{
	// 初始化链式队列
	Queue *q = initQueue();

	// 入队5个元素
	equeue(q, 10);
	equeue(q, 20);
	equeue(q, 30);
	equeue(q, 40);
	equeue(q, 50);

	// 出队并打印
	ElemType e;
	dequeue(q, &e);
	printf("出队%d\n", e);  // 输出: 出队10
	dequeue(q, &e);
	printf("出队%d\n", e);  // 输出: 出队20

	// 获取队头元素
	printf("%d\n", getFront(q));  // 输出: 30

	// TODO: 完整的清理应该释放所有节点和队列结构

    system("pause");
	return 0;
}
