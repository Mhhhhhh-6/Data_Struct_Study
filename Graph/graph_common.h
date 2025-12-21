/**
 * ===========================================================================
 * 文件名: graph_common.h
 * 描述:   图模块通用头文件定义
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件定义了图模块所有文件共用的数据结构和函数声明
 *   包括邻接矩阵、邻接表、以及通用函数接口
 *
 * 使用方法:
 *   在图模块的C文件中包含此头文件：
 *   #include "graph_common.h"
 *
 * ===========================================================================
 */

#ifndef GRAPH_COMMON_H
#define GRAPH_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ==================== 常量定义 ====================

#define MAXSIZE 100        // 最大顶点数
#define INF 0x3f3f3f3f     // 无穷大（表示两顶点不相邻）

// ==================== 类型定义 ====================

/**
 * 顶点数据类型定义
 *
 * 说明:
 *   默认使用char类型，可根据需要修改
 */
typedef char VertexType;

/**
 * 边权重类型定义
 *
 * 说明:
 *   使用int类型表示边的权重
 */
typedef int EdgeType;

// ==================== 邻接矩阵结构 ====================

/**
 * 邻接矩阵图结构定义
 *
 * 成员说明:
 *   - vertex[MAXSIZE]: 顶点数组，存储顶点信息
 *   - arc[MAXSIZE][MAXSIZE]: 邻接矩阵，存储边的权重
 *   - vertex_num: 当前顶点数
 *   - edge_num: 当前边数
 *
 * 邻接矩阵特点:
 *   - 适合稠密图（边数较多）
 *   - 空间复杂度: O(V²)
 *   - 判断两顶点是否相邻: O(1)
 *   - 遍历所有边: O(V²)
 *
 * 矩阵表示:
 *   arc[i][j] = weight: 顶点i到顶点j有边，权重为weight
 *   arc[i][j] = 0:      无向图中，顶点i和j不相邻
 *   arc[i][j] = INF:    有向图/带权图中，顶点i到j无边
 *
 * 示意图:
 *   顶点: A B C D
 *   邻接矩阵:
 *       A  B  C  D
 *    A [0  1  1  0]
 *    B [1  0  1  1]
 *    C [1  1  0  1]
 *    D [0  1  1  0]
 */
typedef struct {
    VertexType vertex[MAXSIZE];      // 顶点数组
    EdgeType arc[MAXSIZE][MAXSIZE];  // 邻接矩阵
    int vertex_num;                   // 顶点数
    int edge_num;                     // 边数
} MGraph;

// ==================== 邻接表结构 ====================

/**
 * 邻接表的边节点（弧节点）
 *
 * 成员说明:
 *   - adjvex: 邻接顶点的索引
 *   - weight: 边的权重
 *   - next: 指向下一条边的指针
 *
 * 说明:
 *   每个边节点表示一条边
 *   多个边节点链接成链表
 */
typedef struct ArcNode {
    int adjvex;              // 邻接顶点索引
    int weight;              // 边权重
    struct ArcNode *next;    // 下一条边
} ArcNode;

/**
 * 邻接表的顶点节点
 *
 * 成员说明:
 *   - data: 顶点数据
 *   - firstarc: 指向第一条边的指针
 *
 * 说明:
 *   每个顶点节点包含顶点信息和一个边链表
 */
typedef struct VNode {
    VertexType data;         // 顶点数据
    ArcNode *firstarc;       // 第一条边
} VNode, AdjList[MAXSIZE];

/**
 * 邻接表图结构定义
 *
 * 成员说明:
 *   - vertices: 顶点数组（每个元素是VNode）
 *   - vexnum: 顶点数
 *   - arcnum: 边数
 *
 * 邻接表特点:
 *   - 适合稀疏图（边数较少）
 *   - 空间复杂度: O(V+E)
 *   - 判断两顶点是否相邻: O(degree) - degree是顶点的度
 *   - 遍历所有边: O(V+E)
 *
 * 示意图:
 *   vertices[0] (A) → [B] → [C] → NULL
 *   vertices[1] (B) → [A] → [C] → [D] → NULL
 *   vertices[2] (C) → [A] → [B] → [D] → NULL
 *   vertices[3] (D) → [B] → [C] → NULL
 */
typedef struct {
    AdjList vertices;        // 顶点数组
    int vexnum;             // 顶点数
    int arcnum;             // 边数
} ALGraph;

// ==================== 并查集结构（用于Kruskal算法）====================

/**
 * 并查集结构定义
 *
 * 成员说明:
 *   - parent[MAXSIZE]: 父节点数组，parent[i]表示节点i的父节点
 *
 * 并查集操作:
 *   - find(x): 查找x所属的集合（根节点）
 *   - union(x, y): 合并x和y所属的集合
 *
 * 应用:
 *   用于Kruskal最小生成树算法，检测环
 */
typedef struct {
    int parent[MAXSIZE];  // 父节点数组
} UnionFind;

// ==================== 边结构（用于最小生成树）====================

/**
 * 边结构定义（用于Kruskal算法）
 *
 * 成员说明:
 *   - start: 起始顶点索引
 *   - end: 终止顶点索引
 *   - weight: 边的权重
 *
 * 说明:
 *   将图的所有边存储在数组中，便于排序
 */
typedef struct {
    int start;    // 起始顶点
    int end;      // 终止顶点
    int weight;   // 边权重
} Edge;

// ==================== 邻接矩阵图操作函数 ====================

/**
 * 创建邻接矩阵图（无向图）
 */
MGraph* createMGraph(int vertex_num, int edge_num);

/**
 * 添加无向边
 */
void addUndirectedEdge(MGraph *g, int v1, int v2, int weight);

/**
 * 添加有向边
 */
void addDirectedEdge(MGraph *g, int v1, int v2, int weight);

/**
 * 打印邻接矩阵
 */
void printMGraph(MGraph *g);

/**
 * 获取顶点的索引
 */
int getVertexIndex(MGraph *g, VertexType v);

// ==================== 邻接表图操作函数 ====================

/**
 * 创建邻接表图
 */
ALGraph* createALGraph(int vexnum, int arcnum);

/**
 * 添加无向边（邻接表）
 */
void addUndirectedEdgeAL(ALGraph *g, int v1, int v2, int weight);

/**
 * 添加有向边（邻接表）
 */
void addDirectedEdgeAL(ALGraph *g, int v1, int v2, int weight);

/**
 * 打印邻接表
 */
void printALGraph(ALGraph *g);

// ==================== 图遍历函数 ====================

/**
 * 深度优先搜索（DFS）
 */
void DFS(MGraph *g, int start, bool visited[]);

/**
 * 深度优先遍历（遍历所有连通分量）
 */
void DFSTraverse(MGraph *g);

/**
 * 广度优先搜索（BFS）
 */
void BFS(MGraph *g, int start);

/**
 * 广度优先遍历（遍历所有连通分量）
 */
void BFSTraverse(MGraph *g);

// ==================== 最小生成树函数 ====================

/**
 * Prim算法求最小生成树
 *
 * 参数:
 *   @param g - 图指针
 *   @param start - 起始顶点索引
 *
 * 返回值: 最小生成树的总权重
 *
 * 算法思想:
 *   从起始顶点开始，逐步选择权重最小的边加入生成树
 *   每次选择一条连接已加入顶点和未加入顶点的最小权重边
 */
int Prim(MGraph *g, int start);

/**
 * Kruskal算法求最小生成树
 *
 * 参数:
 *   @param g - 图指针
 *
 * 返回值: 最小生成树的总权重
 *
 * 算法思想:
 *   将所有边按权重排序
 *   依次选择权重最小的边，如果不形成环则加入生成树
 *   使用并查集检测是否形成环
 */
int Kruskal(MGraph *g);

// ==================== 并查集操作函数 ====================

/**
 * 初始化并查集
 */
void initUnionFind(UnionFind *uf, int n);

/**
 * 查找根节点（路径压缩）
 */
int find(UnionFind *uf, int x);

/**
 * 合并两个集合
 */
void unionSet(UnionFind *uf, int x, int y);

// ==================== 最短路径函数 ====================

/**
 * Dijkstra算法求单源最短路径
 *
 * 参数:
 *   @param g - 图指针
 *   @param start - 起始顶点索引
 *   @param dist - 距离数组（输出参数）
 *   @param path - 路径数组（输出参数）
 *
 * 算法思想:
 *   贪心策略，每次选择距离起点最近的未访问顶点
 *   更新该顶点到其他顶点的最短距离
 */
void Dijkstra(MGraph *g, int start, int dist[], int path[]);

/**
 * Floyd算法求所有顶点对之间的最短路径
 *
 * 参数:
 *   @param g - 图指针
 *   @param dist - 距离矩阵（输出参数）
 *   @param path - 路径矩阵（输出参数）
 *
 * 算法思想:
 *   动态规划，考虑所有中间顶点
 *   dist[i][j]表示从i到j的最短距离
 */
void Floyd(MGraph *g, int dist[][MAXSIZE], int path[][MAXSIZE]);

// ==================== 拓扑排序函数 ====================

/**
 * 拓扑排序
 *
 * 参数:
 *   @param g - 有向无环图指针
 *   @param topo - 拓扑序列数组（输出参数）
 *
 * 返回值:
 *   1 - 排序成功（无环）
 *   0 - 排序失败（有环）
 *
 * 算法思想:
 *   每次选择入度为0的顶点输出
 *   删除该顶点及其出边，更新其他顶点的入度
 */
int TopologicalSort(MGraph *g, int topo[]);

// ==================== 辅助函数 ====================

/**
 * 比较函数（用于边的排序）
 */
int compareEdges(const void *a, const void *b);

#endif // GRAPH_COMMON_H
