# Data_Struct_Study - C语言数据结构学习项目

## 项目简介

本项目是一个完整的C语言数据结构学习仓库，涵盖数据结构与算法的核心内容，包括线性表、栈、队列、树、图等基本数据结构及其相关算法实现。

**适用人群**：数据结构初学者、计算机专业学生

**特色**：
- 完整的中文注释，包含算法思路和复杂度分析
- 交互式测试程序，方便理解和调试
- 结构化的代码组织，便于学习和查找
- 从基础到进阶的完整学习路径

---

## 目录结构

```
Data_struct_study/
├── Chained_list/           # 链表基础练习
│   ├── test.c             # 链表基础操作
│   ├── test2.c            # 链表字符型
│   ├── test3.c            # 链表进阶
│   └── test4.c            # 链表高级操作
├── Ordered_list/           # 有序表实现
│   ├── test.c
│   └── test2.c
├── Stack/                  # 栈基础练习
│   ├── test1.c            # 顺序栈基础
│   ├── test2.c            # 栈应用
│   └── test3.c            # 栈进阶
├── Queue/                  # 队列基础练习
│   ├── test1.c            # 队列基础
│   ├── test2.c            # 队列操作
│   ├── test3.c            # 队列应用
│   └── test4.c            # 队列进阶
├── Lab_work/               # 核心实验代码（主要学习内容）
│   ├── Tree/              # 树算法集合
│   │   └── README.md      # 树模块说明
│   ├── Graph/             # 图算法集合
│   │   └── README.md      # 图模块说明
│   ├── Sequential_List.c  # 顺序表实现
│   ├── Linked_List.c      # 链表高级实现
│   ├── My_Stack.c         # 栈实现（带菜单）
│   ├── Stack.c            # 栈实现（另一版本）
│   ├── Linked_queue.c     # 链式队列
│   ├── bt1.c              # 二叉树基础实现
│   ├── BT.h               # 二叉树头文件
│   ├── Binary_Expression_Tree.c  # 二叉表达式树
│   ├── graph_net.c        # 图的邻接矩阵实现
│   ├── graph_net_other.c  # 图的其他实现
│   ├── sort.c             # 排序算法集合
│   └── coin/              # 编译输出目录
└── README.md              # 项目说明文档（本文件）
```

---

## 已实现数据结构与算法

### 1. 线性结构

#### 顺序表
- [x] **顺序表基础操作** (`Sequential_List.c`)
  - 初始化、插入、删除、查找
  - 支持动态扩容
  - 时间复杂度：插入/删除 O(n)，查找 O(1)

#### 链表
- [x] **单链表完整实现** (`Linked_List.c`, `Chained_list/test*.c`)
  - 头插法/尾插法
  - 指定位置插入/删除
  - 快慢指针查找倒数第k个节点
  - 查找两个链表的交点
  - 时间复杂度：插入/删除 O(1)，查找 O(n)

#### 栈
- [x] **顺序栈** (`My_Stack.c`, `Stack.c`, `Stack/test*.c`)
  - 初始化、进栈、出栈
  - 获取栈顶元素、判断栈空/栈满
  - 交互式菜单界面
  - 时间复杂度：O(1)

#### 队列
- [x] **顺序队列** (`Queue/test*.c`)
  - 循环队列实现
  - 入队、出队、获取队头
  - 队列调整功能
- [x] **链式队列** (`Linked_queue.c`)
  - 基于链表的队列
  - 消除顺序队列的虚假溢出
  - 时间复杂度：O(1)

### 2. 树结构

#### 二叉树基础
- [x] **二叉树基本操作** (`bt1.c`, `Binary_Expression_Tree.c`)
  - 多种创建方式（编号法、括号表示法、先序输入）
  - 先序、中序、后序遍历
  - 树的销毁和显示
  - 时间复杂度：O(n)

#### 树模块（Lab_work/Tree/）
- [ ] 二叉树遍历 - 递归实现
- [ ] 二叉树遍历 - 栈实现（非递归）
- [ ] 线索二叉树
- [ ] 计算二叉树深度
- [ ] 加权路径长度（WPL）计算
- [ ] AVL平衡二叉树（可选）
- [ ] 哈夫曼树与编码（可选）

### 3. 图结构

#### 图的存储
- [x] **邻接矩阵表示** (`graph_net.c`, `graph_net_other.c`)
  - 有向图/无向图
  - 加权图/非加权图
  - 图的打印和顶点定位

#### 图模块（Lab_work/Graph/）
- [ ] DFS深度优先遍历
- [ ] BFS广度优先遍历
- [ ] 最小生成树 - Prim算法
- [ ] 最小生成树 - Kruskal算法
- [ ] 最短路径 - Dijkstra算法（可选）
- [ ] 拓扑排序（可选）

### 4. 排序算法
- [x] **插入排序** (`sort.c`)
  - 直接插入排序
  - 性能统计（比较次数）
  - 时间复杂度：O(n²)

---

## 编译与运行

### 环境要求
- **编译器**：MinGW-GCC（Windows）或 GCC（Linux/Mac）
- **开发工具**：VS Code（推荐）或任何文本编辑器
- **C标准**：C89/C99

### 编译单个文件

#### Windows (MinGW)
```bash
# 进入代码目录
cd D:\Data_struct_study\Lab_work

# 编译单个文件
gcc Sequential_List.c -o sequential_list.exe

# 运行程序
sequential_list.exe
```

#### Linux/Mac
```bash
# 编译
gcc Lab_work/Sequential_List.c -o sequential_list

# 运行
./sequential_list
```

### 批量编译

```bash
# 编译Lab_work目录下的所有C文件
cd Lab_work
gcc *.c -o all_structures.exe

# 编译树模块（待实现）
gcc Tree/*.c -o tree_all.exe

# 编译图模块（待实现）
gcc Graph/*.c -o graph_all.exe
```

### 处理中文乱码

如果运行时出现中文乱码，使用以下编译选项：

```bash
# Windows
gcc source.c -fexec-charset=GBK -o output.exe

# 或在源文件顶部添加
#pragma execution_character_set("utf-8")
```

---

## 学习路径建议

### 阶段一：线性结构（1-2周）

**学习顺序**：
1. 顺序表 (`Sequential_List.c`) → 理解顺序存储
2. 链表 (`Linked_List.c`) → 理解链式存储
3. 栈 (`My_Stack.c`) → 理解后进先出（LIFO）
4. 队列 (`Linked_queue.c`) → 理解先进先出（FIFO）

**学习重点**：
- 理解顺序存储和链式存储的区别
- 掌握指针的使用和内存管理
- 熟悉基本操作：初始化、插入、删除、查找
- 分析时间复杂度和空间复杂度

**练习建议**：
- 实现链表的反转
- 用栈实现括号匹配
- 用队列模拟银行排队系统

### 阶段二：树结构（2-3周）

**学习顺序**：
1. 二叉树基础 (`bt1.c`) → 理解树的基本概念
2. 二叉树遍历 - 递归 → 掌握递归思想
3. 二叉树遍历 - 栈 → 理解非递归实现
4. 线索二叉树 → 优化遍历效率
5. AVL树 → 理解平衡的重要性

**学习重点**：
- 理解递归的思想和实现方式
- 掌握树的三种遍历方式（前序、中序、后序）
- 了解树的应用场景（表达式求值、文件系统等）
- 理解平衡树的旋转操作

**练习建议**：
- 根据遍历序列构建二叉树
- 实现二叉搜索树（BST）
- 利用哈夫曼树进行文本压缩

### 阶段三：图结构（2-3周）

**学习顺序**：
1. 图的存储 (`graph_net.c`) → 理解邻接矩阵和邻接表
2. DFS遍历 → 掌握深度优先思想
3. BFS遍历 → 掌握广度优先思想
4. 最小生成树 → 理解贪心算法
5. 最短路径 → 理解动态规划思想

**学习重点**：
- 理解图的两种存储方式的优缺点
- 掌握图的遍历算法（DFS、BFS）
- 了解图的经典算法及应用场景
- 理解Prim和Kruskal算法的差异

**练习建议**：
- 判断图中是否有环
- 实现Dijkstra最短路径算法
- 解决拓扑排序问题

### 阶段四：综合应用（1-2周）

**学习重点**：
- 分析各种排序算法的时间复杂度
- 理解分治、递归、动态规划等算法思想
- 综合运用多种数据结构解决实际问题

**练习建议**：
- 实现快速排序、归并排序
- 解决LeetCode相关题目
- 完成小型项目（如通讯录管理系统）

---

## 代码风格说明

### 注释规范
- 每个文件包含完整的文件头注释（功能说明、使用方法）
- 函数注释包含：功能、参数、返回值、算法思路、复杂度分析
- 关键代码块添加行内注释
- 所有注释使用简洁易懂的中文

### 复杂度标注
所有算法函数都标注了时间和空间复杂度：

```c
/**
 * 函数: preOrder
 * 功能: 先序遍历二叉树（递归实现）
 *
 * 时间复杂度: O(n) - 每个节点访问一次
 * 空间复杂度: O(h) - 递归栈深度为树高h，最坏O(n)，平均O(log n)
 */
void preOrder(BiTree T) {
    // 算法实现...
}
```

### 命名规范
- **变量名**：驼峰命名或下划线分隔（如：`topIndex`、`top_index`）
- **函数名**：驼峰命名（如：`createTree`、`insertNode`）
- **常量名**：全大写+下划线（如：`MAXSIZE`、`MAX_NUM`）
- **类型定义**：首字母大写（如：`BiTree`、`MGraph`）

---

## 常见问题（FAQ）

### Q1: 如何输入测试数据？
**A**: 大部分程序提供交互式菜单，按提示输入即可。

对于树结构，通常使用先序遍历序列，用 `#` 表示空节点。

**示例输入**：`ABDH#K###E##CFI###G#J##`

这表示创建如下二叉树：
```
           A
          / \
         B   C
        / \   \
       D   E   ...
```

### Q2: 编译时出现中文乱码怎么办？
**A**: 这通常是字符编码问题。

**方法1**：在源文件顶部添加
```c
#pragma execution_character_set("utf-8")
```

**方法2**：使用GBK编码编译
```bash
gcc -fexec-charset=GBK source.c -o output.exe
```

**方法3**：确保VS Code使用UTF-8编码保存文件
- 文件 → 首选项 → 设置 → 搜索 "encoding"
- 设置为 `UTF-8`

### Q3: 程序运行后立即退出怎么办？
**A**: 这是Windows控制台自动关闭导致的。

在 `main` 函数 `return 0;` 之前添加：

```c
#ifdef _WIN32
    system("pause");  // Windows系统
#else
    getchar();        // Linux/Mac系统
#endif
```

### Q4: 如何调试程序？
**A**:
1. **使用printf调试法**：在关键位置打印变量值
2. **使用GDB调试器**：
   ```bash
   gcc -g source.c -o output
   gdb output
   ```
3. **使用VS Code调试功能**：配置 `launch.json`

### Q5: 内存泄漏问题如何检查？
**A**:
- **Linux/Mac**：使用Valgrind工具
  ```bash
  valgrind --leak-check=full ./your_program
  ```
- **Windows**：使用Visual Studio内存检测工具
- **通用方法**：确保每个 `malloc` 都有对应的 `free`

---

## 参考资料

### 经典教材
- 《数据结构》（C语言版）- 严蔚敏、吴伟民
- 《算法导论》（第3版）- Thomas H. Cormen等
- 《数据结构与算法分析：C语言描述》- Mark Allen Weiss

### 在线资源
- [VisuAlgo算法可视化](https://visualgo.net) - 动画演示各种算法
- [数据结构动画演示](https://www.cs.usfca.edu/~galles/visualization/) - UCSF提供
- [LeetCode](https://leetcode.cn) - 算法练习平台
- [牛客网](https://www.nowcoder.com) - 编程题库

### 视频课程
- 中国大学MOOC - 数据结构（浙江大学）
- Bilibili - 数据结构与算法系列教程

---

## 贡献指南

欢迎提交Issue和Pull Request！

### 提交规范
- **代码风格**：与现有代码保持一致
- **注释要求**：添加完整的中文注释
- **复杂度分析**：包含算法的时间和空间复杂度
- **测试**：确保代码能正常编译运行

### 提交流程
1. Fork本仓库
2. 创建特性分支：`git checkout -b feature/new-algorithm`
3. 提交更改：`git commit -m "feat: 添加快速排序算法"`
4. 推送分支：`git push origin feature/new-algorithm`
5. 提交Pull Request

---

## 许可证

本项目采用 **MIT 许可证**。

您可以自由地：
- 使用本项目的代码
- 修改本项目的代码
- 分发本项目的代码
- 用于商业用途

唯一要求是在代码中保留版权声明和许可证声明。

---

## 联系方式

- **GitHub**：[@Mhhhhhh-6](https://github.com/Mhhhhhh-6)
- **项目地址**：[https://github.com/Mhhhhhh-6/Data_Struct_Study](https://github.com/Mhhhhhh-6/Data_Struct_Study)
- **问题反馈**：[提交Issue](https://github.com/Mhhhhhh-6/Data_Struct_Study/issues)

---

## 更新日志

### v1.0.0 (2025-12-21)
- 初始化项目
- 添加完整的项目文档
- 整理现有代码并添加详细注释
- 创建树和图模块目录结构

---

**最后更新**：2025-12-21

**项目状态**：🚧 持续更新中...

**Star** ⭐ 如果这个项目对你有帮助！
