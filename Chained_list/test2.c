/**
 * ===========================================================================
 * 文件名: test2.c
 * 描述:   单链表（字符型）- 查找链表交点
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了字符型单链表，重点展示：
 *   1. 链表的基本操作（初始化、插入、删除、遍历）
 *   2. 快慢指针查找倒数第k个节点
 *   3. **快慢指针查找两个链表的交点**（核心算法）
 *
 * 应用场景:
 *   - 判断两个链表是否相交
 *   - 找到相交的起始节点
 *   - 字符串处理中的公共后缀查找
 *
 * 使用方法:
 *   编译: gcc test2.c -o test2
 *   运行: ./test2
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 链表数据元素类型定义（字符型）
typedef char ElemType;

/**
 * 单链表节点结构定义
 */
typedef struct node {
    ElemType data;         // 数据域（字符型）
    struct node *next;     // 指针域
} Node;

/**
 * 函数: initList
 * 功能: 初始化链表，创建带头节点的空链表
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */
Node* initList() {
    Node *head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

/**
 * 函数: initListWithElem
 * 功能: 创建一个带指定数据的单个节点
 *
 * 参数:
 *   @param e - 节点数据
 *
 * 返回值: 返回新创建的节点指针
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 应用场景:
 *   - 创建共享节点，用于构建相交链表
 *   - 需要预先创建节点时使用
 */
Node* initListWithElem(ElemType e) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = e;
    node->next = NULL;
    return node;
}

/**
 * 函数: insertHead
 * 功能: 头插法插入节点
 * 时间复杂度: O(1)
 */
int insertHead(Node* L, ElemType e) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = e;
    p->next = L->next;
    L->next = p;
    return 1;
}

/**
 * 函数: listNode
 * 功能: 遍历并打印链表中的字符
 * 时间复杂度: O(n)
 */
void listNode(Node* L) {
    Node *p = L->next;
    while (p != NULL) {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}

/**
 * 函数: get_tail
 * 功能: 获取链表的尾节点
 * 时间复杂度: O(n)
 */
Node* get_tail(Node *L) {
    Node *p = L;
    while (p->next != NULL) {
        p = p->next;
    }
    return p;
}

/**
 * 函数: insertTail
 * 功能: 尾插法插入新节点（创建新节点）
 * 时间复杂度: O(1)
 */
Node* insertTail(Node *tail, ElemType e) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = e;
    tail->next = p;
    p->next = NULL;
    return p;
}

/**
 * 函数: insertTailWithNode
 * 功能: 尾插法插入已存在的节点
 *
 * 参数:
 *   @param tail - 当前尾节点指针
 *   @param node - 要插入的节点指针
 *
 * 返回值: 返回新的尾节点指针
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 注意事项:
 *   - 与insertTail不同，此函数不创建新节点，而是插入已有节点
 *   - 可用于创建相交链表（多个链表共享同一节点）
 *
 * 示例:
 *   Node *sharedNode = initListWithElem('X');
 *   tailA = insertTailWithNode(tailA, sharedNode);
 *   tailB = insertTailWithNode(tailB, sharedNode);
 *   // 现在listA和listB共享节点X
 */
Node* insertTailWithNode(Node *tail, Node *node) {
    tail->next = node;
    node->next = NULL;
    return node;
}

/**
 * 函数: insertNode
 * 功能: 在指定位置插入节点
 * 时间复杂度: O(n)
 */
int insertNode(Node *L, int pos, ElemType e) {
    Node *p = L;
    int i = 0;
    while (i < pos - 1) {
        p = p->next;
        i++;
        if (p == NULL) {
            return 0;
        }
    }

    Node *q = (Node*)malloc(sizeof(Node));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return 1;
}

/**
 * 函数: deleteNode
 * 功能: 删除指定位置的节点
 * 时间复杂度: O(n)
 */
int deleteNode(Node *L, int pos) {
    Node *p = L;
    int i = 0;
    while (i < pos - 1) {
        p = p->next;
        i++;
        if (p == NULL) {
            return 0;
        }
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

/**
 * 函数: listLength
 * 功能: 计算链表长度（包括头节点）
 * 时间复杂度: O(n)
 */
int listLength(Node *L) {
    Node *p = L;
    int len = 0;
    while (p != NULL) {
        p = p->next;
        len++;
    }
    return len;
}

/**
 * 函数: freeList
 * 功能: 释放链表所有节点
 * 时间复杂度: O(n)
 */
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

/**
 * 函数: findNodeFS
 * 功能: 查找倒数第k个节点（快慢指针法）
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
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

    printf("倒数第%d个节点值为: %d\n", k, slow->data);
    return 1;
}

/**
 * 函数: findIntersectionNode
 * 功能: 查找两个链表的交点（快慢指针法）
 *
 * 参数:
 *   @param headA - 链表A的头节点
 *   @param headB - 链表B的头节点
 *
 * 返回值: 返回交点节点指针，如果不相交返回NULL
 *
 * 算法思路:
 *   1. 分别计算两个链表的长度lenA和lenB
 *   2. 让较长链表的指针先走|lenA-lenB|步
 *   3. 两个指针同时前进，直到指向同一节点
 *   4. 该节点即为交点
 *
 * 时间复杂度: O(m+n) - m和n分别为两个链表的长度
 * 空间复杂度: O(1)
 *
 * 算法原理:
 *   - 两个链表相交后，后续部分完全相同
 *   - 通过让较长链表先走差值步数，使两指针距离交点距离相等
 *   - 这样同步前进时，必然会在交点处相遇
 *
 * 示例:
 *   listA: 1 -> 2 -> 3 -> 4 -> 5 -> 6
 *   listB:      7 -> 8 -> 5 -> 6
 *                         ↑ 交点
 *   lenA=6, lenB=4, 差值=2
 *   让A先走2步: A指向3, B指向7
 *   同步前进:
 *     A=4, B=8
 *     A=5, B=5 ✓ 找到交点
 *
 * 注意事项:
 *   - 如果两个链表不相交，最终返回NULL
 *   - 比较的是节点地址，不是节点数据
 */
Node* findIntersectionNode(Node *headA, Node *headB) {
    // 边界检查
    if (headA == NULL || headB == NULL) {
        return NULL;
    }

    Node *fast;
    Node *slow;
    int step;

    // 计算两个链表的长度
    int lenA = listLength(headA);
    int lenB = listLength(headB);

    // 确定哪个链表更长，计算长度差
    if (lenA > lenB) {
        step = lenA - lenB;
        fast = headA;        // 快指针指向较长链表
        slow = headB;        // 慢指针指向较短链表
    } else {
        step = lenB - lenA;
        fast = headB;        // 快指针指向较长链表
        slow = headA;        // 慢指针指向较短链表
    }

    // 让快指针先走step步，使两指针距离终点距离相等
    for (int i = 0; i < step; i++) {
        fast = fast->next;
    }

    // 快慢指针同时前进，直到指向同一个节点
    // 注意：比较的是地址，不是数据
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }

    // 返回交点（如果不相交，fast和slow最终都为NULL）
    return fast;
}

/**
 * 主函数: 测试链表交点查找
 *
 * 测试场景:
 *   构建两个相交的字符链表
 *   listA: l -> o -> a -> d -> i -> n -> g
 *   listB: b -> e -> i -> n -> g
 *                    ↑ 交点
 */
int main(int argc, char const *argv[]) {
    // 初始化两个链表
    Node *listA = initList();
    Node *listB = initList();
    Node *tailA = get_tail(listA);
    Node *tailB = get_tail(listB);

    // 构建listA的独立部分: l -> o -> a -> d
    tailA = insertTail(tailA, 'l');
    tailA = insertTail(tailA, 'o');
    tailA = insertTail(tailA, 'a');
    tailA = insertTail(tailA, 'd');

    // 构建listB的独立部分: b -> e
    tailB = insertTail(tailB, 'b');
    tailB = insertTail(tailB, 'e');

    // 构建共享部分: i -> n -> g
    // 创建共享节点，两个链表都连接到这些节点
    Node *nodeI = initListWithElem('i');
    tailA = insertTailWithNode(tailA, nodeI);
    tailB = insertTailWithNode(tailB, nodeI);

    Node *nodeN = initListWithElem('n');
    tailA = insertTailWithNode(tailA, nodeN);
    tailB = insertTailWithNode(tailB, nodeN);

    Node *nodeG = initListWithElem('g');
    tailA = insertTailWithNode(tailA, nodeG);
    tailB = insertTailWithNode(tailB, nodeG);

    // 打印两个链表
    printf("链表A: ");
    listNode(listA);  // 输出: l o a d i n g
    printf("链表B: ");
    listNode(listB);  // 输出: b e i n g

    // 查找交点并打印
    Node *intersection = findIntersectionNode(listA, listB);
    printf("交点节点的数据: %c\n", intersection->data);  // 输出: i

    system("pause");
    return 0;
}
