/**
 * ===========================================================================
 * 文件名: binary_tree_wpl.c
 * 描述:   计算二叉树的加权路径长度（WPL）
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了计算二叉树加权路径长度（Weighted Path Length）的功能
 *   包括：
 *   1. 创建带权重的二叉树
 *   2. 使用层序遍历计算WPL
 *   3. 统计叶子节点的权重和深度
 *
 * 什么是加权路径长度（WPL）?
 *   - 路径长度：从根节点到某个节点的路径上的边数（等于节点深度）
 *   - 加权路径长度（WPL）：树中所有叶子节点的 (权重 × 路径长度) 之和
 *   - 公式: WPL = Σ (w_i × l_i)
 *     其中 w_i 是第i个叶子节点的权重
 *          l_i 是第i个叶子节点的路径长度（深度）
 *
 * WPL的应用场景:
 *   1. 哈夫曼树（最优二叉树）：WPL最小的二叉树
 *   2. 哈夫曼编码：用于数据压缩，WPL表示平均编码长度
 *   3. 决策树：WPL表示平均决策代价
 *   4. 文件压缩：字符频率作为权重，WPL最小即压缩率最高
 *
 * 示例二叉树:
 *           100         深度0（非叶子，不计入WPL）
 *          /   \
 *        42     58      深度1（非叶子，不计入WPL）
 *       /  \   /  \
 *     15  27 28  30     深度2（15,27,30是叶子，28不是）
 *            / \
 *          13  15       深度3（13不是叶子，15是叶子）
 *          / \
 *         5   8         深度4（都是叶子）
 *
 * WPL计算:
 *   叶子节点: 15(深度2), 27(深度2), 5(深度4), 8(深度4), 15(深度3), 30(深度2)
 *   WPL = 15×2 + 27×2 + 5×4 + 8×4 + 15×3 + 30×2
 *       = 30 + 54 + 20 + 32 + 45 + 60
 *       = 241
 *
 * 数据结构:
 *   - 树节点包含weight（权重）、left、right指针
 *   - 使用数组模拟队列进行层序遍历
 *
 * 使用方法:
 *   编译: gcc binary_tree_wpl.c -o tree_wpl
 *   运行: ./tree_wpl (Linux/Mac) 或 tree_wpl.exe (Windows)
 *
 * 难度: ⭐⭐⭐（理解WPL概念 + 层序遍历）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

// 树节点权重类型
typedef int ElemType;

/**
 * 二叉树节点结构定义（带权重）
 *
 * 成员说明:
 *   - weight: 节点权重（整数）
 *   - left: 左孩子指针
 *   - right: 右孩子指针
 *
 * 与普通二叉树的区别:
 *   节点存储的是权重值（int），而不是字符
 */
typedef struct TreeNode
{
	ElemType weight;          // 节点权重
	struct TreeNode *left;    // 左孩子指针
	struct TreeNode *right;   // 右孩子指针
}TreeNode;

// 二叉树类型定义
typedef TreeNode* BiTree;

/**
 * 全局变量:
 *   idx: 当前处理的权重索引
 *   weight[]: 先序遍历的权重序列，-1表示空节点
 *
 * 权重序列说明:
 *   {100, 42, 15, -1, -1, 27, -1, -1, 58, 28, 13, 5, -1, -1, 8, -1, -1, 15, -1, -1, 30, -1, -1}
 *
 * 对应的二叉树:
 *           100
 *          /   \
 *        42     58
 *       /  \   /  \
 *     15  27 28  30
 *            / \
 *          13  15
 *          / \
 *         5   8
 */
int idx = 0;
int weight[] = {100, 42, 15, -1, -1, 27, -1, -1, 58, 28, 13, 5, -1, -1, 8, -1, -1, 15, -1, -1, 30, -1, -1};

/**
 * 函数: createTree
 * 功能: 根据权重序列创建二叉树
 *
 * 参数:
 *   @param T - 指向树根节点指针的指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 读取当前权重值
 *   2. 如果是-1，表示空节点
 *   3. 否则创建节点并保存权重
 *   4. 递归创建左子树
 *   5. 递归创建右子树
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(h) - 递归栈深度
 */
void createTree(BiTree *T)
{
	ElemType ch;
	// 读取当前权重
	ch = weight[idx++];

	if (ch == -1)
	{
		// 空节点
		*T = NULL;
	}
	else
	{
		// 创建节点
		*T = (BiTree)malloc(sizeof(TreeNode));
		(*T)->weight = ch;

		// 递归创建左子树
		createTree(&(*T)->left);

		// 递归创建右子树
		createTree(&(*T)->right);
	}
}

/**
 * 函数: wpl
 * 功能: 计算二叉树的加权路径长度（使用层序遍历）
 *
 * 参数:
 *   @param T - 二叉树根节点指针
 *
 * 返回值: WPL值（所有叶子节点的 权重×深度 之和）
 *
 * 算法思路:
 *   1. 如果树为空，返回0
 *   2. 初始化队列（数组实现）、WPL和深度
 *   3. 根节点入队
 *   4. 层序遍历：
 *      a. 获取当前层的节点数量
 *      b. 处理当前层的所有节点：
 *         - 出队一个节点
 *         - 如果是叶子节点（无左右孩子），累加 weight × depth
 *         - 如果有左孩子，左孩子入队
 *         - 如果有右孩子，右孩子入队
 *      c. 当前层处理完毕，深度加1
 *   5. 返回WPL
 *
 * 核心思想:
 *   - 层序遍历逐层处理，可以准确追踪每个节点的深度
 *   - 只有叶子节点才计入WPL
 *   - 叶子节点的WPL贡献 = 权重 × 深度
 *
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(w) - w为树的最大宽度（队列最大长度）
 *
 * 示例:
 *   二叉树:       100 (depth=0)
 *               /    \
 *             42      58 (depth=1)
 *            /  \
 *          15   27 (depth=2, 叶子)
 *
 *   执行过程:
 *   depth=0: 处理100（非叶子，不计入）
 *   depth=1: 处理42和58（非叶子，不计入）
 *   depth=2: 处理15和27（叶子）
 *            WPL += 15*2 + 27*2 = 30 + 54 = 84
 */
int wpl(BiTree T)
{
	// 1. 空树WPL为0
	if (T == NULL)
	{
		return 0;
	}

	// 2. 初始化队列（使用数组）
	BiTree queue[MAXSIZE];
	int front = 0;  // 队头指针
	int rear = 0;   // 队尾指针

	// 3. 初始化WPL和深度
	int wpl = 0;
	int depth = 0;

	// 4. 根节点入队
	queue[rear] = T;
	rear++;

	// 5. 层序遍历
	while(rear != front)
	{
		// 5a. 获取当前层的节点数量
		int count = rear - front;

		// 5b. 处理当前层的所有节点
		while(count > 0)
		{
			// 出队一个节点
			BiTree curr = queue[front];
			front++;

			// 5b-i. 判断是否为叶子节点
			// 叶子节点：没有左孩子也没有右孩子
			if (curr->left == NULL && curr->right == NULL)
			{
				// 累加叶子节点的WPL贡献
				wpl += depth * curr->weight;

				// 调试输出（可选）
				// printf("叶子节点: 权重=%d, 深度=%d, 贡献=%d\n",
				//        curr->weight, depth, depth * curr->weight);
			}

			// 5b-ii. 如果有左孩子，入队
			if (curr->left != NULL)
			{
				queue[rear] = curr->left;
				rear++;
			}

			// 5b-iii. 如果有右孩子，入队
			if (curr->right != NULL)
			{
				queue[rear] = curr->right;
				rear++;
			}

			// 当前节点处理完毕
			count--;
		}

		// 5c. 当前层处理完毕，深度加1
		depth += 1;
	}

	// 6. 返回WPL
	return wpl;
}

/**
 * 函数: wplRecursive (可选实现)
 * 功能: 计算WPL的递归实现
 *
 * 算法思路:
 *   wpl(T, depth) =
 *     if T是叶子: weight * depth
 *     else: wpl(T->left, depth+1) + wpl(T->right, depth+1)
 *
 * 注释版本供参考:
 */
/*
int wplRecursive(BiTree T, int depth)
{
	// 空节点不贡献WPL
	if (T == NULL)
	{
		return 0;
	}

	// 叶子节点贡献 weight × depth
	if (T->left == NULL && T->right == NULL)
	{
		return T->weight * depth;
	}

	// 非叶子节点：累加左右子树的WPL
	return wplRecursive(T->left, depth + 1) + wplRecursive(T->right, depth + 1);
}
*/

/**
 * 主函数: 测试WPL计算
 *
 * 二叉树结构:
 *           100
 *          /   \
 *        42     58
 *       /  \   /  \
 *     15  27 28  30
 *            / \
 *          13  15
 *          / \
 *         5   8
 *
 * 叶子节点及其深度:
 *   - 15 (深度2)
 *   - 27 (深度2)
 *   - 5  (深度4)
 *   - 8  (深度4)
 *   - 15 (深度3)
 *   - 30 (深度2)
 *
 * 预期WPL:
 *   15×2 + 27×2 + 5×4 + 8×4 + 15×3 + 30×2
 *   = 30 + 54 + 20 + 32 + 45 + 60
 *   = 241
 */
int main(int argc, char const *argv[])
{
	BiTree T;

	printf("=== 二叉树加权路径长度（WPL）计算演示 ===\n\n");

	printf("二叉树结构:\n");
	printf("          100\n");
	printf("         /   \\\n");
	printf("       42     58\n");
	printf("      /  \\   /  \\\n");
	printf("    15  27 28  30\n");
	printf("           / \\\n");
	printf("         13  15\n");
	printf("         / \\\n");
	printf("        5   8\n\n");

	// 创建二叉树
	printf("正在创建带权重的二叉树...\n");
	createTree(&T);

	// 计算WPL
	int w = wpl(T);
	printf("\n树的加权路径长度（WPL）为: %d\n", w);

	printf("\nWPL计算说明:\n");
	printf("- WPL = Σ (叶子节点权重 × 叶子节点深度)\n");
	printf("- 只有叶子节点才计入WPL\n");
	printf("- 深度从0开始计数（根节点深度为0）\n");

	printf("\n叶子节点贡献:\n");
	printf("- 15 × 2 = 30\n");
	printf("- 27 × 2 = 54\n");
	printf("- 5  × 4 = 20\n");
	printf("- 8  × 4 = 32\n");
	printf("- 15 × 3 = 45\n");
	printf("- 30 × 2 = 60\n");
	printf("总和: 30+54+20+32+45+60 = 241\n");

	printf("\nWPL应用场景:\n");
	printf("- 哈夫曼编码（数据压缩）\n");
	printf("- 最优二叉树（WPL最小）\n");
	printf("- 决策树代价分析\n");

	printf("\n=== 计算完成 ===\n");

	// TODO: 释放树的内存

	system("pause");
	return 0;
}
