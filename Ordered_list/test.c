#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType;//元素类型

// //顺序表定义
// typedef struct {
//     ElemType data[MAXSIZE];//SeqList中有一个data数组，存放顺序表中的元素，同时实时记录顺序表的长度length
//     int length;
// } SeqList;

// //顺序表初始化
// void InitList(SeqList *L){
//     L->length = 0;
// }

//顺序表定义动态内存分配版
typedef struct{
    ElemType *data;
    int length;
}SeqList;
//初始化动态内存分配版
SeqList* InitList_malloc(){
    SeqList *L=(SeqList*)malloc(sizeof(SeqList));
    L->data=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    L->length=0;
    return L;
}

//在尾部添加元素
int appendElem(SeqList *L,ElemType e){
    if(L->length>=MAXSIZE){
        printf("顺序表已满");
        return 0;
    }
    L->data[L->length]=e;
    L->length++;
    return 1;
}

//遍历顺序表
void listElem(SeqList *L){
    for(int i=0;i<L->length;i++){
        printf("%d ",L->data[i]);
    }
    printf("\n");
}

//插入数据
int insertElem(SeqList *L,int pos,ElemType e){//若为88,45,43,17 对于88而言，pos是第一个位置
    if(L->length>=MAXSIZE){
        printf("表已经满了");
        return 0;
    }

    if(pos<1||pos>L->length){
        printf("插入位置错误");
        return 0;
    }

    if(pos<=L->length){
        for(int i=L->length-1;i>=pos-1;i--){
            L->data[i+1]=L->data[i];
        }
        L->data[pos-1]=e;
        L->length++;
    }
    return 1;
}

//删除数据
int deleteElem(SeqList *L,int pos,ElemType *e){
    if(L->length==0){
        printf("空表");
        return 0;
    }

    if(pos<1||pos>L->length){
        printf("删除数据位置错误");
        return 0;
    }

    *e=L->data[pos-1];
    if(pos<L->length){
        for(int i=pos;i<L->length;i++){
            L->data[i-1]=L->data[i];
        }
    }
    L->length--;
    return 1;
}

//查找数据位置
int findElem(SeqList *L,ElemType e){
    if(L->length==0){
        printf("空表");
        return 0;
    }

    for(int i=0;i<L->length;i++){
        if(L->data[i]==e){
            return i+1;
        }
    }
    return 0;
}

int main(){
    //声明一个顺序表并初始化
    // SeqList list;
    // InitList(&list);

    // //初始化测试
    // printf("长度：%d\n",list.length);
    // printf("字节占用：%zu\n",sizeof(list.data));

    // //添加元素
    // appendElem(&list,88);
    // appendElem(&list, 45);
	// appendElem(&list, 43);
	// appendElem(&list, 17);
    // listElem(&list);//遍历

    // insertElem(&list,2,18);//第二个位置插入18
    // listElem(&list);

    // ElemType delData;
    // deleteElem(&list,2,&delData);//删掉第二个位置的数据
    // printf("被删掉的数据为：%d\n",delData);
    // listElem(&list);

    // //查找元素
    // ElemType Tofind_elem=88;
    // if(findElem(&list,Tofind_elem)){
    //     printf("%d这个数字在第%d个\n",Tofind_elem,findElem(&list,Tofind_elem));
    // }else {
    //     printf("没找到\n");
    // }
    

    //动态内存分配版本
    //声明一个顺序表并初始化
    SeqList *list=InitList_malloc();
    //初始化测试
    printf("长度：%d\n",list->length);
    printf("字节占用：%zu\n",sizeof(list->data));

    //添加元素
        appendElem(list,88);
        appendElem(list,45);
        appendElem(list,43);
        appendElem(list,17);
        listElem(list);//遍历

        insertElem(list,2,18);//第二个位置插入18
        listElem(list);

        ElemType delData;
        deleteElem(list,2,&delData);//删掉第二个位置的数据
        printf("被删掉的数据为：%d\n",delData);
        listElem(list);

        //查找元素
        ElemType Tofind_elem=88;
        if(findElem(list,Tofind_elem)){
            printf("%d这个数字在第%d个\n",Tofind_elem,findElem(list,Tofind_elem));
        }else {
            printf("没找到\n");
        }
        free(list->data);
        free(list);
        system("pause");
        return 0;
}