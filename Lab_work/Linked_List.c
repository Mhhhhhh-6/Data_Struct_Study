#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef struct node{
    elemtype data;
    struct node *next;
}linklist;

//Init
static linklist *InitList(){
    linklist *head=(linklist*)malloc(sizeof(linklist));
    head->data=0;
    head->next=NULL;
    return head;
}

//DestroyList
static void DestroyList(linklist *head){
    linklist *p=head;
    while(p){
        linklist *tmp=p->next;
        free(p);
        p=tmp;
    }
}

//TailCreate
static void TailCreate(linklist *head,int n){
    linklist *tail=head;
    while(tail->next){
        tail->next;
    }
    printf("请输入%d个整数:\n",n);
    for(int i=0;i<n;i++){
        linklist *node=(linklist*)malloc(sizeof(linklist));
        scanf("%d",&node->data);
        node->next=NULL;
        tail->next=node;
        tail=node;
    }
}

//PrintList
static void PrintList(const linklist *head){
    const linklist *p=head->next;
    if(!p){
        printf("链表为空\n");
        return;
    }
    printf("链表:");
    while(p){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

//ListLength
static int ListLength(const linklist *head){
    int len=0;
    const linklist *p=head->next;
    while(p){
        len++;
        p=p->next;
    }
    return len;
}

//InsertList
static int InsertList(linklist *head,int pos,elemtype e){
    if(pos<1) return 0;
    linklist *p=head;
    for(int i=1;i<pos&&p;i++) p=p->next;
    if(!p)return 0;

    linklist *node=(linklist*)malloc(sizeof(linklist));
    if(!node) return 0;
    node->data=e;
    node->next=p->next;
    p->next=node;
    return 1;
}

//DeleteList
static int DeleteList(linklist *head,int pos,elemtype *e){
    if(pos<1) return 0;
    linklist *p=head;
    for(int i=1;i<pos&&p->next;i++) p=p->next;
    if(!p->next) return 0;
    linklist *del=p->next;
    *e=del->data;
    p->next=del->next;
    free(del);
    return 1;
}

int main(){
    linklist *head =InitList();
    int initialized=0;
    int choice;
    while (1) {
        printf("\n===== 单链表操作菜单 =====\n");
        printf("1. 尾插法建立单链表\n");
        printf("2. 输出链表\n");
        printf("3. 在第i个位置插入元素\n");
        printf("4. 删除第i个位置元素\n");
        printf("0. 退出\n");
        printf("=========================\n");
        printf("请选择: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("已退出\n");
            break;
        }

        if (choice == 1) {
            int n;
            printf("请输入结点个数 n: ");
            scanf("%d", &n);
            if (n < 0) {
                printf("n 不合法\n");
                continue;
            }
            DestroyList(head);
            head = InitList();
            TailCreate(head, n);
            initialized = 1;
            PrintList(head);
        } else if (!initialized) {
            printf("请先建立链表！\n");
            continue;
        } else if (choice == 2) {
            PrintList(head);
        } else if (choice == 3) {
            int pos;
            elemtype val;
            printf("当前长度: %d\n", ListLength(head));
            printf("请输入插入位置 i: ");
            scanf("%d", &pos);
            printf("请输入元素值: ");
            scanf("%d", &val);
            if (InsertList(head, pos, val))
                PrintList(head);
            else
                printf("插入失败\n");
        } else if (choice == 4) {
            int pos;
            elemtype val;
            printf("当前长度: %d\n", ListLength(head));
            printf("请输入删除位置 i: ");
            scanf("%d", &pos);
            if (DeleteList(head, pos, &val)) {
                printf("删除元素: %d\n", val);
                PrintList(head);
            } else {
                printf("删除失败\n");
            }
        } else {
            printf("无效选择\n");
        }
    }

    DestroyList(head);

    system("pause");
    return 0;
}