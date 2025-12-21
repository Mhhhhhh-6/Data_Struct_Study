#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
    ElemType data;
    struct node *next; 
}Node;//由一个data和下一个data的地址构成

//初始化链表
Node* InitList(){
    Node *head=(Node*)malloc(sizeof(Node));
    head->data=0;
    head->next=NULL;
    return head;
}

//头插法
int insertHead(Node* L,ElemType e){
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    p->next=L->next;
    L->next=p;
    return 1;
}

//获取尾部结点
Node* get_tail(Node *L){
    Node *p=L;
    while(p->next!=NULL){
        p=p->next;
    }
    return p;
}

//尾插法
Node* insertTail(Node *tail,ElemType e){
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    tail->next=p;
    p->next=NULL;
    return p;
}

//指定位置插入
int insertNode(Node *L,int pos,ElemType e){
    //用来保存插入位置的前躯节点
    Node *p=L;
    int i=0;

    //遍历链表找到插入位置的前驱节点
    while(i<pos-1){
        p=p->next;
        i++;
        if(p==NULL){
            return 0;
        }
    }

    //定义插入的新节点
    Node *q=(Node*)malloc(sizeof(Node));
    q->data=e;
    q->next=p->next;
    p->next=q;
    return 1;
}

//遍历
void listNode(Node* L){
    Node *p=L->next;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

//删除节点
int deleteNode(Node *L,int pos){
    //要删除节点的前驱
    Node *p=L;
    int i=0;
    //遍历链表，找到要删除的节点的前驱
    while(i<pos-1)
    {
        p=p->next;
        i++;
        if(p==NULL){
            return 0;
        }
    }

    if(p->next==NULL){
        printf("要删除的位置错误");
        return 0;
    }
    //q指向要删除的节点
    Node *q=p->next;
    //让要删除节点的前驱指向要删除节点的后继
    p->next=q->next;
    //释放删除节点的内存空间
    free(q);
    return 1;
}

//获取链表长度
int listLength(Node *L){
    Node *p=L;
    int len=0;
    while(p->next!=NULL){
        p=p->next;
        len++;
    }
    return len;
}

//释放链表
void freeList(Node *L){
    Node *p=L->next;
    Node *q;
    while(p!=NULL){
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL;
}

//查找倒数第k个节点(快慢指针 快指针先走三步 然后快慢指针同时走 当快指针走到)
int findNodeFS(Node *L,int k){
    Node *fast=L->next;
    Node *slow=L->next;
    for(int i=0;i<k;i++){
        fast=fast->next;
    }

    while(fast!=NULL){
        fast=fast->next;
        slow=slow->next;
    }

    printf("倒数第%d个节点值为:%d\n",k,slow->data);
    return 1;
}

int main(){

    Node *list=InitList();

    //头插法
    // insertHead(list,10);
    // insertHead(list,20);
    // insertHead(list,30);

    //尾插法
    Node *tail=get_tail(list);
    tail=insertTail(tail,10);
    tail=insertTail(tail,20);
    tail=insertTail(tail,30);
    tail=insertTail(tail,40);
	tail=insertTail(tail,50);
	tail=insertTail(tail,60);
	tail=insertTail(tail,70);
    listNode(list);
    findNodeFS(list,3);

    //测试
    // listNode(list);
    // insertNode(list,2,15);
    // listNode(list);
    // deleteNode(list,2);
    // listNode(list);
    // printf("length:%d\n",listLength(list));
    // freeList(list);
    // printf("%d\n",listLength(list));
    system("pause");
    return 0;
}