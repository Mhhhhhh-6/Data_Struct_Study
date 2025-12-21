/**
 * ===========================================================================
 * 文件名: graph_mst_prim.c
 * 描述:   最小生成树 - Prim算法实现
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   实现Prim算法求无向带权图的最小生成树（Minimum Spanning Tree, MST）
 *
 * 什么是最小生成树?
 *   - 连通图的生成树：包含所有顶点的无环连通子图
 *   - 最小生成树：所有边权重之和最小的生成树
 *   - 性质：n个顶点的MST有n-1条边
 *
 * Prim算法思想:
 *   1. 从任意顶点开始，将其加入MST
 *   2. 重复以下步骤n-1次：
 *      - 选择连接MST内外顶点的最小权重边
 *      - 将该边和新顶点加入MST
 *      - 更新候选边集合
 *   3. 贪心策略：每次选择当前最优解
 *
 * 时间复杂度: O(V²) - 适合稠密图
 * 空间复杂度: O(V)
 *
 * 使用方法:
 *   编译: gcc graph_mst_prim.c -o prim
 *   运行: ./prim (Linux/Mac) 或 prim.exe (Windows)
 *
 * 难度: ⭐⭐⭐⭐（贪心算法 + 图论）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAX 0x7fffffff  // 无穷大

typedef struct
{
	VertexType vertex[MAXSIZE];
	EdgeType arc[MAXSIZE][MAXSIZE];
	int vertex_num;
	int edge_num;
}Mat_Graph;

/**
 * 函数: create_graph
 * 功能: 创建带权无向图
 *
 * 图结构（带权重）:
 *   顶点: A B C D E F G H I
 *   边权重: 如A-B权重10, A-F权重11等
 */
void create_graph(Mat_Graph* G)
{
	G->vertex_num = 9;
	G->edge_num = 15;

	// 初始化顶点
	G->vertex[0] = 'A';
	G->vertex[1] = 'B';
	G->vertex[2] = 'C';
	G->vertex[3] = 'D';
	G->vertex[4] = 'E';
	G->vertex[5] = 'F';
	G->vertex[6] = 'G';
	G->vertex[7] = 'H';
	G->vertex[8] = 'I';

	// 初始化邻接矩阵（无穷大表示不相邻）
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			if (i == j)
			{
				G->arc[i][j] = 0;
			}
			else
			{
				G->arc[i][j] = MAX;  // 不相邻
			}
		}
	}

	// 添加带权边
	G->arc[0][1] = 10;  // A-B: 10
	G->arc[0][5] = 11;  // A-F: 11

	G->arc[1][2] = 18;  // B-C: 18
	G->arc[1][6] = 16;  // B-G: 16
	G->arc[1][8] = 12;  // B-I: 12

	G->arc[2][3] = 22;  // C-D: 22
	G->arc[2][8] = 8;   // C-I: 8

	G->arc[3][4] = 20;  // D-E: 20
	G->arc[3][6] = 24;  // D-G: 24
	G->arc[3][7] = 16;  // D-H: 16
	G->arc[3][8] = 21;  // D-I: 21

	G->arc[4][5] = 26;  // E-F: 26
	G->arc[4][7] = 7;   // E-H: 7

	G->arc[5][6] = 17;  // F-G: 17

	G->arc[6][7] = 19;  // G-H: 19

	// 对称化（无向图）
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

/**
 * 函数: prim
 * 功能: Prim算法求最小生成树
 *
 * 参数:
 *   @param G - 图指针
 *
 * 算法思路:
 *   1. 初始化：从顶点A开始，weight[i]存储A到i的边权重
 *   2. 重复n-1次：
 *      a. 在候选边中选择权重最小的边
 *      b. 将该边加入MST（打印）
 *      c. 更新候选边集合（新顶点的所有边）
 *
 * weight[i]: MST到顶点i的最小权重（0表示i已在MST中）
 * vex_index[i]: MST中连接到顶点i的顶点索引
 *
 * 示例：
 *   初始（从A开始）:
 *   weight = [0, 10, MAX, MAX, MAX, 11, MAX, MAX, MAX]
 *   选择最小边A-B(10), B加入MST
 *   更新weight = [0, 0, 18, MAX, MAX, 11, 16, MAX, 12]
 *   选择最小边A-F(11), F加入MST
 *   ...依此类推
 */
void prim(Mat_Graph* G)
{
	int i, j, k;
	int min;
	int weight[MAXSIZE];       // 候选边权重
	int vex_index[MAXSIZE];    // 候选边起点

	// 1. 初始化：从顶点A（索引0）开始
	weight[0] = 0;             // A在MST中
	vex_index[0] = 0;

	// 初始化：A到其他顶点的权重
	for (i = 1; i < G->vertex_num; i++)
	{
		weight[i] = G->arc[0][i];
		vex_index[i] = 0;  // 都从A出发
	}

	// 2. 循环n-1次，每次加入一个顶点
	for (int i = 1; i < G->vertex_num; i++)
	{
		// 2a. 找最小权重边
		min = MAX;
		j = 0;
		k = 0;

		while(j < G->vertex_num)
		{
			// weight[j]!=0表示j不在MST中
			if (weight[j] != 0 && weight[j] < min)
			{
				min = weight[j];
				k = j;  // k是要加入的顶点
			}
			j++;
		}

		// 2b. 输出选中的边
		printf("边 (%c, %c) 权重: %d\n",
		       G->vertex[vex_index[k]], G->vertex[k], min);

		// 标记k已加入MST
		weight[k] = 0;

		// 2c. 更新候选边（k的所有邻接边）
		for (j = 0; j < G->vertex_num; j++)
		{
			// 如果j不在MST中，且k-j的边更小
			if (weight[j] != 0 && G->arc[k][j] < weight[j])
			{
				weight[j] = G->arc[k][j];
				vex_index[j] = k;
			}
		}
	}
}

/**
 * 主函数: 测试Prim算法
 *
 * 预期输出最小生成树的所有边
 */
int main(int argc, char const *argv[])
{
	Mat_Graph G;

	printf("=== 最小生成树 - Prim算法演示 ===\n\n");

	printf("正在创建带权无向图...\n");
	printf("顶点数: 9 (A-I)\n");
	printf("边数: 15\n\n");

	create_graph(&G);

	printf("Prim算法求最小生成树（从A开始）:\n");
	printf("================================\n");
	prim(&G);

	printf("\nPrim算法特点:\n");
	printf("- 贪心策略：每次选择最小权重边\n");
	printf("- 时间复杂度: O(V²)\n");
	printf("- 适合稠密图\n");

	printf("\n=== 算法完成 ===\n");

	system("pause");
	return 0;
}
