#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

typedef struct LNode {
    int data;
    struct LNode* next;
} LNode, * LinkList;

// ��ʼ������
bool InitList(LinkList* L) {
    *L = (LNode*)malloc(sizeof(LNode)); // ʹ��ָ��ָ���ָ�����޸�ԭָ��
    if (*L == NULL) {
        return false; // ����ʧ��
    }
    (*L)->next = NULL; // �� next ָ���ʼ��Ϊ NULL
    return true;
}

// ����ڵ㵽����
bool Insert(LinkList L) {
    LNode* r = L; // ��ͷ�ڵ㿪ʼ
    int x = 0;

    printf("����ֵ��9999 ��������\n");
    while (1) {
        scanf_s("%d", &x); // ʹ�� scanf��ȷ��������
        if (x == 9999) break; // �����ڱ�ֵʱ�˳�ѭ��

        LNode* s = (LNode*)malloc(sizeof(LNode)); // �����½ڵ�
        if (s == NULL) {
            return false; // ��� malloc �Ƿ�ɹ�
        }

        s->data = x; // ���������ݸ�ֵ���½ڵ�
        s->next = NULL; // ��ʼ���½ڵ�� next ָ��
        r->next = s; // ��ǰһ���ڵ����½ڵ�����
        r = s; // ��ǰָ���ƶ����½ڵ�
    }

    return true;
}

// ��ʾ����
void DisplayList(LinkList L) {
    LNode* current = L->next; // ����ͷ�ڵ�
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n"); // �б����
}

// ������
int main() {
    LinkList L = NULL;

    if (InitList(&L)) { // ����ָ��ĵ�ַ�� InitList
        if (Insert(L)) { // ������ L �� Insert
            printf("����ɹ���\n");
            DisplayList(L); // ��ʾ����
        }
    }
    else {
        printf("��ʼ������ʧ�ܡ�\n");
    }

    // �ͷŷ�����ڴ棨���Ը���Ϊ�����ĺ�����
    LNode* current = L;
    LNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}