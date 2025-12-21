/**
 * ===========================================================================
 * 文件名: binary_tree_traversal_stack.c
 * 描述:   二叉树的非递归遍历实现（栈模拟递归）
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了二叉树的非递归遍历方法：
 *   1. 先序遍历的非递归实现（iterPreOrder）
 *   2. 中序遍历的非递归实现（iterInOrder）
 *   3. 同时保留递归版本供对比
 *
 * 为什么需要非递归遍历?
 *   - 递归实现简洁优雅，但有递归调用的开销
 *   - 递归深度过大可能导致栈溢出
 *   - 非递归实现使用显式栈，更节省空间，更加高效
 *   - 在某些系统中，非递归实现是必需的
 *
 * 核心思想:
 *   用显式的栈结构模拟系统的递归调用栈
 *   将递归过程中的"回溯"操作用出栈来实现
 *
 * 数据结构:
 *   - 二叉树节点：包含data、lchild、rchild
 *   - 栈：存储BiTree类型（树节点指针），用于模拟递归
 *
 * 示例二叉树:
 *          A
 *        /   \
 *       B     C
 *      / \   / \
 *     D   E F   G
 *    /     /     \
 *   H     I       J
 *    \
 *     K
 *
 * 使用方法:
 *   编译: gcc binary_tree_traversal_stack.c -o traversal_stack
 *   运行: ./traversal_stack (Linux/Mac) 或 traversal_stack.exe (Windows)
 *
 * 难度: ⭐⭐⭐（栈的应用，非递归算法理解）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

// 节点数据类型定义
typedef char ElemType;

/**
 * 二叉树节点结构定义
 */
typedef struct TreeNode
{
	ElemType data;            // 节点数据
	struct TreeNode *lchild;  // 左孩子指针
	struct TreeNode *rchild;  // 右孩子指针
}TreeNode;

typedef TreeNode* BiTree;

/**
 * 栈结构定义（用于非递归遍历）
 *
 * 成员说明:
 *   - data: 存储BiTree类型的数组（树节点指针）
 *   - top: 栈顶指针，-1表示空栈
 *
 * 栈的作用:
 *   模拟递归调用栈，保存需要回溯的节点
 */
typedef struct
{
	BiTree *data;  // 存储树节点指针的数组
	int top;       // 栈顶指针
}Stack;

// 全局变量：先序序列和索引
char str[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;

/**
 * 函数: initStack
 * 功能: 初始化栈
 *
 * 返回值: 返回指向新创建栈的指针
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(MAXSIZE)
 */
Stack* initStack()
{
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->data = (BiTree*)malloc(sizeof(BiTree) * MAXSIZE);
	s->top = -1;  // 空栈标志
	return s;
}

/**
 * 函数: isEmpty
 * 功能: 判断栈是否为空
 *
 * 返回值:
 *   1 - 栈为空
 *   0 - 栈不为空
 *
 * 时间复杂度: O(1)
 */
int isEmpty(Stack *s)
{
	if (s->top == -1)
	{
		return 1;  // 栈为空
	}
	else
	{
		return 0;  // 栈不为空
	}
}

/**
 * 函数: push
 * 功能: 入栈操作
 *
 * 参数:
 *   @param s - 栈指针
 *   @param e - 要入栈的树节点指针
 *
 * 返回值:
 *   1 - 入栈成功
 *   0 - 入栈失败（栈满）
 *
 * 时间复杂度: O(1)
 */
int push(Stack *s, BiTree e)
{
	// 检查栈是否已满
	if (s->top >= MAXSIZE - 1)
	{
		printf("栈满\n");
		return 0;
	}

	// 入栈
	s->top++;
	s->data[s->top] = e;
	return 1;
}

/**
 * 函数: pop
 * 功能: 出栈操作
 *
 * 参数:
 *   @param s - 栈指针
 *   @param e - 用于存储出栈元素的指针
 *
 * 返回值:
 *   1 - 出栈成功
 *   0 - 出栈失败（栈空）
 *
 * 时间复杂度: O(1)
 */
int pop(Stack *s, BiTree *e)
{
	// 检查栈是否为空
	if (s->top == -1)
	{
		return 0;  // 栈空，出栈失败
	}

	// 出栈
	*e = s->data[s->top];
	s->top--;
	return 1;
}

/**
 * 函数: getTop
 * 功能: 获取栈顶元素（不出栈）
 *
 * 返回值:
 *   1 - 获取成功
 *   0 - 获取失败（栈空）
 *
 * 时间复杂度: O(1)
 */
int getTop(Stack *s, BiTree *e)
{
	if (s->top == -1)
	{
		return 0;
	}
	*e = s->data[s->top];
	return 1;
}

/**
 * 函数: createTree
 * 功能: 根据先序遍历序列创建二叉树
 *
 * （注释详见binary_tree_traversal_recursive.c）
 */
void createTree(BiTree *T)
{
	ElemType ch;
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
 * 函数: preOrder
 * 功能: 先序遍历（递归实现，供对比）
 *
 * （注释详见binary_tree_traversal_recursive.c）
 */
void preOrder(BiTree T)
{
	if (T == NULL)
	{
		return;
	}
	printf("%c ", T->data);
	preOrder(T->lchild);
	preOrder(T->rchild);
}

/**
 * 函数: inOrder
 * 功能: 中序遍历（递归实现，供对比）
 *
 * （注释详见binary_tree_traversal_recursive.c）
 */
void inOrder(BiTree T)
{
	if (T == NULL)
	{
		return;
	}
	inOrder(T->lchild);
	printf("%c ", T->data);
	inOrder(T->rchild);
}

/**
 * 函数: postOrder
 * 功能: 后序遍历（递归实现，供对比）
 *
 * （注释详见binary_tree_traversal_recursive.c）
 */
void postOrder(BiTree T)
{
	if (T == NULL)
	{
		return;
	}
	postOrder(T->lchild);
	postOrder(T->rchild);
	printf("%c ", T->data);
}

/**
 * 函数: iterPreOrder
 * 功能: 先序遍历的非递归实现（使用栈）
 *
 * 参数:
 *   @param s - 栈指针
 *   @param T - 二叉树根节点指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 当前节点不为空或栈不为空时循环：
 *      a. 沿着左子树一路向下，每遇到一个节点：
 *         - 访问该节点（打印）
 *         - 将该节点入栈（为了后续能回到它访问右子树）
 *         - 移动到左孩子
 *      b. 当左子树走到底（NULL）时：
 *         - 从栈中弹出一个节点
 *         - 转向其右子树
 *
 * 核心逻辑:
 *   先序遍历顺序是"根→左→右"
 *   - 访问节点时立即打印（根）
 *   - 左子树通过循环一路走到底（左）
 *   - 栈保存的是"待访问右子树"的节点
 *   - 出栈后访问右子树（右）
 *
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(h) - 栈的最大深度为树高h
 *
 * 示例:
 *   二叉树:      A
 *             /   \
 *            B     C
 *           / \
 *          D   E
 *
 *   执行过程:
 *   1. 访问A，入栈A，向左→B
 *   2. 访问B，入栈B，向左→D
 *   3. 访问D，入栈D，向左→NULL
 *   4. 出栈D，向右→NULL
 *   5. 出栈B，向右→E
 *   6. 访问E，入栈E，向左→NULL
 *   7. 出栈E，向右→NULL
 *   8. 出栈A，向右→C
 *   9. 访问C，入栈C，向左→NULL
 *   10. 出栈C，向右→NULL
 *   输出: A B D E C
 */
void iterPreOrder(Stack *s, BiTree T)
{
	// 外层循环：当前节点不为空 或 栈不为空
	// (栈不为空表示还有节点的右子树没访问)
	while(T != NULL || !isEmpty(s))
	{
		// 内层循环：沿左子树一路向下
		while(T != NULL)
		{
			// 先序：访问节点（根）
			printf("%c ", T->data);

			// 将节点入栈（保存，以便访问右子树）
			push(s, T);

			// 移动到左孩子
			T = T->lchild;
		}

		// 左子树访问完毕，出栈一个节点
		pop(s, &T);

		// 转向右子树
		T = T->rchild;
	}
}

/**
 * 函数: iterInOrder
 * 功能: 中序遍历的非递归实现（使用栈）
 *
 * 参数:
 *   @param s - 栈指针
 *   @param T - 二叉树根节点指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 当前节点不为空或栈不为空时循环：
 *      a. 沿着左子树一路向下，每遇到一个节点：
 *         - 将该节点入栈（先不访问）
 *         - 移动到左孩子
 *      b. 当左子树走到底（NULL）时：
 *         - 从栈中弹出一个节点
 *         - 访问该节点（打印）
 *         - 转向其右子树
 *
 * 与iterPreOrder的区别:
 *   - iterPreOrder: 入栈时就访问（打印）节点
 *   - iterInOrder: 出栈时才访问（打印）节点
 *
 * 核心逻辑:
 *   中序遍历顺序是"左→根→右"
 *   - 先遍历左子树（左）- 通过循环走到底
 *   - 左子树遍历完，出栈访问根节点（根）
 *   - 再遍历右子树（右）
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(h)
 *
 * 示例:
 *   二叉树:      A
 *             /   \
 *            B     C
 *           / \
 *          D   E
 *
 *   执行过程:
 *   1. 入栈A，向左→B
 *   2. 入栈B，向左→D
 *   3. 入栈D，向左→NULL
 *   4. 出栈D，访问D，向右→NULL
 *   5. 出栈B，访问B，向右→E
 *   6. 入栈E，向左→NULL
 *   7. 出栈E，访问E，向右→NULL
 *   8. 出栈A，访问A，向右→C
 *   9. 入栈C，向左→NULL
 *   10. 出栈C，访问C，向右→NULL
 *   输出: D B E A C
 */
void iterInOrder(Stack *s, BiTree T)
{
	// 外层循环：当前节点不为空 或 栈不为空
	while(T != NULL || !isEmpty(s))
	{
		// 内层循环：沿左子树一路向下
		while(T != NULL)
		{
			// 将节点入栈（先不访问）
			push(s, T);

			// 移动到左孩子
			T = T->lchild;
		}

		// 左子树访问完毕，出栈一个节点
		pop(s, &T);

		// 中序：访问节点（根）
		printf("%c ", T->data);

		// 转向右子树
		T = T->rchild;
	}
}

/**
 * 主函数: 测试非递归遍历
 *
 * 测试流程:
 *   1. 创建二叉树
 *   2. 执行递归先序遍历（对比）
 *   3. 执行非递归先序遍历
 *   4. 执行递归中序遍历（对比）
 *   5. 执行非递归中序遍历
 *
 * 预期输出:
 *   递归和非递归的结果应该完全一致
 */
int main(int argc, char const *argv[])
{
	BiTree T;
	Stack *s = initStack();

	printf("=== 二叉树非递归遍历演示 ===\n\n");
	printf("二叉树结构:\n");
	printf("         A\n");
	printf("       /   \\\n");
	printf("      B     C\n");
	printf("     / \\   / \\\n");
	printf("    D   E F   G\n");
	printf("   /     /     \\\n");
	printf("  H     I       J\n");
	printf("   \\\n");
	printf("    K\n\n");

	// 创建二叉树
	createTree(&T);

	// 先序遍历对比
	printf("【先序遍历】\n");
	printf("递归版本:    ");
	preOrder(T);
	printf("\n");

	printf("非递归版本:  ");
	iterPreOrder(s, T);
	printf("\n\n");

	// 中序遍历对比
	printf("【中序遍历】\n");
	printf("递归版本:    ");
	inOrder(T);
	printf("\n");

	// 重新初始化栈（因为栈已被先序遍历使用）
	s->top = -1;

	printf("非递归版本:  ");
	iterInOrder(s, T);
	printf("\n\n");

	// 后序遍历（仅递归版本）
	printf("【后序遍历】\n");
	printf("递归版本:    ");
	postOrder(T);
	printf("\n");
	printf("(后序非递归实现较复杂，本例未实现)\n");

	printf("\n=== 遍历完成 ===\n");

	// TODO: 释放栈和树的内存
	free(s->data);
	free(s);

	system("pause");
	return 0;
}
