/**
 * ===========================================================================
 * 文件名: test3.c
 * 描述:   单链表高级算法集合
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了多个链表的高级算法，包括：
 *   1. 链表的基本操作
 *   2. 查找倒数第k个节点、查找链表交点
 *   3. **删除绝对值相同的节点（桶算法）**
 *   4. **反转链表**
 *   5. **删除中间节点**
 *   6. **链表重新排序**
 *   7. **判断链表是否有环**
 *   8. **找到链表环的入口**
 *
 * 难度: ⭐⭐⭐⭐（高级算法集合）
 *
 * 使用方法:
 *   编译: gcc test3.c -o test3
 *   运行: ./test3
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node {
    ElemType data;
    struct node *next;
} Node;

// ============ 基础操作（简化注释） ============
Node* initList() {
    Node *head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

Node* initListWithElem(ElemType e) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;
    return node;
}

int insertHead(Node* L, ElemType e) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = e;
    p->next = L->next;
    L->next = p;
    return 1;
}

void listNode(Node* L) {
    Node *p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

Node* get_tail(Node *L) {
    Node *p = L;
    while (p->next != NULL) {
        p = p->next;
    }
    return p;
}

Node* insertTail(Node *tail, ElemType e) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = e;
    tail->next = p;
    p->next = NULL;
    return p;
}

Node* insertTailWithNode(Node *tail, Node *node) {
    tail->next = node;
    node->next = NULL;
    return node;
}

int insertNode(Node *L, int pos, ElemType e) {
    Node *p = L;
    int i = 0;
    while (i < pos - 1) {
        p = p->next;
        i++;
        if (p == NULL) return 0;
    }
    Node *q = (Node*)malloc(sizeof(Node));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return 1;
}

int deleteNode(Node *L, int pos) {
    Node *p = L;
    int i = 0;
    while (i < pos - 1) {
        p = p->next;
        i++;
        if (p == NULL) return 0;
    }
    if (p->next == NULL) {
        printf("要删除的位置错误\n");
        return 0;
    }
    Node *q = p->next;
    p->next = q->next;
    free(q);
    return 1;
}

int listLength(Node *L) {
    Node *p = L;
    int len = 0;
    while (p != NULL) {
        p = p->next;
        len++;
    }
    return len;
}

void freeList(Node *L) {
    Node *p = L->next;
    Node *q;
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}

int findNodeFS(Node *L, int k) {
    Node *fast = L->next;
    Node *slow = L->next;
    for (int i = 0; i < k; i++) {
        fast = fast->next;
    }
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    printf("倒数第%d个节点值为：%d\n", k, slow->data);
    return 1;
}

Node* findIntersectionNode(Node *headA, Node *headB) {
    if (headA == NULL || headB == NULL) return NULL;
    Node *p = headA;
    int lenA = 0, lenB = 0;
    while (p != NULL) {
        p = p->next;
        lenA++;
    }
    p = headB;
    while (p != NULL) {
        p = p->next;
        lenB++;
    }
    Node *m, *n;
    int step;
    if (lenA > lenB) {
        step = lenA - lenB;
        m = headA;
        n = headB;
    } else {
        step = lenB - lenA;
        m = headB;
        n = headA;
    }
    for (int i = 0; i < step; i++) {
        m = m->next;
    }
    while (m != n) {
        m = m->next;
        n = n->next;
    }
    return m;
}

// ============ 高级算法（详细注释） ============

/**
 * 函数: removeNode
 * 功能: 删除链表中绝对值相同的节点（桶算法/哈希表）
 *
 * 参数:
 *   @param L - 链表头节点
 *   @param n - 节点数据的最大绝对值范围
 *
 * 算法思路:
 *   1. 创建一个大小为n+1的桶数组，初始化为0
 *   2. 遍历链表，对每个节点：
 *      - 计算其绝对值作为桶索引
 *      - 如果桶值为0，标记为1并保留节点
 *      - 如果桶值为1，说明已存在绝对值相同的节点，删除当前节点
 *   3. 释放桶数组
 *
 * 时间复杂度: O(n) - 遍历一次链表
 * 空间复杂度: O(n) - 需要桶数组
 *
 * 示例:
 *   输入链表: 1 -> -2 -> 3 -> -1 -> 2
 *   输出链表: 1 -> -2 -> 3
 *   说明: |-1| = 1已存在，|2| = 2已存在，删除
 */
void removeNode(Node *L, int n) {
    Node *p = L;
    int index;
    // 创建桶数组，大小为n+1（索引0到n）
    int *q = (int*)malloc(sizeof(int) * (n + 1));

    // 初始化桶数组为0
    for (int i = 0; i < n + 1; i++) {
        *(q + i) = 0;
    }

    // 遍历链表
    while (p->next != NULL) {
        // 获取节点数据的绝对值作为桶索引
        index = abs(p->next->data);

        // 检查该绝对值是否已出现过
        if (*(q + index) == 0) {
            // 未出现过，标记为已出现，保留节点
            *(q + index) = 1;
            p = p->next;
        } else {
            // 已出现过，删除当前节点
            Node *temp = p->next;
            p->next = temp->next;
            free(temp);
        }
    }

    // 释放桶数组
    free(q);
}

/**
 * 函数: reverseList
 * 功能: 反转链表
 *
 * 参数:
 *   @param head - 原链表头节点
 *
 * 返回值: 返回反转后的新链表头节点
 *
 * 算法思路（三指针法）:
 *   使用first、second、third三个指针
 *   依次改变节点的指向，使其指向前一个节点
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 *
 * 示例:
 *   原链表: NULL  1 -> 2 -> 3 -> 4 -> 5 -> NULL
 *           first sec  thi
 *
 *   步骤1:  NULL <- 1   2 -> 3 -> 4 -> 5
 *          first   sec  thi
 *
 *   步骤2:  NULL <- 1 <- 2   3 -> 4 -> 5
 *                 first sec  thi
 *
 *   最终:   NULL <- 1 <- 2 <- 3 <- 4 <- 5
 *                                    first
 */
Node* reverseList(Node* head) {
    Node *first = NULL;           // 指向已反转部分的末尾
    Node *second = head->next;    // 指向当前要反转的节点
    Node *third;                  // 指向下一个待处理节点

    // 遍历链表，逐个反转节点指向
    while (second != NULL) {
        third = second->next;     // 保存下一个节点
        second->next = first;     // 反转指向
        first = second;           // first前移
        second = third;           // second前移
    }

    // 创建新的头节点
    Node *hd = initList();
    hd->next = first;
    return hd;
}

/**
 * 函数: delMiddleNode
 * 功能: 删除链表的中间节点（快慢指针法）
 *
 * 算法思路:
 *   - fast指针每次走2步，slow指针每次走1步
 *   - 当fast到达末尾时，slow指向中间节点的前驱
 *   - 删除slow的下一个节点即可
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 *
 * 示例:
 *   输入: 1 -> 2 -> 3 -> 4 -> 5
 *   输出: 1 -> 2 -> 4 -> 5 （删除3）
 */
int delMiddleNode(Node *head) {
    Node *fast = head->next;
    Node *slow = head;

    // fast走两步，slow走一步
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // slow指向中间节点的前驱，删除中间节点
    Node *q = slow->next;
    slow->next = q->next;
    free(q);
    return 1;
}

/**
 * 函数: reOrderList
 * 功能: 链表重新排序（L0→L1→...→Ln 变为 L0→Ln→L1→Ln-1→...）
 *
 * 算法思路:
 *   1. 找到链表的中间节点，将链表分为两段
 *   2. 反转第二段链表
 *   3. 将两段链表交替合并
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 *
 * 示例:
 *   输入: 1 -> 2 -> 3 -> 4 -> 5 -> 6
 *
 *   步骤1: 分为两段
 *     第一段: 1 -> 2 -> 3
 *     第二段: 4 -> 5 -> 6
 *
 *   步骤2: 反转第二段
 *     第一段: 1 -> 2 -> 3
 *     第二段: 6 -> 5 -> 4
 *
 *   步骤3: 交替合并
 *     1 -> 6 -> 2 -> 5 -> 3 -> 4
 */
void reOrderList(Node *head) {
    // 步骤1: 找到中间节点
    Node *fast = head->next;
    Node *slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // 步骤2: 反转第二段链表
    Node *first = NULL;
    Node *second = slow->next;
    slow->next = NULL;  // 断开第一段和第二段
    Node *third = NULL;

    while (second != NULL) {
        third = second->next;
        second->next = first;
        first = second;
        second = third;
    }

    // 步骤3: 交替合并两段链表
    Node *p1 = head->next;  // 第一段的当前节点
    Node *q1 = first;       // 第二段的当前节点（已反转）
    Node *p2, *q2;          // 临时保存下一个节点

    while (p1 != NULL && q1 != NULL) {
        // 保存下一个节点
        p2 = p1->next;
        q2 = q1->next;

        // 交替连接
        p1->next = q1;
        q1->next = p2;

        // 移动到下一对节点
        p1 = p2;
        q1 = q2;
    }
}

/**
 * 函数: isCycle
 * 功能: 判断链表是否有环（快慢指针法）
 *
 * 算法思路:
 *   - fast指针每次走2步，slow指针每次走1步
 *   - 如果有环，fast和slow必然会相遇（追及问题）
 *   - 如果无环，fast会先到达NULL
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 *
 * 示例（有环）:
 *   1 -> 2 -> 3 -> 4 -> 5
 *             ↑         ↓
 *             8 ← 7 ← 6
 *   fast和slow会在环内相遇
 */
int isCycle(Node *head) {
    Node *fast = head;
    Node *slow = head;

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;

        // 【修复bug】原代码是 if(fast=slow)，应该是 ==
        if (fast == slow) {
            return 1;  // 有环
        }
    }
    return 0;  // 无环
}

/**
 * 函数: findBegin
 * 功能: 找到链表环的入口节点
 *
 * 算法思路:
 *   1. 使用快慢指针检测是否有环，并在相遇点停止
 *   2. 从相遇点出发，计算环的节点数count
 *   3. 让fast指针先走count步
 *   4. fast和slow同时前进，相遇点即为环的入口
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 *
 * 算法原理:
 *   设环外长度为a，环长度为b
 *   让一个指针先走b步，然后两指针同步前进
 *   它们会在环的入口相遇
 */
Node* findBegin(Node *head) {
    Node *fast = head;
    Node *slow = head;

    // 步骤1: 检测是否有环，找到相遇点
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow) {
            // 步骤2: 计算环的节点数
            Node *p = fast;
            int count = 1;
            while (p->next != slow) {
                count++;
                p = p->next;
            }

            // 步骤3: 重置指针，让fast先走count步
            fast = head;
            slow = head;
            for (int i = 0; i < count; i++) {
                fast = fast->next;
            }

            // 步骤4: 同步前进，相遇点即为环入口
            while (fast != slow) {
                fast = fast->next;
                slow = slow->next;
            }
            return slow;
        }
    }
    return NULL;  // 无环
}

/**
 * 主函数: 测试环检测和环入口查找
 *
 * 构建带环链表:
 *   1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8
 *             ↑                       ↓
 *             └───────────────────────┘
 *   环入口: 节点3
 */
int main(int argc, char const *argv[]) {
    Node *list = initList();
    Node *tail = get_tail(list);

    // 构建链表并保存节点3的指针
    tail = insertTail(tail, 1);
    tail = insertTail(tail, 2);
    tail = insertTail(tail, 3);
    Node *three = tail;  // 环的入口
    tail = insertTail(tail, 4);
    tail = insertTail(tail, 5);
    tail = insertTail(tail, 6);
    tail = insertTail(tail, 7);
    tail = insertTail(tail, 8);

    // 创建环：让尾节点指向节点3
    tail->next = three;

    // 查找环的入口
    Node *p = findBegin(list);
    printf("环的入口节点数据: %d\n", p->data);  // 输出: 3

    system("pause");
    return 0;
}
