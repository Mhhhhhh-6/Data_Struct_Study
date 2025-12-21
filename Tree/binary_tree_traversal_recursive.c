/**
 * ===========================================================================
 * 文件名: binary_tree_traversal_recursive.c
 * 描述:   二叉树的递归遍历实现
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了二叉树的三种递归遍历方法：
 *   1. 先序遍历（Preorder Traversal）：根 → 左子树 → 右子树
 *   2. 中序遍历（Inorder Traversal）： 左子树 → 根 → 右子树
 *   3. 后序遍历（Postorder Traversal）：左子树 → 右子树 → 根
 *
 * 数据结构:
 *   二叉树节点包含：
 *   - data: 节点数据（字符型）
 *   - lchild: 左孩子指针
 *   - rchild: 右孩子指针
 *
 * 二叉树创建方法:
 *   采用先序遍历序列创建二叉树
 *   输入格式：字符串形式，'#'表示空节点
 *
 * 示例二叉树结构:
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
 * 先序序列: ABDH#K###E##CFI###G#J##
 * 遍历结果:
 *   - 先序: A B D H K E C F I G J
 *   - 中序: H K D B E A I F C G J
 *   - 后序: K H D E B I F J G C A
 *
 * 三种遍历的应用场景:
 *   - 先序遍历: 复制树、生成树的先序表达式
 *   - 中序遍历: 二叉搜索树的中序遍历得到有序序列
 *   - 后序遍历: 计算表达式树的值、释放树的内存
 *
 * 使用方法:
 *   编译: gcc binary_tree_traversal_recursive.c -o traversal_recursive
 *   运行: ./traversal_recursive (Linux/Mac) 或 traversal_recursive.exe (Windows)
 *
 * 难度: ⭐⭐（二叉树基础，递归算法入门）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 节点数据类型定义
typedef char ElemType;

/**
 * 二叉树节点结构定义
 *
 * 成员说明:
 *   - data: 节点数据域
 *   - lchild: 左孩子指针
 *   - rchild: 右孩子指针
 */
typedef struct TreeNode
{
	ElemType data;            // 节点数据
	struct TreeNode *lchild;  // 左孩子指针
	struct TreeNode *rchild;  // 右孩子指针
}TreeNode;

// 二叉树类型定义
typedef TreeNode* BiTree;

/**
 * 全局变量:
 *   str: 先序遍历序列字符串，'#'表示空节点
 *   idx: 当前处理的字符索引
 *
 * 二叉树结构示意:
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
 * 对应的先序序列: ABDH#K###E##CFI###G#J##
 * 解析说明:
 *   A -> B -> D -> H -> # (H的左孩子为空)
 *             -> K -> # (K的左孩子为空)
 *                  -> # (K的右孩子为空)
 *             -> # (H的右孩子已经有K了，这是D的右孩子为空)
 *        -> E -> # (E的左孩子为空)
 *             -> # (E的右孩子为空)
 *   ...依此类推
 */
char str[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;

/**
 * 函数: createTree
 * 功能: 根据先序遍历序列创建二叉树（递归实现）
 *
 * 参数:
 *   @param T - 指向树根节点指针的指针（二级指针）
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 读取当前字符
 *   2. 如果是'#'，则当前节点为空（*T = NULL）
 *   3. 如果不是'#'，则创建节点：
 *      a. 分配内存
 *      b. 保存数据
 *      c. 递归创建左子树
 *      d. 递归创建右子树
 *
 * 时间复杂度: O(n) - n为节点总数，每个节点访问一次
 * 空间复杂度: O(h) - h为树高，递归栈深度
 *
 * 为什么使用二级指针?
 *   因为需要修改外部的树指针T本身，如果只传BiTree T（一级指针）
 *   在函数内修改T只会改变形参，不会影响实参
 *
 * 示例:
 *   输入序列: "AB##C##"
 *   构建结果:
 *        A
 *       / \
 *      B   C
 */
void createTree(BiTree *T)
{
	ElemType ch;
	// 1. 读取当前字符
	ch = str[idx++];

	// 2. 判断是否为空节点标记
	if (ch == '#')
	{
		*T = NULL;  // 空节点
	}
	else
	{
		// 3. 创建节点
		*T = (BiTree)malloc(sizeof(TreeNode));

		// 4. 保存数据
		(*T)->data = ch;

		// 5. 递归创建左子树
		createTree(&(*T)->lchild);

		// 6. 递归创建右子树
		createTree(&(*T)->rchild);
	}
}

/**
 * 函数: preOrder
 * 功能: 先序遍历二叉树（递归实现）
 *
 * 参数:
 *   @param T - 二叉树根节点指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 若树为空，直接返回
 *   2. 访问根节点（打印数据）
 *   3. 递归遍历左子树
 *   4. 递归遍历右子树
 *
 * 遍历顺序: 根 → 左子树 → 右子树（Root-Left-Right）
 *
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(h) - 递归栈深度为树高h
 *
 * 示例:
 *   二叉树:      A
 *             /   \
 *            B     C
 *           / \
 *          D   E
 *
 *   先序遍历结果: A B D E C
 *   执行过程:
 *     1. 访问A
 *     2. 遍历A的左子树:
 *        - 访问B
 *        - 遍历B的左子树: 访问D
 *        - 遍历B的右子树: 访问E
 *     3. 遍历A的右子树: 访问C
 *
 * 应用场景:
 *   - 复制一棵树
 *   - 生成树的先序表达式
 *   - 文件系统的先序遍历
 */
void preOrder(BiTree T)
{
	// 递归终止条件：空树直接返回
	if (T == NULL)
	{
		return;
	}

	// 1. 访问根节点
	printf("%c ", T->data);

	// 2. 递归遍历左子树
	preOrder(T->lchild);

	// 3. 递归遍历右子树
	preOrder(T->rchild);
}

/**
 * 函数: inOrder
 * 功能: 中序遍历二叉树（递归实现）
 *
 * 参数:
 *   @param T - 二叉树根节点指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 若树为空，直接返回
 *   2. 递归遍历左子树
 *   3. 访问根节点（打印数据）
 *   4. 递归遍历右子树
 *
 * 遍历顺序: 左子树 → 根 → 右子树（Left-Root-Right）
 *
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(h) - 递归栈深度为树高h
 *
 * 示例:
 *   二叉树:      A
 *             /   \
 *            B     C
 *           / \
 *          D   E
 *
 *   中序遍历结果: D B E A C
 *   执行过程:
 *     1. 遍历A的左子树:
 *        - 遍历B的左子树: 访问D
 *        - 访问B
 *        - 遍历B的右子树: 访问E
 *     2. 访问A
 *     3. 遍历A的右子树: 访问C
 *
 * 应用场景:
 *   - 二叉搜索树（BST）的中序遍历得到有序序列
 *   - 表达式树的中序遍历得到中缀表达式
 *
 * 重要特性:
 *   对于二叉搜索树，中序遍历结果是递增有序的
 */
void inOrder(BiTree T)
{
	// 递归终止条件：空树直接返回
	if (T == NULL)
	{
		return;
	}

	// 1. 递归遍历左子树
	inOrder(T->lchild);

	// 2. 访问根节点
	printf("%c ", T->data);

	// 3. 递归遍历右子树
	inOrder(T->rchild);
}

/**
 * 函数: postOrder
 * 功能: 后序遍历二叉树（递归实现）
 *
 * 参数:
 *   @param T - 二叉树根节点指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 若树为空，直接返回
 *   2. 递归遍历左子树
 *   3. 递归遍历右子树
 *   4. 访问根节点（打印数据）
 *
 * 遍历顺序: 左子树 → 右子树 → 根（Left-Right-Root）
 *
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(h) - 递归栈深度为树高h
 *
 * 示例:
 *   二叉树:      A
 *             /   \
 *            B     C
 *           / \
 *          D   E
 *
 *   后序遍历结果: D E B C A
 *   执行过程:
 *     1. 遍历A的左子树:
 *        - 遍历B的左子树: 访问D
 *        - 遍历B的右子树: 访问E
 *        - 访问B
 *     2. 遍历A的右子树: 访问C
 *     3. 访问A
 *
 * 应用场景:
 *   - 释放树的内存（必须先释放子节点，再释放父节点）
 *   - 计算表达式树的值（先计算子表达式，再计算根）
 *   - 文件系统的后序遍历（统计目录大小）
 *
 * 重要特性:
 *   后序遍历的最后一个节点一定是根节点
 *   适合需要"先处理子节点，再处理父节点"的场景
 */
void postOrder(BiTree T)
{
	// 递归终止条件：空树直接返回
	if (T == NULL)
	{
		return;
	}

	// 1. 递归遍历左子树
	postOrder(T->lchild);

	// 2. 递归遍历右子树
	postOrder(T->rchild);

	// 3. 访问根节点
	printf("%c ", T->data);
}

/**
 * 主函数: 测试二叉树的三种递归遍历
 *
 * 测试流程:
 *   1. 根据先序序列创建二叉树
 *   2. 执行先序遍历并输出
 *   3. 执行中序遍历并输出
 *   4. 执行后序遍历并输出
 *
 * 二叉树结构:
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
 * 预期输出:
 *   先序遍历: A B D H K E C F I G J
 *   中序遍历: H K D B E A I F C G J
 *   后序遍历: K H D E B I F J G C A
 *
 * 注意事项:
 *   本程序未实现内存释放（destroyTree函数）
 *   在实际应用中，应添加后序遍历释放内存的功能
 */
int main(int argc, char const *argv[])
{
	BiTree T;

	// 1. 创建二叉树
	printf("=== 二叉树递归遍历演示 ===\n\n");
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

	createTree(&T);

	// 2. 先序遍历
	printf("先序遍历 (根→左→右): ");
	preOrder(T);
	printf("\n");

	// 3. 中序遍历
	printf("中序遍历 (左→根→右): ");
	inOrder(T);
	printf("\n");

	// 4. 后序遍历
	printf("后序遍历 (左→右→根): ");
	postOrder(T);
	printf("\n");

	printf("\n=== 遍历完成 ===\n");

	// TODO: 应添加释放树内存的代码
	// destroyTree(T);

	system("pause");
	return 0;
}
