/**
 * ===========================================================================
 * 文件名: graph_traversal_dfs.c
 * 描述:   图的深度优先搜索（DFS）实现
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了图的深度优先搜索（Depth-First Search, DFS）：
 *   1. 使用邻接矩阵表示无向图
 *   2. 递归实现DFS算法
 *   3. 使用visited数组标记已访问顶点
 *
 * 什么是深度优先搜索（DFS）?
 *   - DFS是图的一种遍历算法
 *   - 从起始顶点开始，沿着一条路径尽可能深入
 *   - 当无法继续深入时，回溯到上一个顶点，探索其他路径
 *   - 类似于树的先序遍历
 *
 * DFS特点:
 *   - 使用递归实现（隐式使用系统栈）
 *   - 也可用显式栈实现（非递归版本）
 *   - 时间复杂度: O(V+E) - V为顶点数，E为边数
 *   - 空间复杂度: O(V) - visited数组 + 递归栈
 *
 * DFS vs BFS:
 *   ┌────────────┬─────────────┬─────────────┐
 *   │ 特性       │ DFS         │ BFS         │
 *   ├────────────┼─────────────┼─────────────┤
 *   │ 数据结构   │ 栈（递归）  │ 队列        │
 *   │ 遍历顺序   │ 深度优先    │ 广度优先    │
 *   │ 路径       │ 不一定最短  │ 最短路径    │
 *   │ 内存占用   │ 较小（深度）│ 较大（宽度）│
 *   │ 应用       │ 拓扑排序    │ 最短路径    │
 *   │            │ 连通性检测  │ 层次遍历    │
 *   └────────────┴─────────────┴─────────────┘
 *
 * 数据结构:
 *   - 邻接矩阵图：使用二维数组存储边的关系
 *   - visited数组：标记顶点是否已访问
 *
 * 示例图结构:
 *       A --- B --- C
 *       |     |     |
 *       F --- G --- D
 *             |     |
 *       E --- H     I
 *
 *   顶点: A B C D E F G H I (9个顶点)
 *   边数: 15条边（无向图）
 *
 * DFS遍历顺序（从A开始）:
 *   A → B → C → D → E → F → G → H → I
 *   （具体顺序取决于邻接矩阵中边的存储顺序）
 *
 * DFS应用场景:
 *   1. 判断图的连通性
 *   2. 查找路径
 *   3. 拓扑排序（有向无环图）
 *   4. 检测图中的环
 *   5. 迷宫问题求解
 *   6. 搜索树遍历
 *
 * 使用方法:
 *   编译: gcc graph_traversal_dfs.c -o graph_dfs
 *   运行: ./graph_dfs (Linux/Mac) 或 graph_dfs.exe (Windows)
 *
 * 难度: ⭐⭐⭐（递归 + 图遍历）
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
 *
 * 成员说明:
 *   - vertex[MAXSIZE]: 顶点数组
 *   - arc[MAXSIZE][MAXSIZE]: 邻接矩阵
 *     * arc[i][j] = 1: 顶点i和顶点j之间有边
 *     * arc[i][j] = 0: 顶点i和顶点j之间无边
 *   - vertex_num: 顶点数
 *   - edge_num: 边数
 *
 * 无向图特点:
 *   邻接矩阵是对称的，即 arc[i][j] == arc[j][i]
 */
typedef struct
{
	VertexType vertex[MAXSIZE];      // 顶点数组
	EdgeType arc[MAXSIZE][MAXSIZE];  // 邻接矩阵
	int vertex_num;                   // 顶点数
	int edge_num;                     // 边数
}Mat_Graph;

/**
 * 全局访问标记数组
 *
 * visited[i] = 0: 顶点i未访问
 * visited[i] = 1: 顶点i已访问
 *
 * 说明:
 *   使用全局数组简化递归函数参数
 *   在DFS开始前需要初始化为0
 */
int visited[MAXSIZE];

/**
 * 函数: create_graph
 * 功能: 创建无向图（邻接矩阵表示）
 *
 * 参数:
 *   @param G - 图指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 初始化顶点数和边数
 *   2. 初始化顶点数组（A-I共9个顶点）
 *   3. 初始化邻接矩阵为0（无边）
 *   4. 添加边（先添加一个方向）
 *   5. 对称化邻接矩阵（无向图特性）
 *
 * 图的结构:
 *       A --- B --- C
 *       |     |     |
 *       F --- G --- D
 *             |     |
 *       E --- H     I
 *
 * 边的连接关系:
 *   A: B, F
 *   B: A, C, G, I
 *   C: B, D, I
 *   D: C, E, G, H, I
 *   E: D, F, H
 *   F: A, E, G
 *   G: B, D, F, H
 *   H: D, E, G
 *   I: B, C, D
 *
 * 时间复杂度: O(V²) - 需要初始化邻接矩阵
 * 空间复杂度: O(V²) - 邻接矩阵
 */
void create_graph(Mat_Graph* G)
{
	// 1. 初始化顶点数和边数
	G->vertex_num = 9;
	G->edge_num = 15;

	// 2. 初始化顶点数组
	G->vertex[0] = 'A';
	G->vertex[1] = 'B';
	G->vertex[2] = 'C';
	G->vertex[3] = 'D';
	G->vertex[4] = 'E';
	G->vertex[5] = 'F';
	G->vertex[6] = 'G';
	G->vertex[7] = 'H';
	G->vertex[8] = 'I';

	// 3. 初始化邻接矩阵为0（无边）
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			G->arc[i][j] = 0;
		}
	}

	// 4. 添加边（先添加一个方向）
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

	// 5. 对称化邻接矩阵（无向图：arc[i][j] = arc[j][i]）
	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

/**
 * 函数: dfs
 * 功能: 深度优先搜索（递归实现）
 *
 * 参数:
 *   @param G - 图结构
 *   @param i - 当前访问的顶点索引
 *
 * 返回值: 无
 *
 * 算法思路:
 *   1. 标记当前顶点i为已访问
 *   2. 访问（打印）当前顶点
 *   3. 遍历所有顶点j：
 *      a. 如果i和j之间有边（arc[i][j] == 1）
 *      b. 且j未被访问（visited[j] == 0）
 *      c. 则递归访问j（深度优先）
 *   4. 递归终止条件：当前顶点的所有邻接顶点都已访问
 *
 * DFS递归过程示意:
 *   从A开始：
 *   1. 访问A，标记A已访问
 *   2. A的邻接顶点：B(未访问), F(未访问)
 *   3. 选择B（索引较小），递归访问B
 *      - 访问B，标记B已访问
 *      - B的邻接顶点：A(已访问), C(未访问), G(未访问), I(未访问)
 *      - 选择C，递归访问C
 *        * 访问C，标记C已访问
 *        * C的邻接顶点：B(已访问), D(未访问), I(未访问)
 *        * 选择D，递归访问D
 *          ... 继续深入
 *
 * 时间复杂度: O(V²) - 邻接矩阵需要遍历所有V²个元素
 *              （使用邻接表可优化为O(V+E)）
 * 空间复杂度: O(V) - 递归栈最深为V层
 *
 * 关键点:
 *   - visited数组防止重复访问和无限递归
 *   - 递归的本质是深度优先：先探索一条路径到底，再回溯
 *   - 每个顶点只被访问一次
 */
void dfs(Mat_Graph G, int i)
{
	// 1. 标记当前顶点为已访问
	visited[i] = 1;

	// 2. 访问当前顶点（打印）
	printf("%c ", G.vertex[i]);

	// 3. 遍历所有可能的邻接顶点
	for (int j = 0; j < G.vertex_num; j++)
	{
		// 3a. 如果i和j之间有边 且 j未被访问
		if (G.arc[i][j] == 1 && visited[j] == 0)
		{
			// 3b. 递归访问顶点j（深度优先）
			dfs(G, j);
		}
	}

	// 递归终止：当前顶点的所有邻接顶点都已访问
	// 函数返回，回溯到上一层递归
}

/**
 * 函数: dfsTraverse
 * 功能: 深度优先遍历（处理非连通图）
 *
 * 说明:
 *   如果图不是连通的（有多个连通分量）
 *   需要对每个未访问的顶点调用DFS
 *
 * 算法思路:
 *   for i = 0 to V-1:
 *     if visited[i] == 0:
 *       dfs(G, i)
 *
 * 本示例图是连通图，从任意顶点出发都能遍历所有顶点
 * 此函数在本例中不是必需的，但在非连通图中很重要
 */
void dfsTraverse(Mat_Graph *G)
{
	// 初始化visited数组
	for (int i = 0; i < G->vertex_num; i++)
	{
		visited[i] = 0;
	}

	// 对每个未访问的顶点调用DFS
	for (int i = 0; i < G->vertex_num; i++)
	{
		if (visited[i] == 0)
		{
			dfs(*G, i);
		}
	}
}

/**
 * 主函数: 测试DFS算法
 *
 * 测试流程:
 *   1. 创建无向图
 *   2. 初始化visited数组
 *   3. 从顶点A（索引0）开始DFS遍历
 *
 * 图结构:
 *       A --- B --- C
 *       |     |     |
 *       F --- G --- D
 *             |     |
 *       E --- H     I
 *
 * 预期输出（从A开始的DFS序列）:
 *   A B C D E F G H I
 *   （具体顺序可能因边的遍历顺序而异）
 *
 * DFS特点演示:
 *   - 深度优先：沿着一条路径尽可能深入
 *   - 回溯：无法继续时返回上一个顶点
 *   - 每个顶点仅访问一次
 */
int main(int argc, char const *argv[])
{
	Mat_Graph G;

	printf("=== 图的深度优先搜索（DFS）演示 ===\n\n");

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

	// 3. 从顶点A开始DFS遍历
	printf("DFS遍历序列（从顶点A开始）: ");
	dfs(G, 0);
	printf("\n");

	printf("\nDFS特点:\n");
	printf("- 深度优先：沿着一条路径尽可能深入\n");
	printf("- 使用递归实现（隐式栈）\n");
	printf("- 时间复杂度: O(V²) - 邻接矩阵\n");
	printf("- 空间复杂度: O(V) - 递归栈\n");

	printf("\n=== DFS遍历完成 ===\n");

	system("pause");
	return 0;
}
