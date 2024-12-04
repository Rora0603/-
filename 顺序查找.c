#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int* elem;
	int TableLen;
}SSTable;

int Search_Seq(SSTable ST, int key) {
	ST.elem[0] = key;
	int i;
	for (i = ST.TableLen; ST.elem[i] != key; --i);
	return i;//���ҳɹ������±ꣻ����ʧ�ܷ���0
}

int main() {
	SSTable ST;
	ST.TableLen = 10;
	ST.elem = (int*)malloc((ST.TableLen + 1) * sizeof(int));
	int arr[] = { 8,5,7,6,4,1,5,2,3,10 };
	for (int i = 0; i < ST.TableLen; i++) {
		ST.elem[i + 1] = arr[i];
	}
	int key = 7;
	int index = Search_Seq(ST, 7);
	if (index == 0) {
		printf("δ�ҵ�key=%d���±�", key);
	}
	else {
		printf("key=%d������%d���ҵ�", key,index);
	}
	free(ST.elem);
	return 0;
}