/*带头结点的单链表*/
#include<stdio.h>
#include<stdlib.h>
#define bool int
#define true 1
#define false 0

typedef struct LNode {
	int data;
	struct LNode* next;
}LNode, * LinkList;//强调这是一个单链表LinkList,强调这是一个结点LNode*

bool InitList(LinkList L) {
	L = (LNode*)malloc(sizeof(LNode));
	if (L == NULL) {
		return false;
	}
	L->next = NULL;
	return true;
}
int main() {
	LinkList L;
	InitList(L);

}