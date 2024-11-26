#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

typedef struct LNode {
    int data;
    struct LNode* next;
} LNode, * LinkList;

// 初始化链表
bool InitList(LinkList* L) {
    *L = (LNode*)malloc(sizeof(LNode)); // 使用指向指针的指针来修改原指针
    if (*L == NULL) {
        return false; // 分配失败
    }
    (*L)->next = NULL; // 将 next 指针初始化为 NULL
    return true;
}

// 插入节点到链表
bool Insert(LinkList L) {
    LNode* r = L; // 从头节点开始
    int x = 0;

    printf("输入值（9999 结束）：\n");
    while (1) {
        scanf_s("%d", &x); // 使用 scanf，确保兼容性
        if (x == 9999) break; // 遇到哨兵值时退出循环

        LNode* s = (LNode*)malloc(sizeof(LNode)); // 创建新节点
        if (s == NULL) {
            return false; // 检查 malloc 是否成功
        }

        s->data = x; // 将输入数据赋值给新节点
        s->next = NULL; // 初始化新节点的 next 指针
        r->next = s; // 将前一个节点与新节点链接
        r = s; // 当前指针移动到新节点
    }

    return true;
}

// 显示链表
void DisplayList(LinkList L) {
    LNode* current = L->next; // 跳过头节点
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n"); // 列表结束
}

// 主函数
int main() {
    LinkList L = NULL;

    if (InitList(&L)) { // 传递指针的地址给 InitList
        if (Insert(L)) { // 仅传递 L 给 Insert
            printf("插入成功。\n");
            DisplayList(L); // 显示链表
        }
    }
    else {
        printf("初始化链表失败。\n");
    }

    // 释放分配的内存（可以改善为单独的函数）
    LNode* current = L;
    LNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}