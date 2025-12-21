#ifndef __SQLIST_H__
#define __SQLIST_H__

#define MAXSIZE  1024
#define OK 1
#define NO 0


typedef int elemtype;    /*  线性表中存放整型元素  */
typedef int status;//状态 判断是否能够插入

typedef struct
{ elemtype vec[MAXSIZE];
  int len;             /*  顺序表的长度  */
 }sequenlist;


#endif