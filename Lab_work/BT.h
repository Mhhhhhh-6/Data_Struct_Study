#ifndef BT_H
#define BT_H

#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
typedef struct node
{
    char data;              // 节点数据
    struct node *lchild;    // 左孩子指针
    struct node *rchild;    // 右孩子指针
} BTCHINALR;

// 函数声明
BTCHINALR* createbt();                    // 建立二叉树
void preorder(BTCHINALR *root);           // 先序遍历
void inorder(BTCHINALR *root);            // 中序遍历
void postorder(BTCHINALR *root);          // 后序遍历
void destroybt(BTCHINALR *root);          // 销毁二叉树
void displayTree(BTCHINALR *root, int space);  // 显示二叉树结构

#endif