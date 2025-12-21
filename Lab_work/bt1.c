#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <dos.h>
 #include <conio.h>

 #define TRUE       1
 #define FALSE      0
 #define OK         1
 #define ERROR      0
 #define INFEASIBLE -1
 #define OVERFLOW   -2

//Status 是函数的类型,其值是函数结果状态代码
typedef int Status;
//TElemType 是二叉树数据元素类型,此程序定义为char型
typedef char TElemType;

//-----二叉树的二叉链表存储表示-----
typedef struct  BiTNode{      //定义二叉树结点结构
  TElemType  data;                //数据域
  struct BiTNode *lchild,*rchild; //左右孩子指针域
}BiTNode,*BiTree;

Status CreateBiTree(BiTree &T);//生成一个二叉树(可用两种方法输入)
Status CreateBiTreeInPreOrderResult(BiTree &T);//生成一个二叉树(先序遍历结果输入)
Status CreateBiTreeInBracket(BiTree &T);//生成一个二叉树(嵌套括号法输入)
Status PrintElement(BiTree t);
Status PreOrderTraverse(BiTree T,Status (*Visit)(BiTree t)); //先序递归遍历二叉树
Status InOrderTraverse(BiTree T,Status (*Visit)(BiTree t));  //中序递归遍历二叉树
Status PostOrderTraverse(BiTree T,Status (*Visit)(BiTree t));//后序递归遍历二叉树

char * pstr;

Status CreateBiTree(BiTree &T){//生成一个二叉树(可用两种方法输入)
  int i,len,choice=0;
  char str[200];
  printf("请选择建立二叉树的方法:\n");
  printf("1.按先序遍历的结果输入二叉树\n");
  printf("2.按嵌套括号表示法输入二叉树\n");
  do{
    gets(str);
    choice = atoi(str);
  }while(choice<1||choice>2);
  if(choice==1){
    printf("请输入先序遍历二叉树的结果,程序据此建立二叉树。\n");
    printf("对于叶子结点以空格表示。\n");
    printf("例如:abc__de_g__f___(回车)，建立如下二叉树：\n");
    printf("           a      \n");
    printf("          /       \n");
    printf("         b        \n");
    printf("        / \\       \n");
    printf("       c   d      \n");
    printf("          / \\     \n");
    printf("         e   f    \n");
    printf("          \\       \n");
    printf("           g      \n");
    pstr=gets(str);
    len=strlen(str);
    for(i=len;i<180;++i)
      str[i]=' ';
    str[i]=0;
    CreateBiTreeInPreOrderResult(T);//初始化二叉树
  }
  else{
    printf("请输入嵌套括号表示法表示的二叉树,程序据此建立二叉树。\n");
    printf("例如:(a(b(c,d(e(,g),f))))(回车)，建立如下二叉树：\n");
    printf("           a      \n");
    printf("          /       \n");
    printf("         b        \n");
    printf("        / \\       \n");
    printf("       c   d      \n");
    printf("          / \\     \n");
    printf("         e   f    \n");
    printf("          \\       \n");
    printf("           g      \n");
    pstr=gets(str);
    CreateBiTreeInBracket(T);       //初始化二叉树
  }
  return OK;
}

Status CreateBiTreeInPreOrderResult(BiTree &T){
//根据存放在字符串*str中的先序遍历二叉树的结果,生成链接存储的二叉树。
//(若某结点无左孩子或右孩子,则以空格表示其"孩子")。
  if(!(*pstr)||*pstr==' '){
    T=NULL;
    pstr++;
  }
  else{
    T=(BiTNode *)malloc(sizeof(BiTNode)); //生成一个新结点
    if(!T) exit(OVERFLOW);
    T->data=*(pstr++);
    CreateBiTreeInPreOrderResult(T->lchild);  //生成左子树
    CreateBiTreeInPreOrderResult(T->rchild);  //生成右子树
  }
  return OK;
}

Status CreateBiTreeInBracket(BiTree &T){
//根据嵌套括号表示法的字符串*str生成链接存储的二叉树
//例如:*pstr="(a(b(c),d(e(,f),g)))"
  BiTree stack[100],p;
  int top=0, k;  //top为栈指针,k指定是左还是右孩子;
  T=NULL;
  while(*pstr){
    switch(*pstr){
      case '(':stack[top++]=p;k=1;break;  //左结点,其父结点为*p
      case ')':top--;             break;
      case ',':               k=2;break;  //右结点,其父结点为*p
      case ' ':                   break;
      default :
	p=(BiTree)malloc(sizeof(BiTNode));
	p->data=*pstr;
	p->lchild=p->rchild=NULL;
	if(!T) T=p;                      //根结点
	else{
	  switch(k){
	    case 1:stack[top-1]->lchild=p;break;
	    case 2:stack[top-1]->rchild=p;break;
	  }
	}
    }
    pstr++;
  }
  return OK;
}

Status DestroyBiTree(BiTree &T){
  if(T){
    if(T->lchild) DestroyBiTree(T->lchild);   //销毁左子树
    if(T->rchild) DestroyBiTree(T->rchild);   //销毁右子树
    free(T);   //销毁根结点
    T=NULL;
    return OK;
  }
  else
    return OK;
}

Status PrintElement(BiTree t){
  printf("%c",t->data);  //显示结点数据域
  return OK;
}

Status PreOrderTraverse(BiTree T, Status (*Visit)(BiTree t)){//先序
  if(T){
    if((*Visit)(T))     //访问结点
	if(PreOrderTraverse(T->lchild,Visit))   //遍历左子树
	    if(PreOrderTraverse(T->rchild,Visit))   //遍历右子树
		return OK;
    return ERROR;
  }
  else return OK;
}

Status InOrderTraverse(BiTree T, Status (*Visit)(BiTree t)){//中序
  if(T){
    if(InOrderTraverse(T->lchild,Visit))   //遍历左子树
	if((*Visit)(T))     //访问结点
	    if(InOrderTraverse(T->rchild,Visit))   //遍历右子树
		return OK;
    return ERROR;
  }
  else return OK;
}

Status PostOrderTraverse(BiTree T, Status (*Visit)(BiTree e)){//后序
  if(T){
    if(PostOrderTraverse(T->lchild,PrintElement))   //遍历左子树
	if(PostOrderTraverse(T->rchild,PrintElement))   //遍历右子树
	    if((*Visit)(T))     //访问结点
		return OK;
    return ERROR;
  }
  else return OK;
}

Status DisplayBiTreeInConcave(BiTree T){//以凹入表示法输出一棵二叉树
   BiTree stack[100],p;
   int level[100][2],top,n,i,width=4;
   char childtype[3]={'L','R','D'};
   const int MaxWidth = 30;
   if(T){
     top=0;
     stack[top]=T;          //根结点入栈
     level[top][0]=width;
     level[top][1]=2;       //2表示是根
     while(top>=0){
       p=stack[top];       //退栈并凹入显示该结点值
       n=level[top][0];
       for(i=1;i<=n;i++) printf(" ");//其中n为显示场宽,字符以右对齐显示
       printf("%c (%c)",p->data,childtype[level[top][1]]);
       for(i=n+1;i<=MaxWidth;i+=2) printf("━");
       printf("\n");
       top--;
       if(p->rchild){//将右子树根结点入栈
	 top++;
	 stack[top]=p->rchild;
	 level[top][0]=n+width; //显示场宽增width
	 level[top][1]=1;       //1表示是右子树
       }
       if(p->lchild){//将左子树根结点入栈
	 top++;
	 stack[top]=p->lchild;
	 level[top][0]=n+width;  //显示场宽增width
	 level[top][1]=0;        //0表示是左子树
       }
     }
   }
   else
     printf("该二叉树是一棵空二叉树!\n");
   return OK;
}

Status DisplayBiTreeInBracket(BiTree T){
//以嵌套括号表示法输出一棵二叉树
   if(T){
     printf("%c",T->data);
     if(T->lchild || T->rchild){
       printf("(");
       if(T->lchild) DisplayBiTreeInBracket(T->lchild);     //递归处理左子树
       if(T->rchild) printf(",");
       if(T->rchild) DisplayBiTreeInBracket(T->rchild);    //递归处理右子树
       printf(")");
     }
   }
   else
     printf("该二叉树是一棵空二叉树!");
   return OK;
}

int main(){
  BiTree T;
  char ch,j;
  char str[200];
  int choice,flag=1,len,i;
  Status temp;
  printf("本程序实现二叉树的操作:\n");
  printf("可以进行建立二叉树, 递归先序、中序、后序遍历等操作。\n");

  CreateBiTree(T);

  while(flag){
    printf("请选择: \n");
    printf("1.递归先序遍历\n");
    printf("2.递归中序遍历\n");
    printf("3.递归后序遍历\n");
    printf("4.凹入表示法输出二叉树\n");
    printf("5.嵌套括号表示法输出二叉树\n");
    printf("6.重新构建二叉树\n");
    printf("7.退出程序\n");
    scanf("%d",&choice);
    switch(choice){
      case 1:
	if(T){
	  printf("先序遍历二叉树:");
	  PreOrderTraverse(T,PrintElement); //先序递归遍历二叉树
	  printf("\n");
	}
	else
	  printf("二叉树为空!\n");
	break;
      case 2:
	if(T){
	  printf("中序遍历二叉树:");
	  InOrderTraverse(T,PrintElement);  //中序递归遍历二叉树
	  printf("\n");
	}
	else
	  printf("二叉树为空!\n");
	break;
      case 3:
	if(T){
	  printf("后序遍历二叉树:");
	  PostOrderTraverse(T,PrintElement);//后序递归遍历二叉树
	  printf("\n");
	}
	else
	  printf("二叉树为空!\n");
	break;
      case 4:
	DisplayBiTreeInConcave(T);
	break;
      case 5:
       printf("(");
	DisplayBiTreeInBracket(T);
       printf(")\n");
	break;
      case 6:
	DestroyBiTree(T);
	CreateBiTree(T);
	break;
      default:xie
	flag=0;
	printf("程序运行结束，按任意键退出!\n");
	getch();
    system("pause");
    return 0;
    }
  }

  DestroyBiTree(T);

}
