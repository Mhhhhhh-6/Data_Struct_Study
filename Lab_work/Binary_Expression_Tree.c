#include "BT.h"

// 建立二叉树
BTCHINALR* createbt()
{
    BTCHINALR *q;
    BTCHINALR *s[30];  // 存储节点指针的数组
    int j, i;
    char x;
    
    printf("建立二叉树，输入结点对应的编号和值,编号和值之间用逗号隔开\n");
    printf("编号从1开始，根节点编号为1，左孩子=父节点*2，右孩子=父节点*2+1\n");
    printf("输入0,$表示结束\n\n");
    
    printf("i,x = ");
    scanf("%d,%c", &i, &x);
    
    while(i != 0 && x != '$')
    {
        q = (BTCHINALR*)malloc(sizeof(BTCHINALR));  // 建立一个新结点q
        q->data = x;
        q->lchild = NULL;
        q->rchild = NULL;
        s[i] = q;  // q新结点地址存入s指针数组中
        
        if(i != 1)  // i = 1，对应的结点是根结点
        {
            j = i / 2;  // 求双亲结点的编号j
            if(i % 2 == 0)
                s[j]->lchild = q;  // q结点编号为偶数则挂在双亲结点j的左边
            else
                s[j]->rchild = q;  // q结点编号为奇数则挂在双亲结点j的右边
        }
        
        printf("i,x = ");
        scanf("%d,%c", &i, &x);
    }
    
    return s[1];  // 返回根结点地址
}

// 显示二叉树结构
void displayTree(BTCHINALR *root, int space)
{
    int i;
    if(root == NULL)
        return;
    
    space += 4;  // 增加缩进
    
    displayTree(root->rchild, space);  // 先打印右子树
    
    printf("\n");
    for(i = 4; i < space; i++)
        printf(" ");
    printf("%c\n", root->data);
    
    displayTree(root->lchild, space);  // 再打印左子树
}

// 先序遍历（根-左-右）
void preorder(BTCHINALR *root)
{
    if(root != NULL)
    {
        printf("%c ", root->data);     // 访问根节点
        preorder(root->lchild);        // 遍历左子树
        preorder(root->rchild);        // 遍历右子树
    }
}

// 中序遍历（左-根-右）
void inorder(BTCHINALR *root)
{
    if(root != NULL)
    {
        inorder(root->lchild);         // 遍历左子树
        printf("%c ", root->data);     // 访问根节点
        inorder(root->rchild);         // 遍历右子树
    }
}

// 后序遍历（左-右-根）
void postorder(BTCHINALR *root)
{
    if(root != NULL)
    {
        postorder(root->lchild);       // 遍历左子树
        postorder(root->rchild);       // 遍历右子树
        printf("%c ", root->data);     // 访问根节点
    }
}

// 销毁二叉树
void destroybt(BTCHINALR *root)
{
    if(root != NULL)
    {
        destroybt(root->lchild);
        destroybt(root->rchild);
        free(root);
    }
}

// 显示菜单
void showMenu()
{
    printf("\n========== 二叉树操作菜单 ==========\n");
    printf("1. 创建二叉树\n");
    printf("2. 显示二叉树结构\n");
    printf("3. 先序遍历\n");
    printf("4. 中序遍历\n");
    printf("5. 后序遍历\n");
    printf("6. 销毁二叉树\n");
    printf("0. 退出程序\n");
    printf("===================================\n");
    printf("请选择操作: ");
}

// 主函数
int main()
{
    BTCHINALR *root = NULL;
    int choice;
    
    printf("========== 二叉树遍历实验 ==========\n");
    
    while(1)
    {
        showMenu();
        scanf("%d", &choice);
        getchar();  // 清除输入缓冲区的换行符
        
        switch(choice)
        {
            case 1:
                if(root != NULL)
                {
                    printf("\n警告: 已存在二叉树，将先销毁原有二叉树!\n");
                    destroybt(root);
                    root = NULL;
                }
                root = createbt();
                if(root != NULL)
                    printf("\n二叉树创建成功!\n");
                else
                    printf("\n二叉树创建失败或为空!\n");
                break;
                
            case 2:
                if(root == NULL)
                {
                    printf("\n二叉树为空，请先创建二叉树!\n");
                }
                else
                {
                    printf("\n========== 二叉树结构 ==========\n");
                    displayTree(root, 0);
                    printf("\n");
                }
                break;
                
            case 3:
                if(root == NULL)
                {
                    printf("\n二叉树为空，请先创建二叉树!\n");
                }
                else
                {
                    printf("\n先序遍历结果: ");
                    preorder(root);
                    printf("\n");
                }
                break;
                
            case 4:
                if(root == NULL)
                {
                    printf("\n二叉树为空，请先创建二叉树!\n");
                }
                else
                {
                    printf("\n中序遍历结果: ");
                    inorder(root);
                    printf("\n");
                }
                break;
                
            case 5:
                if(root == NULL)
                {
                    printf("\n二叉树为空，请先创建二叉树!\n");
                }
                else
                {
                    printf("\n后序遍历结果: ");
                    postorder(root);
                    printf("\n");
                }
                break;
                
            case 6:
                if(root == NULL)
                {
                    printf("\n二叉树已经为空!\n");
                }
                else
                {
                    destroybt(root);
                    root = NULL;
                    printf("\n二叉树已销毁!\n");
                }
                break;
                
            case 0:
                if(root != NULL)
                {
                    destroybt(root);
                    printf("\n已清理资源。");
                }
                printf("程序结束，再见!\n");
                system("pause");
                return 0;
                
            default:
                printf("\n无效的选择，请重新输入!\n");
                break;
        }
    }
    
    return 0;
}
