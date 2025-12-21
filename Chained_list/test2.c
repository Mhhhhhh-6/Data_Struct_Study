#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct node{
	ElemType data;
	struct node *next;
}Node;

//初化链表
Node* initList()
{
	Node *head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	return head;
}
//初始化节点（带节点数据域参数）
Node* initListWithElem(ElemType e)
{
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = e;
	node->next = NULL;
	return node;
}

//头插法
int insertHead(Node* L, ElemType e)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = L->next;
	L->next = p;
	return 1;
}

//遍历
void listNode(Node* L)
{
	Node *p = L->next;
	while(p != NULL)
	{
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n");
}

//获取尾部结点
Node*  get_tail(Node  *L)
{
	Node *p = L;
	while(p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

//尾插法
Node* insertTail(Node *tail, ElemType e)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	tail->next = p;
	p->next = NULL;
	return p;
}

//尾插法（节点）
Node* insertTailWithNode(Node *tail, Node *node)
{
	tail->next = node;
	node->next = NULL;
	return node;
}

//指定位置插入
int insertNode(Node *L, int pos, ElemType e)
{
	Node *p = L;
	int i = 0;
	while(i < pos-1)
	{
		p = p->next;
		i++;
		if (p == NULL)
		{
			return 0;
		}
	}
	

	Node *q = (Node*)malloc(sizeof(Node));
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1;
}

//删除节点
int deleteNode(Node *L, int pos)
{
	Node *p = L;
	int i = 0;
	while(i < pos-1)
	{
		p = p->next;
		i++;
		if (p == NULL)
		{
			return 0;
		}
	}

	if(p->next == NULL)
	{
		printf("要删除的位置错误\n");
		return 0;
	}

	Node *q = p->next;
	p->next = q->next;
	free(q);
	return 1;
}

//获取链表长度
int listLength(Node *L)
{
	Node *p = L;
	int len = 0;
	while(p != NULL)
	{
		p = p->next;
		len++;
	}
	return len;
}

//释放链表
void freeList(Node *L)
{
	Node *p = L->next;
	Node *q;

	while(p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
}

//查找倒数第k个节点
int findNodeFS(Node *L, int k)
{
	Node *fast = L->next;
	Node *slow = L->next;

	for (int i = 0; i < k; i++)
	{
		fast = fast->next;
	}

	while(fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}

	printf("倒数第%d个节点值为:%d\n", k, slow->data);
	return 1;
}

//查找两个节点共同后缀的起始位置(快慢指针 先获取两个链表的长度 再让快指针先走m-n步 然后再一起走 当走到同一个地址的时候 就是共同后缀的起始位置)
Node* findIntersectionNode(Node *headA,Node *headB){
    if(headA==NULL||headB==NULL){
        return NULL;
    }
    
    Node *fast;
    Node *slow;
    int step;
    int lenA=listLength(headA);
    int lenB=listLength(headB);
    if(lenA>lenB){
        step=lenA-lenB;
        fast=headA;
        slow=headB;
    }else{
        step=lenB-lenA;
        fast=headB;
        slow=headA;
    }

    //让快指针先走step步
    for (int i=0;i<step;i++){
        fast=fast->next;
    }
    //快慢指针同时走，直到指向同一个节点退出循环
    while (fast!=slow){
        fast=fast->next;
        slow=slow->next;
    }
    return fast;
    

}

int main(int argc, char const *argv[])
{
	Node *listA = initList();
	Node *listB = initList();
	Node *tailA = get_tail(listA);
	Node *tailB = get_tail(listB);

	tailA = insertTail(tailA, 'l');
	tailA = insertTail(tailA, 'o');
	tailA = insertTail(tailA, 'a');
	tailA = insertTail(tailA, 'd');

	tailB = insertTail(tailB, 'b');
	tailB = insertTail(tailB, 'e');

	Node *nodeI = initListWithElem('i');
	tailA = insertTailWithNode(tailA, nodeI);
	tailB = insertTailWithNode(tailB, nodeI);
	Node *nodeN = initListWithElem('n');
	tailA = insertTailWithNode(tailA, nodeN);
	tailB = insertTailWithNode(tailB, nodeN);
	Node *nodeG = initListWithElem('g');
	tailA = insertTailWithNode(tailA, nodeG);
	tailB = insertTailWithNode(tailB, nodeG);

	listNode(listA);
	listNode(listB);

	printf("%c\n",findIntersectionNode(listA,listB)->data);
    system("pause");
	return 0;
}