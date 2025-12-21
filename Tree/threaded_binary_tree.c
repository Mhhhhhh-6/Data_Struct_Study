/**
 * ===========================================================================
 * 文件名: threaded_binary_tree.c
 * 描述:   线索二叉树的实现（中序线索化）
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了线索二叉树（Threaded Binary Tree），包括：
 *   1. 创建普通二叉树
 *   2. 中序线索化（利用空指针域存储前驱/后继信息）
 *   3. 基于线索的中序遍历（无需递归或栈）
 *
 * 什么是线索二叉树?
 *   - 普通二叉树有很多空指针域（n个节点有n+1个空指针）
 *   - 线索二叉树利用这些空指针存储节点的前驱/后继信息
 *   - 通过线索化，可以实现无需递归或栈的遍历
 *
 * 线索化的优势:
 *   1. 空间利用率高：利用空指针域存储遍历信息
 *   2. 遍历效率高：O(n)时间，O(1)空间（不需要栈）
 *   3. 查找前驱/后继方便：可以直接通过线索找到
 *
 * 线索标志（tag）:
 *   - ltag = 0: lchild指向左孩子
 *   - ltag = 1: lchild指向前驱（线索）
 *   - rtag = 0: rchild指向右孩子
 *   - rtag = 1: rchild指向后继（线索）
 *
 * 数据结构示意:
 *   普通节点:      [data]
 *                 /      \
 *             lchild    rchild
 *
 *   线索节点:      [data]
 *                 /      \
 *             lchild    rchild
 *             (ltag)    (rtag)
 *
 * 示例二叉树:
 *          A
 *        /   \
 *       B     C
 *      / \   / \
 *     D   E F   G
 *    / \  /
 *   H   I J
 *
 * 中序序列: H D I B J E A F C G
 * 线索化后，叶子节点的空指针会指向前驱/后继
 *
 * 使用方法:
 *   编译: gcc threaded_binary_tree.c -o threaded_tree
 *   运行: ./threaded_tree (Linux/Mac) 或 threaded_tree.exe (Windows)
 *
 * 难度: ⭐⭐⭐⭐（高级数据结构，理解线索化过程较难）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 节点数据类型定义
typedef char ElemType;

/**
 * 线索二叉树节点结构定义
 *
 * 成员说明:
 *   - data: 节点数据域
 *   - lchild: 左指针（可能指向左孩子或前驱）
 *   - rchild: 右指针（可能指向右孩子或后继）
 *   - ltag: 左标志（0=左孩子，1=前驱线索）
 *   - rtag: 右标志（0=右孩子，1=后继线索）
 *
 * 与普通二叉树的区别:
 *   多了ltag和rtag两个标志位，用于区分指针的含义
 */
typedef struct ThreadNode
{
	ElemType data;            // 节点数据
	struct ThreadNode *lchild; // 左指针
	struct ThreadNode *rchild; // 右指针
	int ltag;                 // 左标志：0-左孩子，1-前驱
	int rtag;                 // 右标志：0-右孩子，1-后继
}ThreadNode;

// 线索二叉树类型定义
typedef ThreadNode* ThreadTree;

/**
 * 全局变量:
 *   str: 先序遍历序列
 *   idx: 当前处理的字符索引
 *   prev: 指向当前节点的前驱节点（线索化过程中使用）
 *
 * 二叉树结构:
 *          A
 *        /   \
 *       B     C
 *      / \   / \
 *     D   E F   G
 *    / \  /
 *   H   I J
 *
 * 先序序列: ABDH##I##EJ###CF##G##
 * 中序序列: H D I B J E A F C G
 */
char str[] = "ABDH##I##EJ###CF##G##";
int idx = 0;

/**
 * prev指针的作用:
 *   在线索化过程中，prev始终指向当前节点的前驱
 *   这样可以在访问当前节点时，同时建立前驱和后继的线索
 */
ThreadTree prev;

/**
 * 函数: createTree
 * 功能: 根据先序序列创建二叉树
 *
 * 参数:
 *   @param T - 指向树根节点指针的指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 读取字符，'#'表示空节点
 *   2. 创建节点并保存数据
 *   3. 递归创建左子树，如果左孩子存在则ltag=0
 *   4. 递归创建右子树，如果右孩子存在则rtag=0
 *   5. 如果孩子不存在，tag默认值（后续线索化时会设置为1）
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(h) - 递归栈深度
 *
 * 注意:
 *   创建时只标记有孩子的情况（tag=0）
 *   空指针的tag在线索化时才会设置为1
 */
void createTree(ThreadTree *T)
{
	ElemType ch;
	// 读取当前字符
	ch = str[idx++];

	if (ch == '#')
	{
		// 空节点
		*T = NULL;
	}
	else
	{
		// 创建节点
		*T = (ThreadTree)malloc(sizeof(ThreadNode));
		(*T)->data = ch;

		// 递归创建左子树
		createTree(&(*T)->lchild);
		if ((*T)->lchild != NULL)
		{
			// 有左孩子，ltag=0
			(*T)->ltag = 0;
		}

		// 递归创建右子树
		createTree(&(*T)->rchild);
		if((*T)->rchild != NULL)
		{
			// 有右孩子，rtag=0
			(*T)->rtag = 0;
		}
	}
}

/**
 * 函数: threading
 * 功能: 具体的线索化操作（中序线索化）
 *
 * 参数:
 *   @param T - 当前处理的节点指针
 *
 * 返回值: 无
 *
 * 算法思路（中序遍历的线索化）:
 *   1. 递归线索化左子树
 *   2. 处理当前节点：
 *      a. 如果当前节点的lchild为空，建立前驱线索：
 *         - ltag = 1
 *         - lchild = prev（指向前驱）
 *      b. 如果前驱节点的rchild为空，建立后继线索：
 *         - prev->rtag = 1
 *         - prev->rchild = T（前驱的后继是当前节点）
 *      c. 更新prev为当前节点
 *   3. 递归线索化右子树
 *
 * 核心思想:
 *   按照中序遍历的顺序访问节点
 *   在访问每个节点时，建立它与前驱节点之间的双向线索
 *
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(h) - 递归栈深度
 *
 * 示例:
 *   中序序列: H D I B J E A F C G
 *   线索化过程:
 *   1. 访问H: H的lchild=NULL，指向前驱（head）
 *   2. 访问D: prev(H)的rchild=NULL，指向后继(D)
 *   3. 访问I: I的lchild=NULL，指向前驱(D)
 *              prev(D)的rchild已经指向I（在访问D时建立）
 *   ...依此类推
 */
void threading(ThreadTree T)
{
	if (T != NULL)
	{
		// 1. 递归线索化左子树
		threading(T->lchild);

		// 2. 处理当前节点
		// 2a. 如果当前节点的左孩子为空，建立前驱线索
		if (T->lchild == NULL)
		{
			T->ltag = 1;       // 标记为线索
			T->lchild = prev;  // 指向前驱
		}

		// 2b. 如果前驱节点的右孩子为空，建立后继线索
		if (prev->rchild == NULL)
		{
			prev->rtag = 1;    // 标记为线索
			prev->rchild = T;  // 前驱的后继是当前节点
		}

		// 2c. 更新prev为当前节点（为下一个节点做准备）
		prev = T;

		// 3. 递归线索化右子树
		threading(T->rchild);
	}
}

/**
 * 函数: inOrderThreading
 * 功能: 开始中序线索化（创建头节点并启动线索化）
 *
 * 参数:
 *   @param head - 指向头节点指针的指针
 *   @param T - 二叉树根节点指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 创建头节点（head）：
 *      - ltag = 0: head的lchild指向树根
 *      - rtag = 1: head的rchild指向中序遍历的最后一个节点
 *      - 初始时rchild指向自己
 *   2. 如果树为空：
 *      - head的lchild指向自己
 *   3. 如果树不为空：
 *      - head的lchild指向树根
 *      - prev初始化为head
 *      - 调用threading进行线索化
 *      - 处理最后一个节点：
 *        * 最后一个节点的rchild指向head（形成循环）
 *        * rtag = 1
 *      - head的rchild指向最后一个节点
 *
 * 头节点的作用:
 *   - 简化边界条件处理
 *   - 形成循环结构，便于遍历
 *   - lchild指向树根，rchild指向最后一个节点
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(h)
 *
 * 线索化后的结构示意:
 *   head ← → [第一个节点] ← → [第二个节点] ← → ... ← → [最后一个节点] ← → head
 *   形成一个双向线索链
 */
void inOrderThreading(ThreadTree *head, ThreadTree T)
{
	// 1. 创建头节点
	*head = (ThreadTree)malloc(sizeof(ThreadNode));
	(*head)->ltag = 0;     // lchild指向树根（不是线索）
	(*head)->rtag = 1;     // rchild指向最后一个节点（是线索）
	(*head)->rchild = (*head);  // 初始指向自己

	// 2. 处理空树情况
	if (T == NULL)
	{
		(*head)->lchild = *head;  // 空树，lchild也指向自己
	}
	else
	{
		// 3. 非空树的线索化
		// 3a. head的lchild指向树根
		(*head)->lchild = T;

		// 3b. prev初始化为head
		prev = (*head);

		// 3c. 开始线索化
		threading(T);

		// 3d. 处理最后一个节点
		// 最后一个节点的右孩子指向head（形成循环）
		prev->rchild = *head;
		prev->rtag = 1;

		// 3e. head的右孩子指向最后一个节点
		(*head)->rchild = prev;
	}
}

/**
 * 函数: inOrder
 * 功能: 使用线索进行中序遍历（无需递归或栈）
 *
 * 参数:
 *   @param T - 头节点指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. curr从头节点的lchild开始（树根）
 *   2. 循环直到curr回到头节点：
 *      a. 找到最左下的节点（沿着ltag=0一直向左）
 *      b. 访问该节点
 *      c. 沿着后继线索访问所有后继（rtag=1）
 *      d. 转向右子树（rtag=0）
 *   3. 重复步骤2，直到遍历完成
 *
 * 核心思想:
 *   - 先找到中序序列的第一个节点（最左下）
 *   - 通过后继线索依次访问后续节点
 *   - 遇到有右孩子的节点，转向右子树继续寻找最左下
 *
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(1) - 不需要递归或栈
 *
 * 优势:
 *   相比递归和栈实现，线索遍历不需要额外空间
 *   适合频繁遍历的场景
 *
 * 示例:
 *   中序序列: H D I B J E A F C G
 *   遍历过程:
 *   1. 从A开始，向左找到H（最左下）
 *   2. 访问H
 *   3. H的后继是D（通过线索），访问D
 *   4. D的后继是I（通过线索），访问I
 *   5. I的后继是B（通过线索），访问B
 *   6. B有右孩子E，转向E的子树，找到最左下J
 *   ...依此类推
 */
void inOrder(ThreadTree T)
{
	ThreadTree curr;

	// 从头节点的lchild开始（树根）
	curr = T->lchild;

	// 循环直到回到头节点
	while(curr != T)
	{
		// 1. 找到最左下的节点
		while(curr->ltag == 0)
		{
			curr = curr->lchild;
		}

		// 2. 访问该节点
		printf("%c ", curr->data);

		// 3. 沿着后继线索访问所有后继节点
		// 条件：rtag=1（是线索）且 rchild不是头节点
		while(curr->rtag == 1 && curr->rchild != T)
		{
			curr = curr->rchild;   // 移动到后继
			printf("%c ", curr->data);  // 访问后继
		}

		// 4. 转向右子树（rtag=0表示有右孩子）
		curr = curr->rchild;
	}
	printf("\n");
}

/**
 * 主函数: 测试线索二叉树
 *
 * 测试流程:
 *   1. 创建普通二叉树
 *   2. 进行中序线索化
 *   3. 基于线索进行中序遍历
 *
 * 二叉树结构:
 *          A
 *        /   \
 *       B     C
 *      / \   / \
 *     D   E F   G
 *    / \  /
 *   H   I J
 *
 * 预期输出:
 *   中序遍历结果: H D I B J E A F C G
 *
 * 线索二叉树的应用:
 *   1. 需要频繁遍历的场景（如表达式求值）
 *   2. 内存受限的环境（不能使用递归或栈）
 *   3. 需要快速查找前驱/后继的场景
 */
int main(int argc, char const *argv[])
{
	ThreadTree head;  // 头节点
	ThreadTree T;     // 树根

	printf("=== 线索二叉树演示 ===\n\n");
	printf("二叉树结构:\n");
	printf("         A\n");
	printf("       /   \\\n");
	printf("      B     C\n");
	printf("     / \\   / \\\n");
	printf("    D   E F   G\n");
	printf("   / \\  /\n");
	printf("  H   I J\n\n");

	// 1. 创建二叉树
	printf("正在创建二叉树...\n");
	createTree(&T);

	// 2. 进行中序线索化
	printf("正在进行中序线索化...\n");
	inOrderThreading(&head, T);

	// 3. 基于线索进行中序遍历
	printf("\n基于线索的中序遍历结果: ");
	inOrder(head);

	printf("\n线索化优势:\n");
	printf("- 遍历无需递归或栈\n");
	printf("- 空间复杂度O(1)\n");
	printf("- 可快速查找前驱/后继\n");

	printf("\n=== 遍历完成 ===\n");

	// TODO: 释放树的内存

	system("pause");
	return 0;
}
