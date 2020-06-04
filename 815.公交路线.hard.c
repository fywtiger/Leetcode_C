/*
 * @lc app=leetcode.cn id=815 lang=c
 *
 * [815] 公交路线
 *
 * https://leetcode-cn.com/problems/bus-routes/description/
 *
 * algorithms
 * Hard (30.50%)
 * Likes:    39
 * Dislikes: 0
 * Total Accepted:    2.7K
 * Total Submissions: 9K
 * Testcase Example:  '[[1,2,7],[3,6,7]]\n1\n6'
 *
 * 我们有一系列公交路线。每一条路线
 * routes[i] 上都有一辆公交车在上面循环行驶。例如，有一条路线 routes[0] = [1, 5,
 * 7]，表示第一辆 (下标为0)
 * 公交车会一直按照 1->5->7->1->5->7->1->... 的车站路线行驶。
 *
 * 假设我们从 S 车站开始（初始时不在公交车上），要去往 T 站。
 * 期间仅可乘坐公交车，求出最少乘坐的公交车数量。返回 -1
 * 表示不可能到达终点车站。
 *
 *
 * 示例:
 * 输入:
 * routes = [[1, 2, 7], [3, 6, 7]]
 * S = 1
 * T = 6
 * 输出: 2
 * 解释:
 * 最优策略是先乘坐第一辆公交车到达车站 7, 然后换乘第二辆公交车到车站 6。
 *
 *
 * 说明:
 *
 *
 * 1 <= routes.length <= 500.
 * 1 <= routes[i].length <= 500.
 * 0 <= routes[i][j] < 10 ^ 6.
 *
 *
 */
#include "Mylib.h"
// @lc code=start

struct busMapNode {
    int ikey; /* key */
    int val;
    UT_hash_handle hh; /* makes this structure hashable */
};
static struct busMapNode *busState = NULL;
void AddNodeToMap(int mykey, int val);
int FindNodeFromMap(int mykey);
void DeleteAllFromMap();
int **InitBusStateMap(int routesSize, int **array, int aLen);
int **InitBusArray(int **routes, int routesSize, int *routesColSize, int *stack,
                   int *sLen, int *tEnd, int *tLen, int S, int T, int *maxLen,
                   int *busStateNum);
int GetBusStep(int **busSmap, int routesSize, int *stack, int sLen, int *tEnd,
               int tLen);
int FindBusState(int *stack, int sLen, int *tEnd, int tLen);
int UpdateBusStack(int **busSmap, int routesSize, int *stack, int sLen);
void PrintBusMap(int **busSmap, int routesSize);
void PrintStack(int *stack, int sLen);
int numBusesToDestination(int **routes, int routesSize, int *routesColSize,
                          int S, int T) {
    int stack[500], sLen = 0;
    int tEnd[500], tLen = 0, maxLen = 0, busStateNum = 0;
    if (S == T)
        return 0;
    int **array = InitBusArray(routes, routesSize, routesColSize, stack, &sLen,
                               tEnd, &tLen, S, T, &maxLen, &busStateNum);
    int **busSmap = InitBusStateMap(routesSize, array, busStateNum);
    PrintStack(stack, sLen);
    PrintBusMap(busSmap, routesSize);
    int ret = GetBusStep(busSmap, routesSize, stack, sLen, tEnd, tLen);
    DeleteAllFromMap();
    return ret;
}
void PrintStack(int *stack, int sLen) {
    printf("stack[%d]:", sLen);
    for (int i = 0; i < sLen; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}
void PrintBusMap(int **busSmap, int routesSize) {
    for (int i = 0; i < routesSize; i++) {
        printf("line%d: ", i);
        for (int j = 0; j < routesSize; j++) {
            printf("%d ", busSmap[i][j]);
        }
        printf("\n");
    }
}
int GetBusStep(int **busSmap, int routesSize, int *stack, int sLen, int *tEnd,
               int tLen) {
    int ret = 0;
    int len = sLen;
    while (len != 0) {
        ret++;
        if (FindBusState(stack, len, tEnd, tLen)) {
            return ret;
        } else {
            len = UpdateBusStack(busSmap, routesSize, stack, len);
        }
    }
    return -1;
}
int UpdateBusStack(int **busSmap, int routesSize, int *stack, int sLen) {
    int len = 0;
    int *nStack = malloc(sizeof(int) * routesSize);
    int *site = malloc(sizeof(int) * routesSize);
    memset(site, 0, sizeof(int) * routesSize);
    int i, j;
    for (i = 0; i < sLen; i++) {
        for (j = 0; j < routesSize; j++) {
            if (busSmap[stack[i]][j] == 1 && site[j] == 0) {
                nStack[len++] = j;
                busSmap[stack[i]][j] = 0;
                site[j] = 1;
            }
        }
    }
    memcpy(stack, nStack, sizeof(int) * len);
    free(nStack);
    free(site);
    return len;
}
int FindBusState(int *stack, int sLen, int *tEnd, int tLen) {
    for (int i = 0; i < sLen; i++) {
        for (int j = 0; j < tLen; j++) {
            if (stack[i] == tEnd[j]) {
                return 1;
            }
        }
    }
    return 0;
}
void AddNodeToMap(int mykey, int val) {
    struct busMapNode *s;
    s = (struct busMapNode *)malloc(sizeof(struct busMapNode));
    s->ikey = mykey;
    s->val = val;
    HASH_ADD_INT(busState, ikey, s); /* ikey: name of key field */
    return;
}
int FindNodeFromMap(int mykey) {
    struct busMapNode *s;
    HASH_FIND_INT(busState, &mykey, s); /* mykey already in the hash? */
    if (s == NULL) {
        return -1;
    }
    return s->val;
}
void DeleteAllFromMap() {
    struct busMapNode *current_user, *tmp;

    HASH_ITER(hh, busState, current_user, tmp) {
        HASH_DEL(busState,
                 current_user); /* delete it (users advances to next) */
        free(current_user);     /* free it */
    }
}
void printUsers() {
    struct busMapNode *s;
    for (s = busState; s != NULL; s = (struct busMapNode *)(s->hh.next)) {
        printf("user ikey %d: value %d\n", s->ikey, s->val);
    }
}

int **InitBusStateMap(int routesSize, int **array, int aLen) {
    // struct busMapNode *s;
    int len;
    int state[500];
    int **busSmap = NULL;
    busSmap = malloc(sizeof(int *) * routesSize);
    for (int i = 0; i < routesSize; i++) {
        busSmap[i] = malloc(sizeof(int) * routesSize);
        memset(busSmap[i], 0, sizeof(int) * routesSize);
    }
    for (int site = 0; site < aLen; site++) {
        len = 0;
        for (int i = 0; i < routesSize; i++) {
            if (array[site][i] != 0) {
                state[len++] = i;
            }
        }
        for (int i = 0; i < len - 1; i++) {
            for (int j = i + 1; j < len; j++) {
                busSmap[state[i]][state[j]] = 1;
                busSmap[state[j]][state[i]] = 1;
            }
        }
    }
    return busSmap;
}
int **InitBusArray(int **routes, int routesSize, int *routesColSize, int *stack,
                   int *sLen1, int *tEnd, int *tLen1, int S, int T, int *maxLen,
                   int *StateNum) {
    int site, i, j;
    for (i = 0; i < routesSize; i++) {
        *maxLen = *maxLen + routesColSize[i];
    }
    int **array = NULL;
    array = malloc(sizeof(int *) * (*maxLen));
    for (i = 0; i < *maxLen; i++) {
        array[i] = malloc(sizeof(int) * routesSize);
        memset(array[i], 0, sizeof(int) * routesSize);
    }
    int sLen = 0, tLen = 0, busStateNum = 0;
    for (i = 0; i < routesSize; i++) {
        for (j = 0; j < routesColSize[i]; j++) {
            site = FindNodeFromMap(routes[i][j]);
            if (site == -1) {
                array[busStateNum][i] = 1;
                AddNodeToMap(routes[i][j], busStateNum);
                busStateNum++;
                if (routes[i][j] == S) {
                    stack[sLen++] = i;
                }
                if (routes[i][j] == T) {
                    tEnd[tLen++] = i;
                }
            } else {
                if (array[site][i] == 0 && routes[i][j] == S) {
                    stack[sLen++] = i;
                }
                if (array[site][i] == 0 && routes[i][j] == T) {
                    tEnd[tLen++] = i;
                }
                array[site][i] = 1;
            }
        }
    }
    *sLen1 = sLen;
    *tLen1 = tLen;
    *StateNum = busStateNum;
    return array;
}

// @lc code=end
