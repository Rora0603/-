#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int* elem;
	int TableLen;
}SSTable;

int Binary_Search(SSTable L, int key) {
	int low = 0; 
	int high = L.TableLen - 1;
	int mid;
	while (low < high) {
		mid = (low + high) / 2;
		if (L.elem[mid] == key) {
			return mid;
		}
		else if (L.elem[mid] > key) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return -1;//查找失败，返回-1
}

int main() {
	SSTable ST;
	ST.TableLen = 10;
	ST.elem = (int*)malloc(sizeof(int) *( ST.TableLen));
	int arr[] = { 1,2,4,5,7,9,11,12,13,18 };
	for (int i = 0; i < ST.TableLen; i++) {
		ST.elem[i] = arr[i];
	}
	int key = 9;
	int index = Binary_Search(ST, 9);
	if (index == -1) {
		printf("没有找到key=%d的下标索引", key);
	}
	else {
		printf("key=%d的下标索引为%d", key, index);
	}
	return 0;
}