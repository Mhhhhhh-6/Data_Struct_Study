#include <stdio.h>
#include <stdlib.h>
#include "sqlist.h"

//Init
void InitList(sequenlist *L){
    L->len=0;
}

//Create
void CreateList(sequenlist *L,int n){
    printf("请输入%d个整数:\n",n);
    for(int i=0;i<n;i++){
        scanf("%d",&L->vec[i]);
    }
    L->len=n;
}

//Print
void PrintList(sequenlist L){
    if(L.len==0){
        printf("顺序表为空\n");
        return;
    }
    printf("顺序表内容:");
    for(int i=0;i<L.len;i++){
        printf("%d ",L.vec[i]);
    }
    printf("\n顺序表长度:%d\n",L.len);
}

//Insert
status InsertList(sequenlist *L,int i,elemtype e){
    if(i<1||i>L->len+1){
        printf("插入位置错误\n");
        return NO;
    }

    if(L->len>=MAXSIZE){
        printf("顺序表已满\n");
        return NO;
    }

    for(int j=L->len;j>=i;j--){
        L->vec[j]=L->vec[j-1];
    }
    L->vec[i-1]=e;
    L->len++;
    return OK;
}

//Delete
status DeleteList(sequenlist *L, int i, elemtype *e){
    if(i<1||i>L->len+1){
        printf("删除位置错误\n");
        return NO;
    }
    *e=L->vec[i-1];//被删除元素
    
    for(int j=i;j<L->len;j++){
        L->vec[j-1]=L->vec[j];
    } 
    L->len--;
    return OK;
}

int main(){
    sequenlist L;
    int choice,n,pos;
    elemtype elem;
    int initialized=0;

    while(1){
        printf("\n===== 顺序表操作菜单 =====\n");
        printf("1. 初始化并建立顺序表\n");
        printf("2. 输出顺序表\n");
        printf("3. 插入元素\n");
        printf("4. 删除元素\n");
        printf("0. 退出\n");
        printf("========================\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("请输入顺序表元素个数n: ");
                scanf("%d", &n);
                if(n < 0 || n > MAXSIZE){
                    printf("元素个数不合法！\n");
                    break;
                }
                InitList(&L);
                CreateList(&L, n);
                initialized = 1;
                printf("顺序表建立完成！\n");
                PrintList(L);
                break;

            case 2:
                if(!initialized){
                    printf("请先建立顺序表！\n");
                    break;
                }
                PrintList(L);
                break;

            case 3:
                if(!initialized){
                    printf("请先建立顺序表！\n");
                    break;
                }
                printf("当前顺序表长度: %d\n", L.len);
                printf("请输入要插入的元素: ");
                scanf("%d", &elem);
                printf("请输入插入位置 (1-%d): ", L.len + 1);
                scanf("%d", &pos);
                
                if(InsertList(&L, pos, elem) == OK){
                    printf("插入成功！\n");
                    PrintList(L);
                }
                break;

            case 4:
                if(!initialized){
                    printf("请先建立顺序表！\n");
                    break;
                }
                if(L.len == 0){
                    printf("顺序表为空，无法删除！\n");
                    break;
                }
                printf("当前顺序表长度: %d\n", L.len);
                printf("请输入要删除的位置 (1-%d): ", L.len);
                scanf("%d", &pos);
                
                if(DeleteList(&L, pos, &elem) == OK){
                    printf("删除成功！删除的元素是: %d\n", elem);
                    PrintList(L);
                }
                break;

            case 0:
                printf("已退出\n");
                system("pause");
                return 0;

            default:
                printf("无效选择，请重新输入！\n");
        }
    }
    system("pause");
    return 0;
}