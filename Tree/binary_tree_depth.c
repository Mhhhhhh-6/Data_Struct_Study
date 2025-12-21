/**
 * ===========================================================================
 * 文件名: binary_tree_depth.c
 * 描述:   计算二叉树的深度（层序遍历实现）
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了计算二叉树深度的功能，包括：
 *   1. 使用层序遍历（BFS）计算树的深度
 *   2. 循环队列的实现（用于层序遍历）
 *   3. 逐层遍历并统计层数
 *
 * 什么是树的深度?
 *   - 树的深度（高度）= 从根节点到最远叶子节点的最长路径上的节点数
 *   - 也可以理解为树的层数
 *   - 空树的深度为0，只有根节点的树深度为1
 *
 * 计算深度的方法:
 *   方法1: 递归方法
 *          depth = max(左子树深度, 右子树深度) + 1
 *          时间O(n)，空间O(h)
 *
 *   方法2: 层序遍历（本文件采用）
 *          使用队列逐层遍历，统计层数
 *          时间O(n)，空间O(w) - w为最大宽度
 *
 * 数据结构:
 *   - 二叉树节点：包含data、lchild、rchild
 *   - 循环队列：用于层序遍历，存储树节点指针
 *
 * 示例二叉树:
 *          A           层1（深度=1）
 *        /   \
 *       B     C        层2（深度=2）
 *      / \   / \
 *     D   E F   G      层3（深度=3）
 *    /     /     \
 *   H     I       J    层4（深度=4）
 *    \
 *     K                层5（深度=5）
 *
 * 树的深度: 5
 *
 * 层序遍历过程:
 *   层1: A
 *   层2: B C
 *   层3: D E F G
 *   层4: H I J
 *   层5: K
 *
 * 使用方法:
 *   编译: gcc binary_tree_depth.c -o tree_depth
 *   运行: ./tree_depth (Linux/Mac) 或 tree_depth.exe (Windows)
 *
 * 难度: ⭐⭐（层序遍历 + 循环队列）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

// 树节点数据类型
typedef char TreeType;

/**
 * 二叉树节点结构定义
 */
typedef struct TreeNode
{
	TreeType data;            // 节点数据
	struct TreeNode *lchild;  // 左孩子指针
	struct TreeNode *rchild;  // 右孩子指针
}TreeNode;

// 队列元素类型（树节点指针）
typedef TreeNode* ElemType;

/**
 * 循环队列结构定义
 *
 * 成员说明:
 *   - data: 存储树节点指针的数组
 *   - front: 队头指针
 *   - rear: 队尾指针
 *
 * 循环队列特点:
 *   - 使用模运算实现循环
 *   - 队满条件: (rear+1) % MAXSIZE == front
 *   - 队空条件: front == rear
 */
typedef struct
{
	ElemType *data;  // 存储树节点指针的数组
	int front;       // 队头指针
	int rear;        // 队尾指针
}Queue;

// 二叉树类型定义
typedef TreeNode* BiTree;

// 全局变量：先序序列和索引
char str[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;

/**
 * 函数: createTree
 * 功能: 根据先序序列创建二叉树
 *
 * （注释详见binary_tree_traversal_recursive.c）
 */
void createTree(BiTree *T)
{
	TreeType ch;
	ch = str[idx++];
	if (ch == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTree)malloc(sizeof(TreeNode));
		(*T)->data = ch;
		createTree(&(*T)->lchild);
		createTree(&(*T)->rchild);
	}
}

/**
 * 函数: initQueue
 * 功能: 初始化循环队列
 *
 * 返回值: 返回指向新创建队列的指针
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(MAXSIZE)
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
 *
 * 返回值:
 *   1 - 队列为空
 *   0 - 队列不为空
 *
 * 时间复杂度: O(1)
 */
int isEmpty(Queue *Q)
{
	if (Q->front == Q->rear)
	{
		return 1;  // 队列为空
	}
	else
	{
		return 0;  // 队列不为空
	}
}

/**
 * 函数: equeue
 * 功能: 入队操作
 *
 * 参数:
 *   @param Q - 队列指针
 *   @param e - 要入队的树节点指针
 *
 * 返回值:
 *   1 - 入队成功
 *   0 - 入队失败（队满）
 *
 * 时间复杂度: O(1)
 */
int equeue(Queue *Q, ElemType e)
{
	// 检查队列是否已满
	if ((Q->rear + 1) % MAXSIZE == Q->front)
	{
		printf("队列已满\n");
		return 0;
	}

	// 入队
	Q->data[Q->rear] = e;

	// rear循环后移
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return 1;
}

/**
 * 函数: dequeue
 * 功能: 出队操作
 *
 * 参数:
 *   @param Q - 队列指针
 *   @param e - 用于存储出队元素的指针
 *
 * 返回值:
 *   1 - 出队成功
 *   0 - 出队失败（队空）
 *
 * 时间复杂度: O(1)
 */
int dequeue(Queue *Q, ElemType *e)
{
	// 检查队列是否为空
	if (Q->front == Q->rear)
	{
		return 0;  // 队列为空
	}

	// 出队
	*e = Q->data[Q->front];

	// front循环后移
	Q->front = (Q->front + 1) % MAXSIZE;
	return 1;
}

/**
 * 函数: getHead
 * 功能: 获取队头元素（不出队）
 *
 * 返回值:
 *   1 - 获取成功
 *   0 - 获取失败（队空）
 *
 * 时间复杂度: O(1)
 */
int getHead(Queue *Q, ElemType *e)
{
	if (Q->front == Q->rear)
	{
		return 0;
	}
	*e = Q->data[Q->front];
	return 1;
}

/**
 * 函数: queueSize
 * 功能: 获取队列中的元素数量
 *
 * 参数:
 *   @param Q - 队列指针
 *
 * 返回值: 队列中的元素个数
 *
 * 算法思路:
 *   队列元素数量 = rear - front
 *   （在循环队列中，如果跨越数组边界，需要特殊处理）
 *
 * 时间复杂度: O(1)
 *
 * 注意:
 *   本实现假设rear >= front（未处理跨界情况）
 *   完整实现应为: (rear - front + MAXSIZE) % MAXSIZE
 */
int queueSize(Queue *Q)
{
	if (!isEmpty(Q))
	{
		// 简化版本：假设rear >= front
		return Q->rear - Q->front;
	}
	else
	{
		return 0;
	}
}

/**
 * 函数: maxDepth
 * 功能: 计算二叉树的最大深度（使用层序遍历）
 *
 * 参数:
 *   @param root - 二叉树根节点指针
 *
 * 返回值: 树的深度（层数）
 *
 * 算法思路:
 *   1. 如果树为空，返回0
 *   2. 初始化队列，将根节点入队
 *   3. depth初始化为0
 *   4. 当队列不为空时循环：
 *      a. 获取当前层的节点数量count（当前队列大小）
 *      b. 处理当前层的所有节点（循环count次）：
 *         - 出队一个节点
 *         - 如果有左孩子，左孩子入队
 *         - 如果有右孩子，右孩子入队
 *      c. 当前层处理完毕，depth加1
 *   5. 返回depth
 *
 * 核心思想:
 *   - 层序遍历逐层处理节点
 *   - 每处理完一层，深度加1
 *   - 使用count记录每层的节点数，确保一次处理完整一层
 *
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(w) - w为树的最大宽度（队列最大长度）
 *
 * 示例:
 *   二叉树:      A           depth=0, 队列:[A]
 *             /   \
 *            B     C         depth=1, 队列:[B,C]
 *           / \
 *          D   E             depth=2, 队列:[D,E]
 *
 *   执行过程:
 *   初始: 队列[A], depth=0
 *   第1层: count=1, 处理A, 入队B和C, depth=1
 *   第2层: count=2, 处理B和C, 入队D和E, depth=2
 *   第3层: count=2, 处理D和E, 队列为空, depth=3
 *   返回: 3
 */
int maxDepth(TreeNode* root)
{
	// 1. 空树深度为0
	if (root == NULL)
	{
		return 0;
	}

	// 2. 初始化深度和队列
	int depth = 0;
	Queue *q = initQueue();

	// 3. 根节点入队
	equeue(q, root);

	// 4. 层序遍历
	while(!isEmpty(q))
	{
		// 4a. 获取当前层的节点数量
		int count = queueSize(q);

		// 4b. 处理当前层的所有节点
		while(count > 0)
		{
			TreeNode* curr;

			// 出队一个节点
			dequeue(q, &curr);

			// 如果有左孩子，入队
			if (curr->lchild != NULL)
			{
				equeue(q, curr->lchild);
			}

			// 如果有右孩子，入队
			if (curr->rchild != NULL)
			{
				equeue(q, curr->rchild);
			}

			// 当前节点处理完毕
			count--;
		}

		// 4c. 当前层处理完毕，深度加1
		depth++;
	}

	// 5. 返回深度
	return depth;
}

/**
 * 函数: maxDepthRecursive (可选实现)
 * 功能: 计算二叉树的最大深度（递归实现）
 *
 * 算法思路:
 *   depth(root) = max(depth(left), depth(right)) + 1
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(h) - 递归栈深度
 *
 * 注释版本供参考:
 */
/*
int maxDepthRecursive(TreeNode* root)
{
	// 递归终止条件：空节点深度为0
	if (root == NULL)
	{
		return 0;
	}

	// 递归计算左子树深度
	int leftDepth = maxDepthRecursive(root->lchild);

	// 递归计算右子树深度
	int rightDepth = maxDepthRecursive(root->rchild);

	// 返回较大深度 + 1（加上根节点）
	return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}
*/

/**
 * 主函数: 测试二叉树深度计算
 *
 * 二叉树结构:
 *          A           层1
 *        /   \
 *       B     C        层2
 *      / \   / \
 *     D   E F   G      层3
 *    /     /     \
 *   H     I       J    层4
 *    \
 *     K                层5
 *
 * 预期输出: 树的深度为 5
 */
int main(int argc, char const *argv[])
{
	BiTree T;

	printf("=== 二叉树深度计算演示 ===\n\n");
	printf("二叉树结构:\n");
	printf("         A           层1\n");
	printf("       /   \\\n");
	printf("      B     C        层2\n");
	printf("     / \\   / \\\n");
	printf("    D   E F   G      层3\n");
	printf("   /     /     \\\n");
	printf("  H     I       J    层4\n");
	printf("   \\\n");
	printf("    K                层5\n\n");

	// 创建二叉树
	printf("正在创建二叉树...\n");
	createTree(&T);

	// 计算深度
	int depth = maxDepth(T);
	printf("\n树的深度为: %d\n", depth);

	printf("\n深度计算方法:\n");
	printf("- 本程序使用层序遍历（BFS）\n");
	printf("- 逐层统计，每处理完一层深度加1\n");
	printf("- 时间复杂度: O(n)\n");
	printf("- 空间复杂度: O(w) - w为最大宽度\n");

	printf("\n=== 计算完成 ===\n");

	// TODO: 释放队列和树的内存

	system("pause");
	return 0;
}
