/**
 * ===========================================================================
 * 文件名: graph_mst_kruskal.c
 * 描述:   最小生成树 - Kruskal算法实现
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   实现Kruskal算法求无向带权图的最小生成树（MST）
 *
 * Kruskal算法思想:
 *   1. 将所有边按权重从小到大排序
 *   2. 依次选择权重最小的边：
 *      - 如果该边连接的两个顶点不在同一连通分量，加入MST
 *      - 否则跳过（会形成环）
 *   3. 重复直到选出n-1条边
 *   4. 使用并查集（Union-Find）检测是否形成环
 *
 * Kruskal vs Prim:
 *   ┌─────────┬──────────────┬──────────────┐
 *   │ 特性    │ Kruskal      │ Prim         │
 *   ├─────────┼──────────────┼──────────────┤
 *   │ 策略    │ 边优先       │ 顶点优先     │
 *   │ 数据结构│ 并查集+排序  │ 候选边数组   │
 *   │ 复杂度  │ O(ElogE)     │ O(V²)        │
 *   │ 适用    │ 稀疏图       │ 稠密图       │
 *   └─────────┴──────────────┴──────────────┘
 *
 * 时间复杂度: O(ElogE) - 主要在排序
 * 空间复杂度: O(E+V)
 *
 * 使用方法:
 *   编译: gcc graph_mst_kruskal.c -o kruskal
 *   运行: ./kruskal (Linux/Mac) 或 kruskal.exe (Windows)
 *
 * 难度: ⭐⭐⭐⭐（贪心 + 并查集）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAXEDGE 200
#define MAX 0x7fffffff

typedef struct
{
	VertexType vertex[MAXSIZE];
	EdgeType arc[MAXSIZE][MAXSIZE];
	int vertex_num;
	int edge_num;
}Mat_Graph;

/**
 * 边结构定义
 *
 * 成员说明:
 *   - beigin: 边的起点索引（注：原代码拼写错误，保留以一致）
 *   - end: 边的终点索引
 *   - weight: 边的权重
 */
typedef struct
{
	int beigin;  // 起点
	int end;     // 终点
	int weight;  // 权重
}Edge;

/**
 * 函数: create_graph
 * 功能: 创建带权无向图（同Prim算法）
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
			if (i == j)
			{
				G->arc[i][j] = 0;
			}
			else
			{
				G->arc[i][j] = MAX;
			}
		}
	}

	// 添加带权边（同Prim算法）
	G->arc[0][1] = 10;
	G->arc[0][5] = 11;

	G->arc[1][2] = 18;
	G->arc[1][6] = 16;
	G->arc[1][8] = 12;

	G->arc[2][3] = 22;
	G->arc[2][8] = 8;

	G->arc[3][4] = 20;
	G->arc[3][6] = 24;
	G->arc[3][7] = 16;
	G->arc[3][8] = 21;

	G->arc[4][5] = 26;
	G->arc[4][7] = 7;

	G->arc[5][6] = 17;

	G->arc[6][7] = 19;

	for (int i = 0; i < G->vertex_num; i++)
	{
		for (int j = 0; j < G->vertex_num; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

/**
 * 函数: swap
 * 功能: 交换两条边
 */
void swap(Edge* edges, int i, int j)
{
	int temp;
	temp = edges[i].beigin;
	edges[i].beigin = edges[j].beigin;
	edges[j].beigin = temp;

	temp = edges[i].end;
	edges[i].end = edges[j].end;
	edges[j].end = temp;

	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}

/**
 * 函数: sortEdges
 * 功能: 对边按权重排序（冒泡排序）
 *
 * 时间复杂度: O(E²) - 冒泡排序
 * 注：可优化为快速排序O(ElogE)
 */
void sortEdges(Edge edges[], int edge_num)
{
	for (int i = 0; i < edge_num; i++)
	{
		for (int j = i + 1; j < edge_num; j++)
		{
			if (edges[i].weight > edges[j].weight)
			{
				swap(edges, i, j);
			}
		}
	}
}

/**
 * 函数: find
 * 功能: 并查集的查找操作（找根节点）
 *
 * 参数:
 *   @param parent - 父节点数组
 *   @param index - 要查找的节点索引
 *
 * 返回值: 根节点索引
 *
 * 并查集表示:
 *   - parent[i] = 0: i是根节点
 *   - parent[i] > 0: i的父节点是parent[i]
 *
 * 算法思路:
 *   沿着parent链向上查找，直到找到根节点
 *
 * 时间复杂度: O(h) - h为树高
 * 注：可加入路径压缩优化为O(α(n))
 */
int find(int* parent, int index)
{
	while(parent[index] > 0)
	{
		index = parent[index];
	}
	return index;
}

/**
 * 函数: Kruskal
 * 功能: Kruskal算法求最小生成树
 *
 * 参数:
 *   @param G - 图结构
 *
 * 算法思路:
 *   1. 收集所有边到edges数组
 *   2. 对边按权重排序
 *   3. 初始化并查集（每个顶点自成一个集合）
 *   4. 遍历排序后的边：
 *      a. 查找边的两个端点所属的集合
 *      b. 如果不在同一集合：
 *         - 合并两个集合（parent[n] = m）
 *         - 将该边加入MST（打印）
 *      c. 如果在同一集合：
 *         - 跳过（会形成环）
 *   5. 重复直到选出n-1条边
 *
 * 示例:
 *   边排序: E-H(7), C-I(8), A-B(10), A-F(11), B-I(12), ...
 *   1. 选E-H(7): E和H不在同一集合，加入MST
 *   2. 选C-I(8): C和I不在同一集合，加入MST
 *   3. 选A-B(10): A和B不在同一集合，加入MST
 *   ...依此类推
 *
 * 并查集作用:
 *   快速判断两个顶点是否在同一连通分量
 *   防止形成环
 */
void Kruskal(Mat_Graph G)
{
	Edge edges[MAXEDGE];
	int k = 0;

	// 1. 收集所有边
	for (int i = 0; i < G.vertex_num; i++)
	{
		for (int j = i + 1; j < G.vertex_num; j++)
		{
			if (G.arc[i][j] < MAX)
			{
				edges[k].beigin = i;
				edges[k].end = j;
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
	}

	// 2. 对边按权重排序
	sortEdges(edges, G.edge_num);

	// 3. 初始化并查集
	int parent[MAXSIZE];
	for (int i = 0; i < G.vertex_num; i++)
	{
		parent[i] = 0;  // 初始每个顶点自成一个集合
	}

	// 4. 遍历排序后的边
	int n, m;
	for (int i = 0; i < G.edge_num; i++)
	{
		// 查找两个端点所属的集合（根节点）
		n = find(parent, edges[i].beigin);
		m = find(parent, edges[i].end);

		// 如果不在同一集合，加入MST
		if (n != m)
		{
			// 合并两个集合
			parent[n] = m;

			// 输出选中的边
			printf("边 (%c, %c) 权重: %d\n",
			       G.vertex[edges[i].beigin],
			       G.vertex[edges[i].end],
			       edges[i].weight);
		}
		// 如果在同一集合，跳过（会形成环）
	}
}

/**
 * 主函数: 测试Kruskal算法
 *
 * 预期输出最小生成树的所有边（按权重从小到大）
 */
int main(int argc, char const *argv[])
{
	Mat_Graph G;

	printf("=== 最小生成树 - Kruskal算法演示 ===\n\n");

	printf("正在创建带权无向图...\n");
	printf("顶点数: 9 (A-I)\n");
	printf("边数: 15\n\n");

	create_graph(&G);

	printf("Kruskal算法求最小生成树:\n");
	printf("================================\n");
	Kruskal(G);

	printf("\nKruskal算法特点:\n");
	printf("- 边优先：按权重排序选边\n");
	printf("- 使用并查集检测环\n");
	printf("- 时间复杂度: O(ElogE)\n");
	printf("- 适合稀疏图\n");

	printf("\nKruskal vs Prim:\n");
	printf("- Kruskal: 全局选边，适合稀疏图\n");
	printf("- Prim: 从顶点扩展，适合稠密图\n");

	printf("\n=== 算法完成 ===\n");

	system("pause");
	return 0;
}
