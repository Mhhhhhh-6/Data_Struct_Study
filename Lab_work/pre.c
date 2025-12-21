#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE  100
typedef struct {
    int number;
    char name[20];
    char sex[2];
    int English;
    int Computer;
    int Math;    
    int total;
    double average;
}STUDENT;
STUDENT stu[MAXSIZE];

//Tool function
static void CalcOne(STUDENT *s){
    s->total=s->English+s->Computer+s->Math;
    s->average=s->total/3.0;
}

static int GetIndexByNumber(STUDENT stu[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (stu[i].number == key) return i;
    }
    return -1;
}

static const char* SexDisplay(const char sex[2]) {
    if (sex[0]=='M' || sex[0]=='m') return "男";
    if (sex[0]=='W' || sex[0]=='w') return "女";
    return sex; // 已包含其他值时直接原样显示
}

//main function
void InputStu(STUDENT stu[],int n){
    for(int i=0;i<n;i++){
        printf("第%d位学生：\n",i+1);
        printf("学号：");
        scanf("%d",&stu[i].number);

        printf("姓名：");
        scanf("%19s",stu[i].name);

        printf("性别（M/W）：");
        scanf("%1s",stu[i].sex);

        printf("英语：");
        scanf("%d",&stu[i].English);

        printf("计算机：");
        scanf("%d",&stu[i].Computer);

        printf("高数：");
        scanf("%d",&stu[i].Math);

        CalcOne(&stu[i]);
        printf("\n");
    }
}

void OutputStu(STUDENT stu[],int n){
    if(n<=0){
        printf("当前学生表为空\n");
        return;
    }
    printf("学号\t姓名\t性别\t英语\t计算机\t高数\t总分\t平均分\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%s\t%s\t%d\t%d\t%d\t%d\t%.2f\n",
               stu[i].number,
               stu[i].name,
               SexDisplay(stu[i].sex),
               stu[i].English,
               stu[i].Computer,
               stu[i].Math,
               stu[i].total,
               stu[i].average);
    }
}

void SearchStu(STUDENT stu[],int n){
    if (n <= 0) {
        printf("当前学生表为空，查找失败\n");
        return;
    }
    int key;
    printf("请输入要查找的学号: ");
    scanf("%d", &key);

    int idx = GetIndexByNumber(stu, n, key);
    if (idx < 0) {
        printf("该学生的信息不存在，查找失败\n");
        return;
    }
    printf("已找到：\n");
    printf("学号\t姓名\t性别\t英语\t计算机\t高数\t总分\t平均分\n");
    printf("%d\t%s\t%s\t%d\t%d\t%d\t%d\t%.2f\n",
           stu[idx].number,
           stu[idx].name,
           SexDisplay(stu[idx].sex),
           stu[idx].English,
           stu[idx].Computer,
           stu[idx].Math,
           stu[idx].total,
           stu[idx].average);
}

void UpdateStu(STUDENT stu[],int n){
    if (n <= 0) {
        printf("当前学生表为空，修改失败\n");
        return;
    }
    int key;
    printf("请输入要修改的学号: ");
    scanf("%d", &key);

    int idx = GetIndexByNumber(stu, n, key);
    if (idx < 0) {
        printf("该生的信息不存在，修改失败\n");
        return;
    }

    printf("正在修改学号为 %d 的学生：\n", key);
    printf("新姓名: ");
    scanf("%19s", stu[idx].name);

    printf("新性别(M/W): ");
    scanf("%1s", stu[idx].sex);

    printf("新英语: ");
    scanf("%d", &stu[idx].English);

    printf("新计算机: ");
    scanf("%d", &stu[idx].Computer);

    printf("新高数: ");
    scanf("%d", &stu[idx].Math);

    CalcOne(&stu[idx]);

    printf("修改完成，当前学生信息如下：\n");
    OutputStu(stu, n);
}

void AppendStu(STUDENT stu[],int *pn){
    if (*pn >= MAXSIZE) {
        printf("表已满，添加失败\n");
        return;
    }
    int i = *pn;
    printf("添加一位学生：\n");

    printf("学号: ");
    scanf("%d", &stu[i].number);

    printf("姓名: ");
    scanf("%19s", stu[i].name);

    printf("性别(M/W): ");
    scanf("%1s", stu[i].sex);

    printf("英语: ");
    scanf("%d", &stu[i].English);

    printf("计算机: ");
    scanf("%d", &stu[i].Computer);

    printf("高数: ");
    scanf("%d", &stu[i].Math);

    CalcOne(&stu[i]);
    (*pn)++;

    printf("添加完成，当前学生信息如下：\n");
    OutputStu(stu, *pn);
}

int main(){
    int n = 0;
    int choice;
    while (1) {
        printf("\n===== 学生信息管理 =====\n");
        printf("1. 建立学生表(输入所有学生信息)\n");
        printf("2. 输出所有学生信息\n");
        printf("3. 查找指定学生\n");
        printf("4. 修改指定学生\n");
        printf("5. 添加一名学生\n");
        printf("0. 退出\n");
        printf("请选择: ");
        scanf("%d",&choice);
        switch (choice) {
            case 1: {
                printf("请输入学生人数 n (1-%d): ", MAXSIZE);
                scanf("%d", &n);
                if (n < 1 || n > MAXSIZE) {
                    printf("人数不合法\n");
                    n = 0;
                    break;
                }
                InputStu(stu, n);
                printf("建立完成\n");
                break;
            }
            case 2:
                OutputStu(stu, n);
                break;
            case 3:
                SearchStu(stu, n);
                break;
            case 4:
                UpdateStu(stu, n);
                break;
            case 5:
                AppendStu(stu, &n);
                break;
            case 0:
                printf("已退出\n");
                system("pause");
                return 0;
            default:
                printf("无效选择\n");
        }
    }
}