/**
 * ===========================================================================
 * 文件名: test.c
 * 描述:   顺序表的基本操作实现（动态内存版本）
 * 日期:   2025-12-21
 * ===========================================================================
 *
 * 功能说明:
 *   本文件实现了顺序表（Sequential List）的核心操作，包括：
 *   1. 顺序表的动态初始化
 *   2. 在尾部追加元素
 *   3. 在指定位置插入元素
 *   4. 删除指定位置的元素
 *   5. 查找元素位置
 *   6. 遍历顺序表
 *
 * 数据结构:
 *   采用动态数组实现的顺序表
 *   使用length记录当前元素个数
 *
 * 顺序表特点:
 *   - 逻辑顺序与物理顺序一致
 *   - 支持随机访问（O(1)）
 *   - 插入和删除需要移动元素（O(n)）
 *   - 需要预分配或动态分配连续的内存空间
 *
 * 顺序表 vs 链表:
 *   ┌────────────┬─────────┬─────────┐
 *   │ 操作       │ 顺序表  │ 链表    │
 *   ├────────────┼─────────┼─────────┤
 *   │ 随机访问   │ O(1)    │ O(n)    │
 *   │ 插入/删除  │ O(n)    │ O(1)    │
 *   │ 内存       │ 连续    │ 分散    │
 *   │ 空间利用率 │ 高      │ 低(指针)│
 *   └────────────┴─────────┴─────────┘
 *
 * 使用方法:
 *   编译: gcc test.c -o test
 *   运行: ./test (Linux/Mac) 或 test.exe (Windows)
 *
 * 难度: ⭐（基础数据结构）
 * ===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 顺序表的最大容量
#define MAXSIZE 100

// 元素类型定义
typedef int ElemType;

// 静态数组版本（已注释，供参考）
// typedef struct {
//     ElemType data[MAXSIZE];  // 静态数组
//     int length;              // 当前长度
// } SeqList;
//
// void InitList(SeqList *L){
//     L->length = 0;
// }

/**
 * 顺序表结构定义（动态内存版本）
 *
 * 成员说明:
 *   - data: 指向动态分配的数组的指针
 *   - length: 顺序表的当前长度（元素个数）
 *
 * 与静态版本的区别:
 *   静态版本: ElemType data[MAXSIZE];
 *   动态版本: ElemType *data;
 */
typedef struct{
    ElemType *data;  // 指向动态分配的数组
    int length;      // 当前长度
}SeqList;

/**
 * 函数: InitList_malloc
 * 功能: 初始化顺序表（动态分配内存）
 *
 * 返回值: 返回指向新创建的顺序表的指针
 *
 * 算法思路:
 *   1. 为SeqList结构分配内存
 *   2. 为data数组分配MAXSIZE个元素的内存
 *   3. length初始化为0
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(MAXSIZE)
 */
SeqList* InitList_malloc(){
    SeqList *L=(SeqList*)malloc(sizeof(SeqList));
    L->data=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    L->length=0;
    return L;
}

/**
 * 函数: appendElem
 * 功能: 在顺序表尾部追加元素
 *
 * 参数:
 *   @param L - 指向顺序表的指针
 *   @param e - 要追加的元素
 *
 * 返回值:
 *   1 - 追加成功
 *   0 - 追加失败（表满）
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */
int appendElem(SeqList *L,ElemType e){
    // 检查顺序表是否已满
    if(L->length>=MAXSIZE){
        printf("顺序表已满");
        return 0;
    }

    // 在尾部添加元素
    L->data[L->length]=e;

    // 长度加1
    L->length++;

    return 1;
}

/**
 * 函数: listElem
 * 功能: 遍历并打印顺序表中的所有元素
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
void listElem(SeqList *L){
    for(int i=0;i<L->length;i++){
        printf("%d ",L->data[i]);
    }
    printf("\n");
}

/**
 * 函数: insertElem
 * 功能: 在顺序表的指定位置插入元素
 *
 * 参数:
 *   @param L - 指向顺序表的指针
 *   @param pos - 插入位置（从1开始计数）
 *   @param e - 要插入的元素
 *
 * 返回值:
 *   1 - 插入成功
 *   0 - 插入失败
 *
 * 算法思路:
 *   1. 检查表是否已满
 *   2. 检查插入位置是否合法
 *   3. 将pos位置及其后的元素依次后移一位
 *   4. 在pos位置插入新元素
 *   5. 长度加1
 *
 * 时间复杂度:
 *   最好: O(1) - 在表尾插入
 *   最坏: O(n) - 在表头插入，需要移动所有元素
 *   平均: O(n/2)
 *
 * 示例:
 *   原表: [88, 45, 43, 17]
 *   insertElem(L, 2, 18)
 *   结果: [88, 18, 45, 43, 17]
 */
int insertElem(SeqList *L,int pos,ElemType e){
    // 检查表是否已满
    if(L->length>=MAXSIZE){
        printf("表已经满了");
        return 0;
    }

    // 检查插入位置是否合法（pos从1开始）
    if(pos<1||pos>L->length+1){
        printf("插入位置错误");
        return 0;
    }

    // 将pos位置及其后的元素依次后移
    if(pos<=L->length){
        for(int i=L->length-1;i>=pos-1;i--){
            L->data[i+1]=L->data[i];
        }

        // 在pos位置插入新元素
        L->data[pos-1]=e;

        // 长度加1
        L->length++;
    }

    return 1;
}

/**
 * 函数: deleteElem
 * 功能: 删除顺序表中指定位置的元素
 *
 * 参数:
 *   @param L - 指向顺序表的指针
 *   @param pos - 删除位置（从1开始计数）
 *   @param e - 指向用于存储被删除元素的变量指针
 *
 * 返回值:
 *   1 - 删除成功
 *   0 - 删除失败
 *
 * 算法思路:
 *   1. 检查表是否为空
 *   2. 检查删除位置是否合法
 *   3. 取出要删除的元素
 *   4. 将pos后面的元素依次前移一位
 *   5. 长度减1
 *
 * 时间复杂度:
 *   最好: O(1) - 删除表尾元素
 *   最坏: O(n) - 删除表头元素，需要移动所有后续元素
 *   平均: O(n/2)
 *
 * 示例:
 *   原表: [88, 18, 45, 43, 17]
 *   deleteElem(L, 2, &e)
 *   结果: [88, 45, 43, 17], e=18
 */
int deleteElem(SeqList *L,int pos,ElemType *e){
    // 检查表是否为空
    if(L->length==0){
        printf("空表");
        return 0;
    }

    // 检查删除位置是否合法
    if(pos<1||pos>L->length){
        printf("删除数据位置错误");
        return 0;
    }

    // 取出要删除的元素
    *e=L->data[pos-1];

    // 将pos后面的元素依次前移
    if(pos<L->length){
        for(int i=pos;i<L->length;i++){
            L->data[i-1]=L->data[i];
        }
    }

    // 长度减1
    L->length--;

    return 1;
}

/**
 * 函数: findElem
 * 功能: 查找元素在顺序表中的位置
 *
 * 参数:
 *   @param L - 指向顺序表的指针
 *   @param e - 要查找的元素
 *
 * 返回值:
 *   成功 - 返回元素位置（从1开始）
 *   失败 - 返回0（未找到）
 *
 * 算法思路:
 *   顺序遍历顺序表，找到第一个与e相等的元素
 *
 * 时间复杂度:
 *   最好: O(1) - 第一个元素就是
 *   最坏: O(n) - 最后一个元素或不存在
 *   平均: O(n/2)
 */
int findElem(SeqList *L,ElemType e){
    // 检查表是否为空
    if(L->length==0){
        printf("空表");
        return 0;
    }

    // 顺序查找
    for(int i=0;i<L->length;i++){
        if(L->data[i]==e){
            return i+1;  // 返回位置（从1开始）
        }
    }

    return 0;  // 未找到
}

/**
 * 主函数: 测试顺序表的各种操作
 *
 * 测试流程:
 *   1. 初始化顺序表
 *   2. 追加4个元素: 88, 45, 43, 17
 *   3. 在位置2插入18: [88, 18, 45, 43, 17]
 *   4. 删除位置2的元素: [88, 45, 43, 17]
 *   5. 查找元素88的位置
 *   6. 释放动态分配的内存
 *
 * 内存管理:
 *   正确地释放了data数组和SeqList结构
 */
int main(){
    //静态版本测试（已注释）
    // SeqList list;
    // InitList(&list);
    // printf("长度：%d\n",list.length);
    // printf("字节占用：%zu\n",sizeof(list.data));
    // appendElem(&list,88);
    // appendElem(&list, 45);
	// appendElem(&list, 43);
	// appendElem(&list, 17);
    // listElem(&list);
    // insertElem(&list,2,18);
    // listElem(&list);
    // ElemType delData;
    // deleteElem(&list,2,&delData);
    // printf("被删掉的数据为：%d\n",delData);
    // listElem(&list);
    // ElemType Tofind_elem=88;
    // if(findElem(&list,Tofind_elem)){
    //     printf("%d这个数字在第%d个\n",Tofind_elem,findElem(&list,Tofind_elem));
    // }else {
    //     printf("没找到\n");
    // }


    // ========== 动态内存分配版本测试 ==========

    // 1. 初始化顺序表
    SeqList *list=InitList_malloc();
    printf("初始长度：%d\n",list->length);
    printf("data指针占用字节：%zu\n",sizeof(list->data));

    // 2. 追加元素
    appendElem(list,88);
    appendElem(list,45);
    appendElem(list,43);
    appendElem(list,17);
    printf("追加4个元素后: ");
    listElem(list);

    // 3. 在位置2插入元素18
    insertElem(list,2,18);
    printf("位置2插入18后: ");
    listElem(list);

    // 4. 删除位置2的元素
    ElemType delData;
    deleteElem(list,2,&delData);
    printf("删除位置2元素后: ");
    listElem(list);
    printf("被删掉的数据为：%d\n",delData);

    // 5. 查找元素
    ElemType Tofind_elem=88;
    int pos=findElem(list,Tofind_elem);
    if(pos){
        printf("%d这个数字在第%d个位置\n",Tofind_elem,pos);
    }else {
        printf("没找到\n");
    }

    // 6. 释放动态分配的内存
    free(list->data);
    free(list);

    system("pause");
    return 0;
}
