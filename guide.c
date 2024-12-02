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
    strcpy(map->landmarks[0].name, "图书馆");
    strcpy(map->landmarks[0].code, "A");
    strcpy(map->landmarks[0].introdution, "学校学习资源中心，提供安静的学习环境，藏书资源丰富。");

    strcpy(map->landmarks[1].name, "恒大教学楼");
    strcpy(map->landmarks[1].code, "B");
    strcpy(map->landmarks[1].introdution, "学校教学场所，包含实验室、大阶梯教室等。");

    strcpy(map->landmarks[2].name, "英东体育馆");
    strcpy(map->landmarks[2].code, "C");
    strcpy(map->landmarks[2].introdution, "学校锻炼场所，提供室内篮球场。");

    strcpy(map->landmarks[3].name, "餐厅");
    strcpy(map->landmarks[3].code, "D");
    strcpy(map->landmarks[3].introdution, "学生用餐地点，提供多种菜肴和休闲区域。");

    strcpy(map->landmarks[4].name, "T3宿舍楼");
    strcpy(map->landmarks[4].code, "E");
    strcpy(map->landmarks[4].introdution, "学生住宿区域，提供舒适的居住环境。");

    for (int i = 0; i < MAX_LAND_NUM; i++) {
        for (int j = 0; j < MAX_LAND_NUM; j++) {
            if (i == j) {
                map->graph[i][j] = 0; // 自己到自己的距离为0
            }
            else {
                map->graph[i][j] = INF;
            }
        }
    }
    // 定义不同景点之间的路径长度
    map->graph[0][1] = 5;  // 图书馆到教学楼
    map->graph[1][0] = 5;

    map->graph[1][2] = 10; // 教学楼到体育馆
    map->graph[2][1] = 10;

    map->graph[0][4] = 3;  // 图书馆到T3宿舍楼
    map->graph[4][0] = 3;

    map->graph[1][3] = 5;  // 教学楼到餐厅
    map->graph[3][1] = 5;

    map->graph[4][3] = 20; // 宿舍到餐厅
    map->graph[3][4] = 20;
}

void Floyd(CampusMap* map, int dist[MAX_LAND_NUM][MAX_LAND_NUM], int path[MAX_LAND_NUM][MAX_LAND_NUM]) {
    // 初始化dist和path数组
    for (int i = 0; i < MAX_LAND_NUM; i++) {
        for (int j = 0; j < MAX_LAND_NUM; j++) {
            dist[i][j] = map->graph[i][j];
            if (i != j && map->graph[i][j] < INF) {
                path[i][j] = i;
            }
            else {
                path[i][j] = -1; // 否则没有前驱
            }
        }
    }

    // 应用Floyd-Warshall算法
    for (int k = 0; k < MAX_LAND_NUM; k++) {
        for (int i = 0; i < MAX_LAND_NUM; i++) {
            for (int j = 0; j < MAX_LAND_NUM; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j]; // 更新前驱节点
                }
            }
        }
    }
}

void AskForDirections(CampusMap* map, int dist[MAX_LAND_NUM][MAX_LAND_NUM], int path[MAX_LAND_NUM][MAX_LAND_NUM]) {
    char startCode, endCode;
    printf("请输入起点代号（A-E）: ");
    scanf(" %c", &startCode);
    printf("请输入终点代号（A-E）: ");
    scanf(" %c", &endCode);

    int start = startCode - 'A';
    int end = endCode - 'A';

    // 查找起点和终点
    if (start >= 0 && start < MAX_LAND_NUM && end >= 0 && end < MAX_LAND_NUM) {
        if (dist[start][end] == INF) {
            printf("从 %s (%c) 到 %s (%c) 没有路径。\n", map->landmarks[start].name, startCode, map->landmarks[end].name, endCode);
        }
        else {
            // 打印路径长度
            printf("从 %s (%c) 到 %s (%c) 的最短路径长度为: %d\n",
                map->landmarks[start].name, startCode, map->landmarks[end].name, endCode, dist[start][end]);

            // 重建并打印路径
            int current = end;
            while (current != start) {
                printf("%s (%s) <- ", map->landmarks[current].name, map->landmarks[current].code);
                current = path[start][current]; // 注意这里的变化，我们使用start作为第一个索引
                if (current == -1) { // 如果没有路径，则退出
                    printf("路径不存在。\n");
                    return;
                }
            }
            printf("%s (%s)\n", map->landmarks[start].name, map->landmarks[start].code); // 打印起点
        }
    }
    else {
        printf("无效的地点代号。\n");
    }
}

int main() {
    CampusMap map;
    InitLandmark(&map);

    int dist[MAX_LAND_NUM][MAX_LAND_NUM];
    int path[MAX_LAND_NUM][MAX_LAND_NUM];

    printf("*****************欢迎来到JNU***********\n");
    printf("学校地图信息：\n");
    for (int i = 0; i < MAX_LAND_NUM; i++) {
        printf("景点:%s, 代号:%s, 简介:%s\n",
            map.landmarks[i].name, map.landmarks[i].code, map.landmarks[i].introdution);
    }
    printf("\n");

    printf("***************************************\n");
    Floyd(&map, dist, path);

    printf("\n");
    printf("请输入起点和终点以查询路径：\n");
    AskForDirections(&map, dist, path);

    return 0;
}