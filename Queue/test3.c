/**
 * ===========================================================================
 * 文件名: test3.c
 * 描述:   循环队列的实现（解决假溢出的最佳方案）
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了循环队列（Circular Queue），包括：
 *   1. 队列的动态初始化
 *   2. 判断队空
 *   3. 入队、出队操作（使用模运算实现循环）
 *   4. 获取队头元素
 *
 * 循环队列原理:
 *   通过模运算（%）将数组首尾连接，形成逻辑上的环形结构
 *
 *   逻辑结构示意图:
 *         0   1   2   3   4
 *       ┌───┬───┬───┬───┬───┐
 *       │ A │ B │ C │   │   │
 *       └───┴───┴───┴───┴───┘
 *         ↓               ↑
 *       front=0        rear=3
 *
 *   循环后:
 *       rear从4→0（rear=(rear+1)%5）
 *       front从4→0（front=(front+1)%5）
 *
 * 与test1.c/test2.c的对比:
 *   ┌───────────┬──────────────┬──────────────┬──────────────┐
 *   │ 方案      │ 假溢出处理   │ 时间复杂度   │ 空间利用率   │
 *   ├───────────┼──────────────┼──────────────┼──────────────┤
 *   │ test1/2   │ 队列调整     │ O(n)         │ 100%         │
 *   │ test3     │ 循环队列     │ O(1)         │ MAXSIZE-1    │
 *   └───────────┴──────────────┴──────────────┴──────────────┘
 *
 * 循环队列的关键:
 *   1. 入队: rear = (rear+1) % MAXSIZE
 *   2. 出队: front = (front+1) % MAXSIZE
 *   3. 队满判断: (rear+1) % MAXSIZE == front
 *   4. 队空判断: front == rear
 *
 * 为什么要牺牲一个空间?
 *   如果不牺牲一个空间，队满和队空的判断条件都是 front==rear
 *   无法区分队满和队空，所以约定：
 *   - 队空: front == rear
 *   - 队满: (rear+1) % MAXSIZE == front
 *   这样队列最多存储 MAXSIZE-1 个元素
 *
 * 使用方法:
 *   编译: gcc test3.c -o test3
 *   运行: ./test3 (Linux/Mac) 或 test3.exe (Windows)
 *
 * 难度: ⭐⭐⭐（循环队列是数据结构的经典算法）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType;

/**
 * 循环队列结构定义
 *
 * 与test1.c/test2.c的区别:
 *   操作时使用模运算实现循环
 */
typedef struct{
    ElemType *data;  // 指向动态分配的队列数组
    int front;       // 队头指针
    int rear;        // 队尾指针
}Queue;

/**
 * 函数: initQueue
 * 功能: 初始化循环队列
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(MAXSIZE)
 */
Queue* initQueue(){
    Queue *q=(Queue*)malloc(sizeof(Queue));
    q->data=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    q->front=0;
    q->rear=0;
    return q;
}

/**
 * 函数: isEmpty
 * 功能: 判断循环队列是否为空
 *
 * 判断条件: front == rear
 *
 * 时间复杂度: O(1)
 */
int isEmpty(Queue *Q){
    if(Q->front==Q->rear){
        printf("空的");
        return 1;
    }else{
        return 0;
    }
}

/**
 * 函数: equeue
 * 功能: 入队操作（循环队列版本）
 *
 * 参数:
 *   @param Q - 队列指针
 *   @param e - 要入队的元素
 *
 * 返回值:
 *   1 - 入队成功
 *   0 - 入队失败（队满）
 *
 * 算法关键:
 *   1. 队满判断: (rear+1) % MAXSIZE == front
 *   2. 存入元素: data[rear] = e
 *   3. 循环移动: rear = (rear+1) % MAXSIZE
 *
 * 时间复杂度: O(1) - 不需要移动元素
 *
 * 示例:
 *   MAXSIZE=5, front=0, rear=3
 *   [A][B][C][_][_]
 *    ↑front  ↑rear
 *
 *   入队D: rear=3→4
 *   [A][B][C][D][_]
 *
 *   入队E: rear=4→0 (循环)
 *   [E][B][C][D][_]
 *           ↑front ↑rear=0
 *
 *   此时 (0+1)%5==1 != front=0，还能继续入队
 */
int equeue(Queue *Q,ElemType e){
    // 检查队列是否已满
    // (rear+1)%MAXSIZE == front 表示队满
    if((Q->rear+1)%MAXSIZE==Q->front){
        printf("满了");
        return 0;
    }

    // 将元素存入队尾
    Q->data[Q->rear]=e;

    // rear循环后移（关键操作）
    Q->rear=(Q->rear+1)%MAXSIZE;

    return 1;
}

/**
 * 函数: dequeue
 * 功能: 出队操作（循环队列版本）
 *
 * 算法关键:
 *   1. 队空判断: front == rear
 *   2. 取出元素: e = data[front]
 *   3. 循环移动: front = (front+1) % MAXSIZE
 *
 * 时间复杂度: O(1)
 */
int dequeue(Queue *Q,ElemType *e){
    // 检查队列是否为空
    if(Q->front==Q->rear){
        printf("空的");
        return 0;
    }

    // 取出队头元素
    *e=Q->data[Q->front];

    // front循环后移（关键操作）
    Q->front=(Q->front+1)%MAXSIZE;

    return 1;
}

/**
 * 函数: getHead
 * 功能: 获取队头元素（不删除）
 *
 * 时间复杂度: O(1)
 */
int getHead(Queue *Q,ElemType *e){
    if(Q->front==Q->rear){
        printf("空的");
        return 0;
    }
    *e=Q->data[Q->front];
    return 1;
}

/**
 * 主函数: 测试循环队列
 *
 * 循环队列优势演示:
 *   - 所有操作都是O(1)
 *   - 不需要移动元素
 *   - 是解决假溢出的最佳方案
 */
int main(){
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
	printf("%d\n",e);  // 输出: 10
	dequeue(q, &e);
	printf("%d\n",e);  // 输出: 20

	// 获取队头元素
	getHead(q, &e);
	printf("%d\n",e);  // 输出: 30

    system("pause");
	return 0;
}
