#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000

// 打印数组
void PrintArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 直接插入排序
void InsertSort(int arr[], int n) {
    int i, j, temp;
    int totalCompare = 0;  // 总比较次数
    printf("\n=== 直接插入排序 ===\n");
    printf("初始序列: ");
    PrintArray(arr, n);
    
    for (i = 1; i < n; i++) {
        temp = arr[i];
        j = i - 1;
        int compare = 0;  // 本趟比较次数
        
        // 将大于temp的元素后移
        while (j >= 0 && arr[j] > temp) {
            compare++;
            arr[j + 1] = arr[j];
            j--;
        }
        if (j >= 0) compare++;  // 最后一次比较
        
        arr[j + 1] = temp;
        totalCompare += compare;
        
        // 只在元素较少时显示每趟过程
        if (n <= 20) {
            printf("第 %d 趟: 插入 %d (比较%d次) -> ", i, temp, compare);
            PrintArray(arr, n);
        }
    }
    if (n > 20) {
        printf("最终结果: ");
        PrintArray(arr, n);
    }
    printf("排序完成! 总比较次数: %d\n", totalCompare);
}

// 折半插入排序
void BinaryInsertSort(int arr[], int n) {
    int i, j, temp, low, high, mid;
    int totalCompare = 0;  // 总比较次数
    printf("\n=== 折半插入排序 ===\n");
    printf("初始序列: ");
    PrintArray(arr, n);
    
    for (i = 1; i < n; i++) {
        temp = arr[i];
        low = 0;
        high = i - 1;
        int compare = 0;  // 本趟比较次数
        
        // 折半查找插入位置
        while (low <= high) {
            mid = (low + high) / 2;
            compare++;
            if (arr[mid] > temp) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        totalCompare += compare;
        
        // 移动元素
        for (j = i - 1; j >= low; j--) {
            arr[j + 1] = arr[j];
        }
        arr[low] = temp;
        
        // 只在元素较少时显示每趟过程
        if (n <= 20) {
            printf("第 %d 趟: 插入 %d 到位置%d (比较%d次) -> ", i, temp, low, compare);
            PrintArray(arr, n);
        }
    }
    if (n > 20) {
        printf("最终结果: ");
        PrintArray(arr, n);
    }
    printf("排序完成! 总比较次数: %d\n", totalCompare);
}

// 希尔排序
void ShellSort(int arr[], int n) {
    int i, j, gap, temp;
    int totalCompare = 0;  // 总比较次数
    printf("\n=== 希尔排序 ===\n");
    printf("初始序列: ");
    PrintArray(arr, n);
    
    int pass = 1;
    // 增量序列: n/2, n/4, ..., 1
    for (gap = n / 2; gap > 0; gap /= 2) {
        if (n <= 20) {
            printf("\n【增量 gap = %d】\n", gap);
        }
        
        // 对每个子序列进行直接插入排序
        for (i = gap; i < n; i++) {
            temp = arr[i];
            j = i - gap;
            
            // 记录是否发生移动
            int moved = 0;
            int compare = 0;  // 本次插入的比较次数
            while (j >= 0 && arr[j] > temp) {
                compare++;
                arr[j + gap] = arr[j];
                j -= gap;
                moved = 1;
            }
            if (j >= 0) compare++;  // 最后一次比较
            totalCompare += compare;
            
            arr[j + gap] = temp;
            
            if (moved && n <= 20) {
                printf("  插入 %d (比较%d次): ", temp, compare);
                PrintArray(arr, n);
            }
        }
        
        if (n <= 20) {
            printf("第 %d 趟结果: ", pass);
            PrintArray(arr, n);
        }
        pass++;
    }
    if (n > 20) {
        printf("最终结果: ");
        PrintArray(arr, n);
    }
    printf("排序完成! 总比较次数: %d\n", totalCompare);
}

// 复制数组
void CopyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// 菜单显示
void menu(void) {
    printf("\n*******************************************************\n");
    printf("1. 直接插入排序\n");
    printf("2. 折半插入排序\n");
    printf("3. 希尔排序\n");
    printf("4. 比较三种排序\n");
    printf("5. 生成随机数测试\n");
    printf("0. 退出\n");
    printf("*******************************************************\n");
    printf("请输入命令序号: ");
}

int main(void) {
    int choice;
    int n;
    int arr[MAX_SIZE];
    int temp[MAX_SIZE];
    
    while (1) {
        menu();
        if (scanf("%d", &choice) != 1) {
            printf("输入错误!\n");
            while(getchar() != '\n');  // 清空输入缓冲区
            continue;
        }
        
        if (choice == 0) {
            printf("程序运行结束!\n");
            break;
        }
        
        if (choice >= 1 && choice <= 5) {
            printf("\n请输入数组元素个数: ");
            if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
                printf("输入非法，请重新输入!\n");
                while(getchar() != '\n');  // 清空输入缓冲区
                continue;
            }
            
            if (choice == 5) {
                // 生成随机数
                printf("生成 %d 个随机数 (1-1000)\n", n);
                srand((unsigned int)time(NULL));
                for (int i = 0; i < n; i++) {
                    arr[i] = rand() % 1000 + 1;
                }
            } else {
                printf("请输入 %d 个整数（用空格或回车分隔）: \n", n);
                for (int i = 0; i < n; i++) {
                    if (scanf("%d", &arr[i]) != 1) {
                        printf("输入错误，请重新开始!\n");
                        while(getchar() != '\n');
                        i = n;  // 退出循环
                        continue;
                    }
                }
            }
            
            switch (choice) {
                case 1:
                    CopyArray(arr, temp, n);
                    InsertSort(temp, n);
                    break;
                    
                case 2:
                    CopyArray(arr, temp, n);
                    BinaryInsertSort(temp, n);
                    break;
                    
                case 3:
                    CopyArray(arr, temp, n);
                    ShellSort(temp, n);
                    break;
                    
                case 4:
                    printf("\n原始数组: ");
                    PrintArray(arr, n);
                    
                    CopyArray(arr, temp, n);
                    InsertSort(temp, n);
                    
                    CopyArray(arr, temp, n);
                    BinaryInsertSort(temp, n);
                    
                    CopyArray(arr, temp, n);
                    ShellSort(temp, n);
                    break;
                    
                case 5:
                    printf("\n原始数组: ");
                    PrintArray(arr, n);
                    
                    CopyArray(arr, temp, n);
                    InsertSort(temp, n);
                    
                    CopyArray(arr, temp, n);
                    BinaryInsertSort(temp, n);
                    
                    CopyArray(arr, temp, n);
                    ShellSort(temp, n);
                    break;
            }
        } else {
            printf("输入的命令错误！请重新输入。\n");
        }
    }
    system("pause");
    return 0;
}