#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Block {
    int id;             // 分区号（显示用，会重排：OS=0，其余从1）
    long start;         // 起始地址(KB)
    long size;          // 分区大小(KB)
    int free;           // 1=空闲, 0=已分配
    struct Block* prev;
    struct Block* next;
} Block;

typedef enum { FIRST_FIT = 1, BEST_FIT = 2, WORST_FIT = 3 } Algo;

static Block* head = NULL;  // 双向链表头（OS块）
static Block* tail = NULL;

static void renumber(void) {
    int id = 0;
    for (Block* p = head; p != NULL; p = p->next) {
        p->id = id;
        id++;
    }
}

static Block* new_block(long start, long size, int freeFlag) {
    Block* b = (Block*)malloc(sizeof(Block));
    if (!b) return NULL;
    b->id = -1;
    b->start = start;
    b->size = size;
    b->free = freeFlag;
    b->prev = b->next = NULL;
    return b;
}

static void init_memory(long osSizeKB, long freeSizeKB, long baseAddrKB) {
    // 清理旧链表（防重复初始化）
    Block* p = head;
    while (p) {
        Block* nxt = p->next;
        free(p);
        p = nxt;
    }
    head = tail = NULL;

    // OS块
    head = new_block(baseAddrKB, osSizeKB, 0);
    // 初始空闲块（紧挨OS）
    tail = new_block(baseAddrKB + osSizeKB, freeSizeKB, 1);

    head->next = tail;
    tail->prev = head;

    renumber();
}

static void show(void) {
    printf("\n\t\t》主存空间分配情况《\n");
    printf("**********************************************************\n\n");
    printf("分区序号\t起始地址(KB)\t分区大小(KB)\t分区状态\n\n");
    for (Block* p = head; p != NULL; p = p->next) {
        printf("%d\t\t%ld\t\t%ld\t\t%s\n\n",
               p->id, p->start, p->size, p->free ? "空闲" : "已分配");
    }
    printf("**********************************************************\n");
}

static Block* choose_block(long req, Algo algo) {
    Block* cand = NULL;

    if (algo == FIRST_FIT) {
        for (Block* p = head; p != NULL; p = p->next) {
            if (p->free && p->size >= req) {
                cand = p;
                break;
            }
        }
    } else if (algo == BEST_FIT) {
        long bestLeft = LONG_MAX;
        for (Block* p = head; p != NULL; p = p->next) {
            if (p->free && p->size >= req) {
                long left = p->size - req;
                if (left < bestLeft) {
                    bestLeft = left;
                    cand = p;
                }
            }
        }
    } else { // WORST_FIT
        long worstSize = -1;
        for (Block* p = head; p != NULL; p = p->next) {
            if (p->free && p->size >= req) {
                if (p->size > worstSize) {
                    worstSize = p->size;
                    cand = p;
                }
            }
        }
    }
    return cand;
}

// 成功返回新分配块id；失败返回 -1
static int allocate_mem(long req, Algo algo) {
    if (req <= 0) return -1;

    Block* b = choose_block(req, algo);
    if (!b) return -1;

    if (b->size == req) {
        b->free = 0;
        renumber();
        return b->id;
    }

    // 分裂：在 b 前插入已分配块 alloc，b 自己缩小并右移
    Block* alloc = new_block(b->start, req, 0);
    if (!alloc) return -1;

    alloc->prev = b->prev;
    alloc->next = b;

    if (b->prev) b->prev->next = alloc;
    b->prev = alloc;

    if (head == b) head = alloc;

    b->start += req;
    b->size  -= req;

    renumber();
    return alloc->id;
}

static Block* find_by_id(int id) {
    for (Block* p = head; p != NULL; p = p->next) {
        if (p->id == id) return p;
    }
    return NULL;
}

static void erase_block(Block* b) {
    if (!b) return;

    if (b->prev) b->prev->next = b->next;
    if (b->next) b->next->prev = b->prev;

    if (head == b) head = b->next;
    if (tail == b) tail = b->prev;

    free(b);
}

static int free_mem(int id) {
    if (id == 0) return 0; // OS不可释放

    Block* b = find_by_id(id);
    if (!b) return 0;
    if (b->free) return 0;

    b->free = 1;

    // 与前合并
    if (b->prev && b->prev->free) {
        Block* prev = b->prev;
        prev->size += b->size;
        erase_block(b);
        b = prev;
    }

    // 与后合并
    if (b->next && b->next->free) {
        Block* nxt = b->next;
        b->size += nxt->size;
        erase_block(nxt);
    }

    renumber();
    return 1;
}

static int read_long(const char* prompt, long* out) {
    printf("%s", prompt);
    if (scanf("%ld", out) != 1) {
        // 清理输入缓冲
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        return 0;
    }
    return 1;
}

int main(void) {
    printf("**********************************************************\n");
    printf("\t\t用以下三种方法实现主存空间的分配\n");
    printf("\t(1)首次适应算法\t(2)最佳适应算法\t(3)最差适应算法\n");
    printf("**********************************************************\n\n");

    long a = 0;
    while (1) {
        if (!read_long("请输入所使用的内存分配算法(1/2/3): ", &a)) continue;
        if (a >= 1 && a <= 3) break;
        printf("输入错误，请重新输入。\n");
    }
    Algo algo = (Algo)a;

    if (algo == FIRST_FIT) printf("\n\t****使用首次适应算法****\n");
    if (algo == BEST_FIT)  printf("\n\t****使用最佳适应算法****\n");
    if (algo == WORST_FIT) printf("\n\t****使用最差适应算法****\n");

    // 与你实验一致：OS占用40KB，空闲600KB，基址0 -> 空闲起始地址=40
    init_memory(40, 600, 0);

    while (1) {
        show();
        printf("\t1: 分配内存\t2: 回收内存\t0: 退出\n");

        long op = -1;
        if (!read_long("请输入您的操作: ", &op)) continue;

        if (op == 1) {
            long req = 0;
            if (!read_long("请输入申请分配的主存大小(单位:KB): ", &req)) continue;
            if (req <= 0) {
                printf("分配大小不合适，请重试。\n");
                continue;
            }
            int id = allocate_mem(req, algo);
            if (id >= 0) printf("\t****分配成功**** (分区号=%d)\n", id);
            else printf("\t****内存不足，分配失败****\n");
        } else if (op == 2) {
            long id = -1;
            if (!read_long("请输入您要释放的分区号: ", &id)) continue;
            if (free_mem((int)id)) printf("\t****回收成功****\n");
            else printf("\t****回收失败：分区号不存在/不可释放/已空闲****\n");
        } else if (op == 0) {
            printf("\n退出程序\n");
            break;
        } else {
            printf("输入有误，请重试。\n");
        }
    }

    // 释放链表
    Block* p = head;
    while (p) {
        Block* nxt = p->next;
        free(p);
        p = nxt;
    }
    return 0;
}
