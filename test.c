/*不带头结点的单链表*/
#include<stdio.h>
#define bool int
#define true 1
#define false 0

typedef struct LNode {
	int data;
	struct LNode* next;
}LNode,*LinkList;//强调这是一个单链表LinkList,强调这是一个结点LNode*

bool InitList(LinkList* L) {
	L = NULL;
	return true;
}
int main() {
	LinkList L;
	InitList(L);
	
}