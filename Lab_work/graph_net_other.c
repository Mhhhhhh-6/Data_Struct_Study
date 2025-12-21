#include "stdlib.h"
#include "stdio.h"
#define MAX_VERTEX_NUM 10
#define INFINITY 32768
#define True 1
#define False 0
#define Error -1
#define Ok 1

typedef enum{DG, DN, UDG, UDN} GraphKind;
typedef char VertexData;
typedef struct ArcNode
{
    int adj;
} ArcNode;

typedef struct
{
    VertexData vexs[MAX_VERTEX_NUM];
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphKind kind;
} AdjMatrix;

// 求顶点位置函数
int LocateVertex(AdjMatrix *G, VertexData v)
{
    int j=Error, k;
    for(k=0; k<G->vexnum; k++)
        if(G->vexs[k] == v)
        {
            j=k;
            break;
        }
    return(j);
}

// 菜单显示
void menu()
{
    printf("*******************************************************\n");
    printf("1、输入有向网。\n");
    printf("2、输入无向网。\n");
    printf("3、输入有向图。\n");
    printf("4、输入无向图。\n");
    printf("0、退出。\n");
    printf("*******************************************************\n");
    printf("请输入命令序号：\n");
}

// 创建一个有向网
int CreateDN(AdjMatrix *G)
{
    int i, j, k, weight;
    VertexData v1, v2;
    printf("您选择的是输入有向网！\n");
    printf("请输入有向网的弧数和顶点数\n");
    fflush(stdin);
    scanf("%d,%d", &G->arcnum, &G->vexnum); /*输入图的顶点数和弧数*/
    
    for(i=0; i<G->vexnum; i++)          /*初始化邻接矩阵*/
        for(j=0; j<G->vexnum; j++)
            G->arcs[i][j].adj = INFINITY;
            
    for(i=0; i<G->vexnum; i++)
    {
        printf("输入图的顶点\n");
        fflush(stdin);
        scanf("%c", &G->vexs[i]);   /* 输入图的顶点*/
    }
    
    for(k=0; k<G->arcnum; k++)
    {
        printf("输入一条弧的两个顶点及权值\n");
        fflush(stdin);
        scanf("%c,%c,%d", &v1, &v2, &weight); /*输入一条弧的两个顶点及权值*/
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].adj = weight;   /*建立弧*/
    }
    return(Ok);
}

// 创建一个无向网
int CreateUDN(AdjMatrix *G)
{
    int i, j, k, weight;
    VertexData v1, v2;
    printf("您选择的是输入无向网！\n");
    printf("请输入无向网的边数和顶点数\n");
    fflush(stdin);
    scanf("%d,%d", &G->arcnum, &G->vexnum); /*输入图的顶点数和弧数*/
    
    for(i=0; i<G->vexnum; i++)          /*初始化邻接矩阵*/
        for(j=0; j<G->vexnum; j++)
            G->arcs[i][j].adj = INFINITY;
            
    for(i=0; i<G->vexnum; i++)
    {
        printf("输入图的顶点\n");
        fflush(stdin);
        scanf("%c", &G->vexs[i]);   /* 输入图的顶点*/
    }
    
    for(k=0; k<G->arcnum; k++)
    {
        printf("输入一条边的两个顶点及权值\n");
        fflush(stdin);
        scanf("%c,%c,%d", &v1, &v2, &weight); /*输入一条弧的两个顶点及权值*/
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].adj = weight;   /*建立边*/
        G->arcs[j][i].adj = weight;   /*建立边*/
    }
    return(Ok);
}

// 创建一个有向图
int CreateDG(AdjMatrix *G)
{
    int i, j, k;
    VertexData v1, v2;
    printf("您选择的是输入有向图！\n");
    printf("请输入有向图的弧数和顶点数\n");
    fflush(stdin);
    scanf("%d,%d", &G->arcnum, &G->vexnum); /*输入图的顶点数和弧数*/
    
    for(i=0; i<G->vexnum; i++)          /*初始化邻接矩阵*/
        for(j=0; j<G->vexnum; j++)
            G->arcs[i][j].adj = 0;
            
    for(i=0; i<G->vexnum; i++)
    {
        printf("输入图的顶点\n");
        fflush(stdin);
        scanf("%c", &G->vexs[i]);   /* 输入图的顶点*/
    }
    
    for(k=0; k<G->arcnum; k++)
    {
        printf("输入一条弧的两个顶点:\n");
        fflush(stdin);
        scanf("%c,%c", &v1, &v2); /*输入一条弧的两个顶点*/
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].adj = 1;   /*建立弧*/
    }
    return(Ok);
}

// 创建一个无向图
int CreateUDG(AdjMatrix *G)
{
    int i, j, k;
    VertexData v1, v2;
    printf("您选择的是输入无向图！\n");
    printf("请输入无向图的边数和顶点数\n");
    fflush(stdin);
    scanf("%d,%d", &G->arcnum, &G->vexnum); /*输入图的顶点数和弧数*/
    
    for(i=0; i<G->vexnum; i++)          /*初始化邻接矩阵*/
        for(j=0; j<G->vexnum; j++)
            G->arcs[i][j].adj = 0;
            
    for(i=0; i<G->vexnum; i++)
    {
        printf("输入图的顶点:\n");
        fflush(stdin);
        scanf("%c", &G->vexs[i]);   /* 输入图的顶点*/
    }
    
    for(k=0; k<G->arcnum; k++)
    {
        printf("输入一条边的两个顶点:\n");
        fflush(stdin);
        scanf("%c,%c", &v1, &v2); /*输入一条弧的两个顶点*/ // 注意：这里原文代码有一处可能的错误，无向图不需要输入权重%d，代码中似乎多写了%d但参数只给了两个，我这里修正为只读取两个字符
        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);
        G->arcs[i][j].adj = 1;   /*建立边*/
        G->arcs[j][i].adj = 1;   /*建立边*/
    }
    return(Ok);
}

void Display(AdjMatrix *G)
{
    int i, j;
    printf("输出如下:\n");
    for(i=0; i<G->vexnum; i++)
    {
        for(j=0; j<G->vexnum; j++)
            printf("%d\t", G->arcs[i][j].adj);
        printf("\n");
    }
}

void function()
{
    AdjMatrix G;
    int i;
    menu();
    scanf("%d", &i);
    while(1)
    {
        switch(i)
        {
            case 1:{CreateDN(&G); Display(&G);} break;
            case 2:{CreateUDN(&G); Display(&G);} break;
            case 3:{CreateDG(&G); Display(&G);} break;
            case 4:{CreateUDG(&G); Display(&G);} break;
            case 0:exit(1);
            default:printf("输入的命令错误！请从新输入：\n");
        }
        menu();
        scanf("%d", &i);
    }
}

int main()
{
    function();
    return 0;
}