#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20
#define INF 0x3f3f3f3f

typedef char VertexData;

typedef struct {
    int adj;
} ArcCell;

typedef struct {
    VertexData vexs[MAX_VERTEX_NUM];
    ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum;
    int arcnum;
    int directed;
    int weighted;
} MGraph;

static void InitMatrix(MGraph *G) {
    for (int i = 0; i < G->vexnum; ++i) {
        for (int j = 0; j < G->vexnum; ++j) {
            if (G->weighted) {
                G->arcs[i][j].adj = (i == j) ? 0 : INF;
            } else {
                G->arcs[i][j].adj = 0;
            }
        }
    }
}

static int LocateVertex(const MGraph *G, VertexData v) {
    for (int i = 0; i < G->vexnum; ++i) {
        if (G->vexs[i] == v) {
            return i;
        }
    }
    return -1;
}

static void PrintAdjMatrix(const MGraph *G) {
    printf("邻接矩阵：\n");
    for (int i = 0; i < G->vexnum; ++i) {
        for (int j = 0; j < G->vexnum; ++j) {
            if (G->weighted && G->arcs[i][j].adj == INF) {
                printf(" INF ");
            } else {
                printf("%4d ", G->arcs[i][j].adj);
            }
        }
        printf("\n");
    }
}

static void CreateGraph(MGraph *G) {
    printf("请输入边数和顶点数（格式：边数 顶点数）：\n");
    if (scanf("%d %d", &G->arcnum, &G->vexnum) != 2 || G->vexnum <= 0 || G->vexnum > MAX_VERTEX_NUM) {
        printf("输入非法，创建失败。\n");
        return;
    }

    printf("请输入 %d 个顶点标识（单字符，中间空格分隔）：\n", G->vexnum);
    for (int i = 0; i < G->vexnum; ++i) {
        scanf(" %c", &G->vexs[i]);
    }

    InitMatrix(G);

    printf("请输入每条边的信息：\n");
    printf(G->weighted ? "格式：起点 终点 权值\n" : "格式：起点 终点\n");

    for (int k = 0; k < G->arcnum; ++k) {
        VertexData v1, v2;
        int weight = 1;
        if (G->weighted) {
            if (scanf(" %c %c %d", &v1, &v2, &weight) != 3) {
                printf("输入格式错误，重新输入该边。\n");
                --k;
                continue;
            }
        } else {
            if (scanf(" %c %c", &v1, &v2) != 2) {
                printf("输入格式错误，重新输入该边。\n");
                --k;
                continue;
            }
        }

        int i = LocateVertex(G, v1);
        int j = LocateVertex(G, v2);
        if (i == -1 || j == -1) {
            printf("顶点不存在，重新输入该边。\n");
            --k;
            continue;
        }

        G->arcs[i][j].adj = weight;
        if (!G->directed) {
            G->arcs[j][i].adj = weight;
        }
    }

    PrintAdjMatrix(G);
}

int main(void) {
    int choice;
    while (1) {
        printf("\n请选择图/网类型：\n");
        printf("0. 退出\n");
        printf("1. 有向图\n");
        printf("2. 无向网\n");
        printf("3. 有向网\n");
        printf("4. 无向图\n");
        printf("请输入选项：");
        if (scanf("%d", &choice) != 1) {
            printf("输入错误，程序结束。\n");
            break;
        }

        if (choice == 0) {
            printf("程序运行结束。\n");
            break;
        }

        MGraph G;
        switch (choice) {
            case 1:
                G.directed = 1;
                G.weighted = 0;
                CreateGraph(&G);
                break;
            case 2:
                G.directed = 0;
                G.weighted = 1;
                CreateGraph(&G);
                break;
            case 3:
                G.directed = 1;
                G.weighted = 1;
                CreateGraph(&G);
                break;
            case 4:
                G.directed = 0;
                G.weighted = 0;
                CreateGraph(&G);
                break;
            default:
                printf("无效选项，请重新输入。\n");
                break;
        }
    }
    system("pause");
    return 0;
}