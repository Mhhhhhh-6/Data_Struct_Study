/**
 * ===========================================================================
 * 文件名: test.c
 * 描述:   单链表的基本操作实现
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了单链表的核心操作，包括：
 *   1. 链表的初始化和销毁
 *   2. 节点的插入（头插法、尾插法、指定位置插入）
 *   3. 节点的删除
 *   4. 链表的遍历和长度计算
 *   5. 快慢指针查找倒数第k个节点
 *
 * 数据结构:
 *   采用带头节点的单链表，头节点不存储有效数据
 *   每个节点包含一个数据域和一个指向下一个节点的指针
 *
 * 使用方法:
 *   编译: gcc test.c -o test
 *   运行: ./test (Linux/Mac) 或 test.exe (Windows)
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 链表数据元素类型定义
typedef int ElemType;

/**
 * 单链表节点结构定义
 *
 * 成员说明:
 *   - data: 节点存储的数据元素
 *   - next: 指向下一个节点的指针
 *
 * 说明:
 *   采用单链表结构，每个节点包含一个数据域和一个指针域
 *   指针域指向下一个节点，最后一个节点的指针域为NULL
 */
typedef struct node {
    ElemType data;         // 数据域
    struct node *next;     // 指针域，指向下一个节点
} Node;

/**
 * 函数: InitList
 * 功能: 初始化链表，创建一个带头节点的空链表
 *
 * 参数: 无
 *
 * 返回值: 返回头节点指针
 *
 * 算法思路:
 *   1. 动态分配一个头节点
 *   2. 头节点的data域初始化为0（不存储有效数据）
 *   3. 头节点的next指针初始化为NULL
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 注意事项:
 *   - 头节点不存储有效数据，仅作为链表的入口
 *   - 使用带头节点的链表可以简化插入和删除操作
 */
Node* InitList() {
    // 为头节点分配内存空间
    Node *head = (Node*)malloc(sizeof(Node));

    // 头节点数据域初始化为0（不存储有效数据）
    head->data = 0;

    // 头节点的next指针初始化为NULL，表示空链表
    head->next = NULL;

    return head;
}

/**
 * 函数: insertHead
 * 功能: 在链表头部插入新节点（头插法）
 *
 * 参数:
 *   @param L - 链表头节点指针
 *   @param e - 要插入的数据元素
 *
 * 返回值: 成功返回1
 *
 * 算法思路:
 *   1. 创建新节点并分配内存
 *   2. 新节点的数据域赋值为e
 *   3. 新节点的next指向原来的第一个节点
 *   4. 头节点的next指向新节点
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 示例:
 *   原链表: head -> NULL
 *   insertHead(head, 10)
 *   结果: head -> 10 -> NULL
 *   insertHead(head, 20)
 *   结果: head -> 20 -> 10 -> NULL
 */
int insertHead(Node* L, ElemType e) {
    // 1. 为新节点分配内存空间
    Node *p = (Node*)malloc(sizeof(Node));

    // 2. 新节点的数据域赋值
    p->data = e;

    // 3. 新节点的next指向原来的第一个节点
    p->next = L->next;

    // 4. 头节点的next指向新节点
    L->next = p;

    return 1;
}

/**
 * 函数: get_tail
 * 功能: 获取链表的尾节点
 *
 * 参数:
 *   @param L - 链表头节点指针
 *
 * 返回值: 返回尾节点指针
 *
 * 算法思路:
 *   从头节点开始遍历，直到找到next为NULL的节点
 *
 * 时间复杂度: O(n) - n为链表长度，需要遍历整个链表
 * 空间复杂度: O(1)
 */
Node* get_tail(Node *L) {
    Node *p = L;

    // 遍历链表，找到最后一个节点
    while (p->next != NULL) {
        p = p->next;
    }

    return p;
}

/**
 * 函数: insertTail
 * 功能: 在链表尾部插入新节点（尾插法）
 *
 * 参数:
 *   @param tail - 当前尾节点指针
 *   @param e - 要插入的数据元素
 *
 * 返回值: 返回新的尾节点指针
 *
 * 算法思路:
 *   1. 创建新节点并分配内存
 *   2. 新节点的数据域赋值为e
 *   3. 当前尾节点的next指向新节点
 *   4. 新节点的next设置为NULL
 *   5. 返回新节点作为新的尾节点
 *
 * 时间复杂度: O(1) - 已知尾节点位置
 * 空间复杂度: O(1)
 *
 * 注意事项:
 *   - 需要保存并更新尾节点指针，否则每次插入都需要O(n)时间查找尾节点
 *
 * 示例:
 *   原链表: head -> 10 -> NULL
 *   tail = insertTail(tail, 20)
 *   结果: head -> 10 -> 20 -> NULL
 */
Node* insertTail(Node *tail, ElemType e) {
    // 1. 为新节点分配内存空间
    Node *p = (Node*)malloc(sizeof(Node));

    // 2. 新节点的数据域赋值
    p->data = e;

    // 3. 当前尾节点的next指向新节点
    tail->next = p;

    // 4. 新节点的next设置为NULL，表示这是最后一个节点
    p->next = NULL;

    // 5. 返回新节点作为新的尾节点
    return p;
}

/**
 * 函数: insertNode
 * 功能: 在链表的指定位置插入新节点
 *
 * 参数:
 *   @param L - 链表头节点指针
 *   @param pos - 插入位置（从1开始计数）
 *   @param e - 要插入的数据元素
 *
 * 返回值: 成功返回1，失败返回0
 *
 * 算法思路:
 *   1. 从头节点开始遍历，找到插入位置的前驱节点
 *   2. 创建新节点
 *   3. 新节点的next指向前驱节点的next
 *   4. 前驱节点的next指向新节点
 *
 * 时间复杂度: O(n) - 最坏情况需要遍历到第pos-1个节点
 * 空间复杂度: O(1)
 *
 * 注意事项:
 *   - pos从1开始计数（第一个有效节点为位置1）
 *   - 如果pos超出链表长度，返回0表示插入失败
 *
 * 示例:
 *   原链表: head -> 10 -> 20 -> 30 -> NULL
 *   insertNode(head, 2, 15)
 *   结果: head -> 10 -> 15 -> 20 -> 30 -> NULL
 */
int insertNode(Node *L, int pos, ElemType e) {
    // p用来保存插入位置的前驱节点
    Node *p = L;
    int i = 0;

    // 遍历链表找到插入位置的前驱节点
    while (i < pos - 1) {
        p = p->next;
        i++;

        // 如果遍历到NULL，说明pos超出链表长度
        if (p == NULL) {
            return 0;
        }
    }

    // 创建新节点并分配内存
    Node *q = (Node*)malloc(sizeof(Node));
    q->data = e;

    // 新节点的next指向原位置的节点
    q->next = p->next;

    // 前驱节点的next指向新节点
    p->next = q;

    return 1;
}

/**
 * 函数: listNode
 * 功能: 遍历并打印链表中的所有元素
 *
 * 参数:
 *   @param L - 链表头节点指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   从第一个有效节点开始，依次访问每个节点并打印其数据
 *
 * 时间复杂度: O(n) - n为链表长度
 * 空间复杂度: O(1)
 */
void listNode(Node* L) {
    // p指向第一个有效节点（跳过头节点）
    Node *p = L->next;

    // 遍历链表，打印每个节点的数据
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/**
 * 函数: deleteNode
 * 功能: 删除链表中指定位置的节点
 *
 * 参数:
 *   @param L - 链表头节点指针
 *   @param pos - 要删除的位置（从1开始计数）
 *
 * 返回值: 成功返回1，失败返回0
 *
 * 算法思路:
 *   1. 从头节点开始遍历，找到要删除节点的前驱节点
 *   2. 保存要删除的节点指针
 *   3. 前驱节点的next指向要删除节点的next
 *   4. 释放要删除节点的内存空间
 *
 * 时间复杂度: O(n) - 最坏情况需要遍历到第pos-1个节点
 * 空间复杂度: O(1)
 *
 * 注意事项:
 *   - pos从1开始计数
 *   - 如果pos超出链表长度，返回0表示删除失败
 *   - 必须释放被删除节点的内存，避免内存泄漏
 *
 * 示例:
 *   原链表: head -> 10 -> 20 -> 30 -> NULL
 *   deleteNode(head, 2)
 *   结果: head -> 10 -> 30 -> NULL
 */
int deleteNode(Node *L, int pos) {
    // p用来保存要删除节点的前驱节点
    Node *p = L;
    int i = 0;

    // 遍历链表，找到要删除节点的前驱节点
    while (i < pos - 1) {
        p = p->next;
        i++;

        // 如果遍历到NULL，说明pos超出链表长度
        if (p == NULL) {
            return 0;
        }
    }

    // 检查要删除的节点是否存在
    if (p->next == NULL) {
        printf("要删除的位置错误\n");
        return 0;
    }

    // q指向要删除的节点
    Node *q = p->next;

    // 前驱节点的next指向要删除节点的后继
    // 这样就跳过了要删除的节点
    p->next = q->next;

    // 释放删除节点的内存空间
    free(q);

    return 1;
}

/**
 * 函数: listLength
 * 功能: 计算链表的长度（有效节点数量）
 *
 * 参数:
 *   @param L - 链表头节点指针
 *
 * 返回值: 返回链表长度
 *
 * 算法思路:
 *   从头节点开始遍历，计数每个有效节点
 *
 * 时间复杂度: O(n) - n为链表长度
 * 空间复杂度: O(1)
 */
int listLength(Node *L) {
    Node *p = L;
    int len = 0;

    // 遍历链表，统计节点数量
    while (p->next != NULL) {
        p = p->next;
        len++;
    }

    return len;
}

/**
 * 函数: freeList
 * 功能: 释放链表的所有节点（保留头节点）
 *
 * 参数:
 *   @param L - 链表头节点指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   从第一个有效节点开始，依次释放每个节点的内存
 *   保留头节点，将其next设置为NULL
 *
 * 时间复杂度: O(n) - n为链表长度
 * 空间复杂度: O(1)
 *
 * 注意事项:
 *   - 必须先保存next指针，再释放当前节点
 *   - 否则会因为访问已释放的内存而导致错误
 */
void freeList(Node *L) {
    // p指向第一个有效节点
    Node *p = L->next;
    Node *q;

    // 遍历链表，释放每个节点
    while (p != NULL) {
        q = p->next;      // 保存下一个节点的指针
        free(p);          // 释放当前节点
        p = q;            // 移动到下一个节点
    }

    // 头节点的next设置为NULL，表示空链表
    L->next = NULL;
}

/**
 * 函数: findNodeFS
 * 功能: 查找链表中倒数第k个节点（使用快慢指针法）
 *
 * 参数:
 *   @param L - 链表头节点指针
 *   @param k - 倒数第k个（k从1开始）
 *
 * 返回值: 成功返回1
 *
 * 算法思路:
 *   1. 定义快指针fast和慢指针slow，初始都指向第一个有效节点
 *   2. 快指针先向前移动k步
 *   3. 快慢指针同时向前移动，直到快指针到达链表末尾
 *   4. 此时慢指针指向的就是倒数第k个节点
 *
 * 时间复杂度: O(n) - n为链表长度，只需遍历一次
 * 空间复杂度: O(1)
 *
 * 算法原理:
 *   快慢指针之间相差k个节点
 *   当快指针到达末尾时，慢指针正好指向倒数第k个节点
 *
 * 示例:
 *   链表: head -> 10 -> 20 -> 30 -> 40 -> 50 -> NULL
 *   findNodeFS(head, 2)
 *   初始: fast=10, slow=10
 *   fast先走2步: fast=30, slow=10
 *   同时前进:
 *     fast=40, slow=20
 *     fast=50, slow=30
 *     fast=NULL, slow=40
 *   结果: 倒数第2个节点值为40
 */
int findNodeFS(Node *L, int k) {
    // 快指针和慢指针都指向第一个有效节点
    Node *fast = L->next;
    Node *slow = L->next;

    // 快指针先向前移动k步
    for (int i = 0; i < k; i++) {
        fast = fast->next;
    }

    // 快慢指针同时向前移动
    // 当快指针到达末尾时，慢指针指向倒数第k个节点
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    printf("倒数第%d个节点值为: %d\n", k, slow->data);
    return 1;
}

/**
 * 主函数: 测试链表的各种操作
 */
int main() {
    // 初始化链表
    Node *list = InitList();

    // === 测试1: 头插法 ===
    // insertHead(list, 10);
    // insertHead(list, 20);
    // insertHead(list, 30);
    // 结果: 30 -> 20 -> 10

    // === 测试2: 尾插法 ===
    Node *tail = get_tail(list);
    tail = insertTail(tail, 10);
    tail = insertTail(tail, 20);
    tail = insertTail(tail, 30);
    tail = insertTail(tail, 40);
    tail = insertTail(tail, 50);
    tail = insertTail(tail, 60);
    tail = insertTail(tail, 70);

    // 打印链表
    printf("当前链表: ");
    listNode(list);

    // 查找倒数第3个节点
    findNodeFS(list, 3);

    // === 测试3: 其他操作 ===
    // listNode(list);
    // insertNode(list, 2, 15);    // 在位置2插入15
    // listNode(list);
    // deleteNode(list, 2);         // 删除位置2的节点
    // listNode(list);
    // printf("链表长度: %d\n", listLength(list));
    // freeList(list);              // 释放链表
    // printf("释放后长度: %d\n", listLength(list));

    system("pause");
    return 0;
}
