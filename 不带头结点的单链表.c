/*����ͷ���ĵ�����*/
#include<stdio.h>
#define bool int
#define true 1
#define false 0

typedef struct LNode {
	int data;
	struct LNode* next;
}LNode,*LinkList;//ǿ������һ��������LinkList,ǿ������һ�����LNode*

bool InitList(LinkList* L) {
	L = NULL;
	return true;
}
int main() {
	LinkList L;
	InitList(L);
	
}