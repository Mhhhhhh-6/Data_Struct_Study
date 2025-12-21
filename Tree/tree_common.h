/**
 * ===========================================================================
 * 文件名: tree_common.h
 * 描述:   树模块通用头文件定义
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件定义了树模块所有文件共用的数据结构和函数声明
 *   包括二叉树节点结构、线索二叉树节点结构、以及通用函数接口
 *
 * 使用方法:
 *   在树模块的C文件中包含此头文件：
 *   #include "tree_common.h"
 *
 * ===========================================================================
 */

#ifndef TREE_COMMON_H
#define TREE_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==================== 类型定义 ====================

/**
 * 树节点数据类型定义
 *
 * 说明:
 *   默认使用char类型，可根据需要修改为int等类型
 *   例如：typedef int TElemType;
 */
typedef char TElemType;

// ==================== 二叉树节点结构 ====================

/**
 * 二叉树节点结构定义
 *
 * 成员说明:
 *   - data: 节点数据域
 *   - lchild: 左孩子指针
 *   - rchild: 右孩子指针
 *
 * 示意图:
 *        [data]
 *       /      \
 *   lchild    rchild
 */
typedef struct TreeNode {
    TElemType data;           // 节点数据
    struct TreeNode *lchild;  // 左孩子指针
    struct TreeNode *rchild;  // 右孩子指针
} TreeNode, *BiTree;

// ==================== 线索二叉树节点结构 ====================

/**
 * 线索标志枚举
 *
 * Link(0): 指针指向孩子节点
 * Thread(1): 指针指向前驱/后继（线索）
 */
typedef enum {
    Link = 0,    // 指向孩子节点
    Thread = 1   // 指向前驱/后继
} PointerTag;

/**
 * 线索二叉树节点结构定义
 *
 * 成员说明:
 *   - data: 节点数据域
 *   - lchild: 左指针（可能指向左孩子或前驱）
 *   - rchild: 右指针（可能指向右孩子或后继）
 *   - ltag: 左指针标志（0=左孩子，1=前驱）
 *   - rtag: 右指针标志（0=右孩子，1=后继）
 *
 * 线索化的作用:
 *   利用二叉树的空指针域存储前驱/后继信息
 *   使得遍历可以不使用递归或栈，直接通过线索完成
 *
 * 示意图:
 *        [data]
 *       /      \
 *   lchild    rchild
 *   (ltag)    (rtag)
 */
typedef struct ThreadNode {
    TElemType data;               // 节点数据
    struct ThreadNode *lchild;    // 左指针
    struct ThreadNode *rchild;    // 右指针
    PointerTag ltag;              // 左标志：0-左孩子，1-前驱
    PointerTag rtag;              // 右标志：0-右孩子，1-后继
} ThreadNode, *ThreadTree;

// ==================== 队列结构（用于层序遍历）====================

/**
 * 队列节点结构（用于层序遍历）
 *
 * 说明:
 *   层序遍历需要使用队列存储树节点指针
 */
typedef struct QueueNode {
    BiTree data;                  // 存储树节点指针
    struct QueueNode *next;       // 下一个队列节点
} QueueNode;

/**
 * 队列结构定义
 */
typedef struct {
    QueueNode *front;  // 队头指针
    QueueNode *rear;   // 队尾指针
} Queue;

// ==================== 栈结构（用于非递归遍历）====================

/**
 * 栈节点结构（用于非递归遍历）
 *
 * 说明:
 *   非递归遍历需要使用栈模拟递归过程
 */
typedef struct StackNode {
    BiTree data;                  // 存储树节点指针
    struct StackNode *next;       // 下一个栈节点
} StackNode;

/**
 * 栈结构定义
 */
typedef struct {
    StackNode *top;  // 栈顶指针
} Stack;

// ==================== 通用函数声明 ====================

/**
 * 二叉树基本操作函数
 */

// 创建二叉树（先序输入，'#'表示空节点）
BiTree createTree();

// 销毁二叉树（释放所有节点内存）
void destroyTree(BiTree T);

// 判断二叉树是否为空
bool isEmpty(BiTree T);

// 计算二叉树的高度（深度）
int getHeight(BiTree T);

// 计算二叉树的节点总数
int getNodeCount(BiTree T);

// 计算二叉树的叶子节点数
int getLeafCount(BiTree T);

/**
 * 二叉树遍历函数
 */

// 先序遍历（递归）
void preOrder(BiTree T);

// 中序遍历（递归）
void inOrder(BiTree T);

// 后序遍历（递归）
void postOrder(BiTree T);

// 层序遍历
void levelOrder(BiTree T);

/**
 * 队列辅助函数（用于层序遍历）
 */

// 初始化队列
Queue* initQueue();

// 入队
void enqueue(Queue *q, BiTree node);

// 出队
BiTree dequeue(Queue *q);

// 判断队列是否为空
bool isQueueEmpty(Queue *q);

/**
 * 栈辅助函数（用于非递归遍历）
 */

// 初始化栈
Stack* initStack();

// 入栈
void push(Stack *s, BiTree node);

// 出栈
BiTree pop(Stack *s);

// 获取栈顶元素（不出栈）
BiTree getTop(Stack *s);

// 判断栈是否为空
bool isStackEmpty(Stack *s);

#endif // TREE_COMMON_H
