/**
 * ===========================================================================
 * 文件名: graph_traversal_bfs.c
 * 描述:   图的广度优先搜索（BFS）实现
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了图的广度优先搜索（Breadth-First Search, BFS）：
 *   1. 使用邻接矩阵表示无向图
 *   2. 使用队列实现BFS算法
 *   3. 使用visited数组标记已访问顶点
 *
 * 什么是广度优先搜索（BFS）?
 *   - BFS是图的一种遍历算法
 *   - 从起始顶点开始，先访问所有距离为1的顶点
 *   - 再访问所有距离为2的顶点，依此类推
 *   - 逐层扩展，类似于树的层序遍历
 *
 * BFS特点:
 *   - 使用队列实现（FIFO - 先进先出）
 *   - 层序遍历，逐层扩展
 *   - 可找到最短路径（无权图）
 *   - 时间复杂度: O(V+E) - V为顶点数，E为边数
 *   - 空间复杂度: O(V) - visited数组 + 队列
 *
 * BFS vs DFS对比:
 *   ┌────────────┬─────────────┬─────────────┐
 *   │ 特性       │ BFS         │ DFS         │
 *   ├────────────┼─────────────┼─────────────┤
 *   │ 数据结构   │ 队列        │ 栈（递归）  │
 *   │ 遍历方式   │ 逐层扩展    │ 深度优先    │
 *   │ 路径       │ 最短路径    │ 不一定最短  │
 *   │ 内存       │ 较大（宽度）│ 较小（深度）│
 *   │ 实现       │ 迭代（队列）│ 递归（栈）  │
 *   │ 应用       │ 最短路径    │ 拓扑排序    │
 *   │            │ 层次遍历    │ 连通性检测  │
 *   └────────────┴─────────────┴─────────────┘
 *
 * 数据结构:
 *   - 邻接矩阵图：使用二维数组存储边的关系
 *   - 队列：存储待访问的顶点索引
 *   - visited数组：标记顶点是否已访问
 *
 * 示例图结构:
 *       A --- B --- C
 *       |     |     |
 *       F --- G --- D
 *             |     |
 *       E --- H     I
 *
 * BFS遍历过程（从A开始）:
 *   层0: A
 *   层1: B, F（A的邻接顶点）
 *   层2: C, G（B的邻接顶点，F已在层1）, E（F的新邻接顶点）
 *   层3: D, I（C的邻接顶点）, H（G和E的邻接顶点）
 *   输出: A B F C G E I D H
 *
 * BFS应用场景:
 *   1. 寻找最短路径（无权图）
 *   2. 连通性检测
 *   3. 层次遍历
 *   4. 社交网络（查找最近的朋友）
 *   5. 网络爬虫
 *   6. 迷宫求最短路径
 *
 * 使用方法:
 *   编译: gcc graph_traversal_bfs.c -o graph_bfs
 *   运行: ./graph_bfs (Linux/Mac) 或 graph_bfs.exe (Windows)
 *
 * 难度: ⭐⭐⭐（队列 + 图遍历）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 顶点数据类型
typedef char VertexType;

// 边权重类型
typedef int EdgeType;

// 最大顶点数
#define MAXSIZE 100

/**
 * 邻接矩阵图结构定义
 */
typedef struct
{
	VertexType vertex[MAXSIZE];      // 顶点数组
	EdgeType arc[MAXSIZE][MAXSIZE];  // 邻接矩阵
	int vertex_num;                   // 顶点数
	int edge_num;                     // 边数
}Mat_Graph;

/**
 * 全局变量:
 *   visited[]: 访问标记数组
 *   queue[]: 队列（存储顶点索引）
 *   front: 队头指针
 *   rear: 队尾指针
 *
 * 队列操作:
 *   入队: queue[rear++] = vertex
 *   出队: vertex = queue[front++]
 *   队空: front == rear
 */
int visited[MAXSIZE];
int front = 0;
int rear = 0;
int queue[MAXSIZE];

/**
 * 函数: create_graph
 * 功能: 创建无向图（邻接矩阵表示）
 *
 * （注释详见graph_traversal_dfs.c）
 *
 * 图结构相同:
 *       A --- B --- C
 *       |     |     |
 *       F --- G --- D
 *             |     |
 *       E --- H     I
 */
void create_graph(Mat_Graph* G)
{
	G->vertex_num = 9;
	G->edge_num = 15;
	G->vertex[0] = 'A';
	G->vertex[1] = 'B';
	G->vertex[2] = 'C';
	G->vertex[3] = 'D';
	G->vertex[4] = 'E';
	G->vertex[5] = 'F';
	G->vertex[6] = 'G';
	G->vertex[7] = 'H';
	G->vertex[8] = 'I';

	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			G->arc[i][j] = 0;
		}
	}

	// A-B A-F
	G->arc[0][1] = 1;
	G->arc[0][5] = 1;

	// B-C B-G B-I
	G->arc[1][2] = 1;
	G->arc[1][6] = 1;
	G->arc[1][8] = 1;

	// C-D C-I
	G->arc[2][3] = 1;
	G->arc[2][8] = 1;

	// D-E D-G D-H D-I
	G->arc[3][4] = 1;
	G->arc[3][6] = 1;
	G->arc[3][7] = 1;
	G->arc[3][8] = 1;

	// E-F E-H
	G->arc[4][5] = 1;
	G->arc[4][7] = 1;

	// F-G
	G->arc[5][6] = 1;

	// G-H
	G->arc[6][7] = 1;

	// 对称化邻接矩阵
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

/**
 * 函数: bfs
 * 功能: 广度优先搜索（使用队列实现）
 *
 * 参数:
 *   @param G - 图结构
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 从起始顶点0开始
 *   2. 标记起始顶点为已访问
 *   3. 访问（打印）起始顶点
 *   4. 起始顶点入队
 *   5. 当队列不为空时循环：
 *      a. 出队一个顶点i
 *      b. 遍历i的所有邻接顶点j：
 *         - 如果j未访问且与i相邻
 *         - 标记j为已访问
 *         - 访问（打印）j
 *         - j入队
 *   6. 队列为空，遍历结束
 *
 * BFS过程示意（从A开始）:
 *   初始: 队列[], 访问A, 队列[A]
 *   步骤1: 出队A, 访问B和F, 队列[B,F]
 *   步骤2: 出队B, 访问C,G,I, 队列[F,C,G,I]
 *   步骤3: 出队F, 访问E, 队列[C,G,I,E]
 *   步骤4: 出队C, 访问D, 队列[G,I,E,D]
 *   步骤5: 出队G, 访问H, 队列[I,E,D,H]
 *   步骤6-9: 出队I,E,D,H（都没有新邻接顶点）
 *   结束: 队列为空
 *
 * 关键特点:
 *   - 使用队列保证先访问的顶点其邻接顶点先被遍历
 *   - 层序遍历：同一层的顶点先全部访问完
 *   - visited数组防止重复访问
 *
 * 时间复杂度: O(V²) - 邻接矩阵
 * 空间复杂度: O(V) - 队列最多存储V个顶点
 *
 * 与DFS的区别:
 *   - DFS用栈（递归），深度优先
 *   - BFS用队列，广度优先
 *   - BFS找到的路径是最短路径（边数最少）
 */
void bfs(Mat_Graph G)
{
	// 1. 从顶点0（A）开始
	int i = 0;

	// 2. 标记起始顶点为已访问
	visited[i] = 1;

	// 3. 访问起始顶点
	printf("%c ", G.vertex[i]);

	// 4. 起始顶点入队
	queue[rear] = i;
	rear++;

	// 5. 队列不为空时循环
	while(front != rear)
	{
		// 5a. 出队一个顶点
		i = queue[front];
		front++;

		// 5b. 遍历该顶点的所有邻接顶点
		for (int j = 0; j < G.vertex_num; j++)
		{
			// 如果j与i相邻 且 j未被访问
			if (G.arc[i][j] == 1 && visited[j] == 0)
			{
				// 标记j为已访问
				visited[j] = 1;

				// 访问j
				printf("%c ", G.vertex[j]);

				// j入队（后续会访问j的邻接顶点）
				queue[rear] = j;
				rear++;
			}
		}
	}

	// 6. 队列为空，遍历结束
}

/**
 * 主函数: 测试BFS算法
 *
 * 测试流程:
 *   1. 创建无向图
 *   2. 初始化visited数组
 *   3. 从顶点A（索引0）开始BFS遍历
 *
 * 图结构:
 *       A --- B --- C
 *       |     |     |
 *       F --- G --- D
 *             |     |
 *       E --- H     I
 *
 * 预期输出（从A开始的BFS序列）:
 *   A B F C G I E D H
 *   （按层序遍历，每层的顶点按索引顺序访问）
 *
 * BFS特点演示:
 *   - 广度优先：逐层扩展
 *   - 最短路径：先访问到的路径是最短路径
 *   - 队列实现：保证先进先出
 */
int main(int argc, char const *argv[])
{
	Mat_Graph G;

	printf("=== 图的广度优先搜索（BFS）演示 ===\n\n");

	// 1. 创建图
	printf("正在创建无向图...\n");
	create_graph(&G);

	printf("图的信息:\n");
	printf("- 顶点数: %d\n", G.vertex_num);
	printf("- 边数: %d\n", G.edge_num);
	printf("- 顶点: ");
	for (int i = 0; i < G.vertex_num; i++)
	{
		printf("%c ", G.vertex[i]);
	}
	printf("\n\n");

	printf("图的结构:\n");
	printf("      A --- B --- C\n");
	printf("      |     |     |\n");
	printf("      F --- G --- D\n");
	printf("            |     |\n");
	printf("      E --- H     I\n\n");

	// 2. 初始化visited数组
	for (int i = 0; i < G.vertex_num; i++)
	{
		visited[i] = 0;
	}

	// 3. 从顶点A开始BFS遍历
	printf("BFS遍历序列（从顶点A开始）: ");
	bfs(G);
	printf("\n");

	printf("\nBFS特点:\n");
	printf("- 广度优先：逐层扩展访问\n");
	printf("- 使用队列实现（FIFO）\n");
	printf("- 可找到最短路径（无权图）\n");
	printf("- 时间复杂度: O(V^2) - 邻接矩阵\n");
	printf("- 空间复杂度: O(V) - 队列\n");

	printf("\nBFS vs DFS:\n");
	printf("- BFS: 层序遍历，队列，最短路径\n");
	printf("- DFS: 深度遍历，栈/递归，深度优先\n");

	printf("\n=== BFS遍历完成 ===\n");

	system("pause");
	return 0;
}
