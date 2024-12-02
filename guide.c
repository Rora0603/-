#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LAND_NUM 5
#define INF INT_MAX

typedef struct {
    char name[100];
    char code[100];
    char introdution[100];
} Landmark;

typedef struct {
    Landmark landmarks[MAX_LAND_NUM];
    int graph[MAX_LAND_NUM][MAX_LAND_NUM];
} CampusMap;

void InitLandmark(CampusMap* map) {
    strcpy(map->landmarks[0].name, "ͼ���");
    strcpy(map->landmarks[0].code, "A");
    strcpy(map->landmarks[0].introdution, "ѧУѧϰ��Դ���ģ��ṩ������ѧϰ������������Դ�ḻ��");

    strcpy(map->landmarks[1].name, "����ѧ¥");
    strcpy(map->landmarks[1].code, "B");
    strcpy(map->landmarks[1].introdution, "ѧУ��ѧ����������ʵ���ҡ�����ݽ��ҵȡ�");

    strcpy(map->landmarks[2].name, "Ӣ��������");
    strcpy(map->landmarks[2].code, "C");
    strcpy(map->landmarks[2].introdution, "ѧУ�����������ṩ�������򳡡�");

    strcpy(map->landmarks[3].name, "����");
    strcpy(map->landmarks[3].code, "D");
    strcpy(map->landmarks[3].introdution, "ѧ���ò͵ص㣬�ṩ���ֲ��Ⱥ���������");

    strcpy(map->landmarks[4].name, "T3����¥");
    strcpy(map->landmarks[4].code, "E");
    strcpy(map->landmarks[4].introdution, "ѧ��ס�������ṩ���ʵľ�ס������");

    for (int i = 0; i < MAX_LAND_NUM; i++) {
        for (int j = 0; j < MAX_LAND_NUM; j++) {
            if (i == j) {
                map->graph[i][j] = 0; // �Լ����Լ��ľ���Ϊ0
            }
            else {
                map->graph[i][j] = INF;
            }
        }
    }
    // ���岻ͬ����֮���·������
    map->graph[0][1] = 5;  // ͼ��ݵ���ѧ¥
    map->graph[1][0] = 5;

    map->graph[1][2] = 10; // ��ѧ¥��������
    map->graph[2][1] = 10;

    map->graph[0][4] = 3;  // ͼ��ݵ�T3����¥
    map->graph[4][0] = 3;

    map->graph[1][3] = 5;  // ��ѧ¥������
    map->graph[3][1] = 5;

    map->graph[4][3] = 20; // ���ᵽ����
    map->graph[3][4] = 20;
}

void Floyd(CampusMap* map, int dist[MAX_LAND_NUM][MAX_LAND_NUM], int path[MAX_LAND_NUM][MAX_LAND_NUM]) {
    // ��ʼ��dist��path����
    for (int i = 0; i < MAX_LAND_NUM; i++) {
        for (int j = 0; j < MAX_LAND_NUM; j++) {
            dist[i][j] = map->graph[i][j];
            if (i != j && map->graph[i][j] < INF) {
                path[i][j] = i;
            }
            else {
                path[i][j] = -1; // ����û��ǰ��
            }
        }
    }

    // Ӧ��Floyd-Warshall�㷨
    for (int k = 0; k < MAX_LAND_NUM; k++) {
        for (int i = 0; i < MAX_LAND_NUM; i++) {
            for (int j = 0; j < MAX_LAND_NUM; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j]; // ����ǰ���ڵ�
                }
            }
        }
    }
}

void AskForDirections(CampusMap* map, int dist[MAX_LAND_NUM][MAX_LAND_NUM], int path[MAX_LAND_NUM][MAX_LAND_NUM]) {
    char startCode, endCode;
    printf("�����������ţ�A-E��: ");
    scanf(" %c", &startCode);
    printf("�������յ���ţ�A-E��: ");
    scanf(" %c", &endCode);

    int start = startCode - 'A';
    int end = endCode - 'A';

    // ���������յ�
    if (start >= 0 && start < MAX_LAND_NUM && end >= 0 && end < MAX_LAND_NUM) {
        if (dist[start][end] == INF) {
            printf("�� %s (%c) �� %s (%c) û��·����\n", map->landmarks[start].name, startCode, map->landmarks[end].name, endCode);
        }
        else {
            // ��ӡ·������
            printf("�� %s (%c) �� %s (%c) �����·������Ϊ: %d\n",
                map->landmarks[start].name, startCode, map->landmarks[end].name, endCode, dist[start][end]);

            // �ؽ�����ӡ·��
            int current = end;
            while (current != start) {
                printf("%s (%s) <- ", map->landmarks[current].name, map->landmarks[current].code);
                current = path[start][current]; // ע������ı仯������ʹ��start��Ϊ��һ������
                if (current == -1) { // ���û��·�������˳�
                    printf("·�������ڡ�\n");
                    return;
                }
            }
            printf("%s (%s)\n", map->landmarks[start].name, map->landmarks[start].code); // ��ӡ���
        }
    }
    else {
        printf("��Ч�ĵص���š�\n");
    }
}

int main() {
    CampusMap map;
    InitLandmark(&map);

    int dist[MAX_LAND_NUM][MAX_LAND_NUM];
    int path[MAX_LAND_NUM][MAX_LAND_NUM];

    printf("*****************��ӭ����JNU***********\n");
    printf("ѧУ��ͼ��Ϣ��\n");
    for (int i = 0; i < MAX_LAND_NUM; i++) {
        printf("����:%s, ����:%s, ���:%s\n",
            map.landmarks[i].name, map.landmarks[i].code, map.landmarks[i].introdution);
    }
    printf("\n");

    printf("***************************************\n");
    Floyd(&map, dist, path);

    printf("\n");
    printf("�����������յ��Բ�ѯ·����\n");
    AskForDirections(&map, dist, path);

    return 0;
}