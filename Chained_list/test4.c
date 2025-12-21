/**
 * ===========================================================================
 * 文件名: test4.c
 * 描述:   双向链表的基本操作实现
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了双向链表（Double Linked List）的核心操作，包括：
 *   1. 链表的初始化和销毁
 *   2. 节点的插入（头插法、尾插法、指定位置插入）
 *   3. 节点的删除
 *   4. 链表的遍历和获取尾节点
 *
 * 数据结构:
 *   采用带头节点的双向链表，头节点不存储有效数据
 *   每个节点包含一个数据域和两个指针（prev指向前驱，next指向后继）
 *
 * 双向链表的优势:
 *   - 可以从任意节点向前或向后遍历
 *   - 删除和插入操作更加灵活
 *   - 访问前驱节点时不需要从头遍历
 *
 * 使用方法:
 *   编译: gcc test4.c -o test4
 *   运行: ./test4 (Linux/Mac) 或 test4.exe (Windows)
 *
 * 难度: ⭐⭐（基础数据结构）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 链表数据元素类型定义
typedef int ElemType;

/**
 * 双向链表节点结构定义
 *
 * 成员说明:
 *   - data: 节点存储的数据元素
 *   - next: 指向下一个节点的指针（后继指针）
 *   - prev: 指向上一个节点的指针（前驱指针）
 *
 * 与单链表的区别:
 *   单链表只有next指针，只能单向遍历
 *   双向链表有prev和next两个指针，可以双向遍历
 *
 * 示例结构:
 *   NULL ← [prev|data|next] ↔ [prev|data|next] ↔ [prev|data|next] → NULL
 */
typedef struct node{
    ElemType data;         // 数据域
    struct node *next;     // 后继指针
    struct node *prev;     // 前驱指针
}Node;

/**
 * 函数: initList
 * 功能: 初始化双向链表，创建一个带头节点的空链表
 *
 * 参数: 无
 *
 * 返回值: 返回头节点指针
 *
 * 算法思路:
 *   1. 动态分配一个头节点
 *   2. 头节点的data域初始化为0（不存储有效数据）
 *   3. 头节点的next和prev指针都初始化为NULL
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 注意事项:
 *   - 双向链表的头节点prev为NULL（前面没有节点）
 *   - 使用带头节点的链表可以简化插入和删除操作
 */
Node* initList(){
    // 为头节点分配内存空间
    Node *head=(Node*)malloc(sizeof(Node));

    // 头节点数据域初始化为0（不存储有效数据）
    head->data=0;

    // 头节点的next指针初始化为NULL，表示空链表
    head->next=NULL;

    // 头节点的prev指针初始化为NULL（头节点前面没有节点）
    head->prev=NULL;

    return head;
}

/**
 * 函数: insertHead
 * 功能: 在双向链表头部插入新节点（头插法）
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
 *   3. 新节点的prev指向头节点L
 *   4. 新节点的next指向原来的第一个节点
 *   5. 如果原来有第一个节点，更新其prev指向新节点
 *   6. 头节点的next指向新节点
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 *
 * 关键点:
 *   - 双向链表插入需要维护4个指针关系（新节点的prev和next，以及相邻节点的指针）
 *   - 必须先检查原第一个节点是否存在，再更新其prev指针
 *
 * 示例:
 *   原链表: head ↔ 10 ↔ 20 ↔ NULL
 *   insertHead(head, 30)
 *   结果: head ↔ 30 ↔ 10 ↔ 20 ↔ NULL
 */
int insertHead(Node* L,ElemType e){
    // 1. 为新节点分配内存空间
    Node *p=(Node*)malloc(sizeof(Node));

    // 2. 新节点的数据域赋值
    p->data=e;

    // 3. 新节点的prev指向头节点
    p->prev=L;

    // 4. 新节点的next指向原来的第一个节点
    p->next=L->next;

    // 5. 如果原来有第一个节点，更新其prev指向新节点
    //    （这是双向链表特有的操作）
    if(L->next!=NULL){
        L->next->prev=p;
    }

    // 6. 头节点的next指向新节点
    L->next=p;

    return 1;
}

/**
 * 函数: listNode
 * 功能: 遍历并打印双向链表中的所有元素（正向遍历）
 *
 * 参数:
 *   @param L - 链表头节点指针
 *
 * 返回值: 无
 *
 * 算法思路:
 *   从第一个有效节点开始，依次访问每个节点并打印其数据
 *   只使用next指针进行正向遍历
 *
 * 时间复杂度: O(n) - n为链表长度
 * 空间复杂度: O(1)
 *
 * 注意事项:
 *   - 双向链表也可以使用prev指针从尾到头反向遍历
 *   - 本函数采用正向遍历，与单链表遍历相同
 */
void listNode(Node* L)
{
	// p指向第一个有效节点（跳过头节点）
	Node *p = L->next;

	// 遍历链表，打印每个节点的数据
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

/**
 * 函数: get_tail
 * 功能: 获取双向链表的尾节点
 *
 * 参数:
 *   @param L - 链表头节点指针
 *
 * 返回值: 返回尾节点指针
 *
 * 算法思路:
 *   从头节点开始，通过next指针遍历，直到找到next为NULL的节点
 *
 * 时间复杂度: O(n) - n为链表长度，需要遍历整个链表
 * 空间复杂度: O(1)
 *
 * 注意事项:
 *   - 尾节点的next为NULL
 *   - 获取尾节点后可以通过prev指针反向访问链表
 */
Node*  get_tail(Node  *L)
{
	Node *p = L;

	// 遍历链表，找到最后一个节点
	while(p->next != NULL)
	{
		p = p->next;
	}

	return p;
}

/**
 * 函数: insertTail
 * 功能: 在双向链表尾部插入新节点（尾插法）
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
 *   3. 新节点的prev指向当前尾节点
 *   4. 当前尾节点的next指向新节点
 *   5. 新节点的next设置为NULL（成为新的尾节点）
 *   6. 返回新节点作为新的尾节点
 *
 * 时间复杂度: O(1) - 已知尾节点位置
 * 空间复杂度: O(1)
 *
 * 关键点:
 *   - 双向链表尾插需要设置新节点的prev和next
 *   - 需要更新原尾节点的next指针
 *
 * 示例:
 *   原链表: head ↔ 10 ↔ 20 ↔ NULL
 *   tail = insertTail(tail, 30)
 *   结果: head ↔ 10 ↔ 20 ↔ 30 ↔ NULL
 */
Node* insertTail(Node *tail,ElemType e){
    // 1. 为新节点分配内存空间
    Node *p=(Node*)malloc(sizeof(Node));

    // 2. 新节点的数据域赋值
    p->data=e;

    // 3. 新节点的prev指向当前尾节点
    p->prev=tail;

    // 4. 当前尾节点的next指向新节点
    tail->next=p;

    // 5. 新节点的next设置为NULL，表示这是最后一个节点
    p->next=NULL;

    // 6. 返回新节点作为新的尾节点
    return p;
}
/**
 * 函数: insertNode
 * 功能: 在双向链表的指定位置插入新节点
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
 *   3. 新节点的prev指向前驱节点
 *   4. 新节点的next指向前驱节点的next
 *   5. 更新后继节点的prev指向新节点
 *   6. 前驱节点的next指向新节点
 *
 * 时间复杂度: O(n) - 最坏情况需要遍历到第pos-1个节点
 * 空间复杂度: O(1)
 *
 * 关键点:
 *   - 双向链表插入需要维护4个指针关系
 *   - 必须先更新后继节点的prev，再更新前驱节点的next
 *
 * 示例:
 *   原链表: head ↔ 10 ↔ 20 ↔ 30 ↔ NULL
 *   insertNode(head, 2, 15)
 *   结果: head ↔ 10 ↔ 15 ↔ 20 ↔ 30 ↔ NULL
 */
int insertNode(Node *L, int pos, ElemType e)
{
	// p用来保存插入位置的前驱节点
	Node *p = L;
	int i = 0;

	// 遍历链表找到插入位置的前驱节点
	while(i < pos-1)
	{
		p = p->next;
		i++;

		// 如果遍历到NULL，说明pos超出链表长度
		if (p == NULL)
		{
			return 0;
		}
	}

	// 创建新节点并分配内存
	Node *q = (Node*)malloc(sizeof(Node));
	q->data = e;

	// 设置新节点的prev指向前驱节点
	q->prev = p;

	// 设置新节点的next指向原位置的节点
	q->next = p->next;

	// 更新后继节点的prev指向新节点（双向链表特有操作）
	p->next->prev = q;

	// 前驱节点的next指向新节点
	p->next = q;

	return 1;
}

/**
 * 函数: deleteNode
 * 功能: 删除双向链表中指定位置的节点
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
 *   4. 更新后继节点的prev指向前驱节点
 *   5. 释放要删除节点的内存空间
 *
 * 时间复杂度: O(n) - 最坏情况需要遍历到第pos-1个节点
 * 空间复杂度: O(1)
 *
 * 关键点:
 *   - 双向链表删除需要更新前驱和后继两个节点的指针
 *   - 必须先更新后继节点的prev，再释放要删除的节点
 *   - 删除操作比单链表多一步：更新后继节点的prev指针
 *
 * 示例:
 *   原链表: head ↔ 10 ↔ 20 ↔ 30 ↔ NULL
 *   deleteNode(head, 2)
 *   结果: head ↔ 10 ↔ 30 ↔ NULL
 */
int deleteNode(Node *L, int pos)
{
	// p用来保存要删除节点的前驱节点
	Node *p = L;
	int i = 0;

	// 遍历链表，找到要删除节点的前驱节点
	while(i < pos-1)
	{
		p = p->next;
		i++;

		// 如果遍历到NULL，说明pos超出链表长度
		if (p == NULL)
		{
			return 0;
		}
	}

	// 检查要删除的节点是否存在
	if(p->next == NULL)
	{
		printf("要删除的位置错误\n");
		return 0;
	}

	// q指向要删除的节点
	Node *q = p->next;

	// 前驱节点的next指向要删除节点的后继
	p->next = q->next;

	// 更新后继节点的prev指向前驱节点（双向链表特有操作）
	// 这样就完全将要删除的节点从链表中摘除
	q->next->prev = p;

	// 释放删除节点的内存空间
	free(q);

	return 1;
}


/**
 * 函数: freeList
 * 功能: 释放双向链表的所有节点（保留头节点）
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
 *   - 双向链表的释放过程与单链表相同，因为只需要顺着next指针释放
 */
void freeList(Node *L)
{
	// p指向第一个有效节点
	Node *p = L->next;
	Node *q;

	// 遍历链表，释放每个节点
	while(p != NULL)
	{
		q = p->next;      // 保存下一个节点的指针
		free(p);          // 释放当前节点
		p = q;            // 移动到下一个节点
	}

	// 头节点的next设置为NULL，表示空链表
	L->next = NULL;
}

/**
 * 主函数: 测试双向链表的各种操作
 *
 * 测试内容:
 *   1. 使用尾插法构建链表: 10 -> 20 -> 30
 *   2. 在位置2插入15: 10 -> 15 -> 20 -> 30
 *   3. 删除位置2的节点: 10 -> 20 -> 30
 *
 * 注意:
 *   - 头插法测试代码已注释，可根据需要取消注释测试
 *   - 双向链表的操作与单链表类似，但需要额外维护prev指针
 */
int main(int argc, char const *argv[])
{
	// 初始化双向链表
	Node *list = initList();

	/*
	// === 测试1: 头插法 ===
	insertHead(list,10);
	insertHead(list,20);
	insertHead(list,30);
	listNode(list);  // 输出: 30 20 10
	*/

	// === 测试2: 尾插法 ===
	Node *tail = get_tail(list);
	tail = insertTail(tail, 10);
	tail = insertTail(tail, 20);
	tail = insertTail(tail, 30);
	printf("尾插法构建链表: ");
	listNode(list);  // 输出: 10 20 30

	// === 测试3: 指定位置插入 ===
	insertNode(list, 2, 15);
	printf("位置2插入15后: ");
	listNode(list);  // 输出: 10 15 20 30

	// === 测试4: 删除节点 ===
	deleteNode(list, 2);
	printf("删除位置2节点后: ");
	listNode(list);  // 输出: 10 20 30

    system("pause");
	return 0;
}
