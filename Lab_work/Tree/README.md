# 树算法模块

本模块包含二叉树及其相关算法的完整实现，从基础遍历到高级应用。

---

## 文件列表

| 文件名 | 功能 | 难度 | 时间复杂度 | 状态 |
|-------|------|------|-----------|------|
| `tree_common.h` | 树结构通用定义 | - | - | 待创建 |
| `binary_tree_traversal_recursive.c` | 二叉树递归遍历 | ⭐⭐ | O(n) | 待创建 |
| `binary_tree_traversal_stack.c` | 二叉树栈遍历（非递归） | ⭐⭐⭐ | O(n) | 待创建 |
| `threaded_binary_tree.c` | 线索二叉树 | ⭐⭐⭐⭐ | O(n) | 待创建 |
| `binary_tree_depth.c` | 计算二叉树深度 | ⭐⭐ | O(n) | 待创建 |
| `binary_tree_wpl.c` | 加权路径长度（WPL） | ⭐⭐⭐ | O(n) | 待创建 |

---

## 学习顺序建议

### 第一阶段：基础遍历
1. **binary_tree_traversal_recursive.c** - 递归遍历
   - 先序遍历（根-左-右）
   - 中序遍历（左-根-右）
   - 后序遍历（左-右-根）
   - **重点**：理解递归思想

### 第二阶段：进阶技巧
2. **binary_tree_traversal_stack.c** - 非递归遍历
   - 使用栈模拟递归过程
   - **重点**：理解栈的应用

3. **binary_tree_depth.c** - 深度计算
   - 使用层序遍历（BFS）
   - **重点**：理解队列在树中的应用

### 第三阶段：高级应用
4. **threaded_binary_tree.c** - 线索二叉树
   - 线索化过程
   - 线索遍历
   - **重点**：优化空间利用

5. **binary_tree_wpl.c** - WPL计算
   - 哈夫曼树基础
   - **重点**：理解最优二叉树

---

## 编译与运行

### 单文件编译
```bash
# Windows
cd Lab_work\Tree
gcc binary_tree_traversal_recursive.c -o traversal_recursive.exe
traversal_recursive.exe

# Linux/Mac
gcc binary_tree_traversal_recursive.c -o traversal_recursive
./traversal_recursive
```

### 批量编译（所有树算法）
```bash
cd Lab_work\Tree
gcc binary_tree*.c -o tree_all.exe
```

---

## 测试数据

### 示例二叉树1（简单）
**先序序列输入**：`ABC##DE###`

**树结构**：
```
    A
   / \
  B   D
   \   \
    C   E
```

**遍历结果**：
- 先序：A B C D E
- 中序：B C A D E
- 后序：C B E D A

### 示例二叉树2（复杂）
**先序序列输入**：`ABDH#K###E##CFI###G#J##`

**树结构**：
```
           A
          / \
         B   C
        / \   \
       D   E   F
      /       / \
     H       I   G
      \          \
       K          J
```

**遍历结果**：
- 先序：A B D H K E C F I G J
- 中序：H K D B E A I F G J C
- 后序：K H D E B I J G F C A

---

## 核心概念

### 1. 递归 vs 非递归
| 特性 | 递归 | 非递归（栈） |
|------|------|------------|
| 代码复杂度 | 简单直观 | 相对复杂 |
| 空间复杂度 | O(h)（系统栈） | O(h)（显式栈） |
| 执行效率 | 较低（函数调用开销） | 较高 |
| 栈溢出风险 | 深度过大时有风险 | 可控 |

### 2. 三种遍历的应用场景
- **先序遍历**：复制树结构、先根处理场景
- **中序遍历**：二叉搜索树（BST）的有序输出
- **后序遍历**：计算目录大小、释放内存

### 3. 线索二叉树的优势
- 无需递归或栈，O(1)空间找到后继节点
- 适合频繁遍历的场景
- 利用空指针域，节省空间

---

## 常见问题

### Q1: 为什么用'#'表示空节点？
**A**: 这是一种约定俗成的表示方法，便于通过先序序列唯一确定一棵二叉树。

### Q2: 如何根据遍历序列重建二叉树？
**A**:
- 先序 + 中序 → 可唯一确定
- 中序 + 后序 → 可唯一确定
- 先序 + 后序 → 不能唯一确定（需要满二叉树）

### Q3: 树的高度和深度有什么区别？
**A**:
- **高度（Height）**：从叶子节点到该节点的最长路径
- **深度（Depth）**：从根节点到该节点的路径长度
- 树的高度 = 根节点的高度

---

## 参考资料

- 《数据结构》（C语言版）- 严蔚敏 第6章
- [VisuAlgo - 二叉树可视化](https://visualgo.net/en/bst)
- [二叉树动画演示](https://www.cs.usfca.edu/~galles/visualization/BST.html)

---

**最后更新**：2025-12-21
