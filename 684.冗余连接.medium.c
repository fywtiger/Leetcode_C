/*
 * @lc app=leetcode.cn id=684 lang=c
 *
 * [684] 冗余连接
 *
 * https://leetcode-cn.com/problems/redundant-connection/description/
 *
 * algorithms
 * Medium (58.39%)
 * Likes:    127
 * Dislikes: 0
 * Total Accepted:    14K
 * Total Submissions: 23.6K
 * Testcase Example:  '[[1,2],[1,3],[2,3]]'
 *
 * 在本问题中, 树指的是一个连通且无环的无向图。
 *
 * 输入一个图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N)
 * 的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。
 *
 * 结果图是一个以边组成的二维数组。每一个边的元素是一对[u, v] ，满足 u < v，表示连接顶点u 和v的无向图的边。
 *
 * 返回一条可以删去的边，使得结果图是一个有着N个节点的树。如果有多个答案，则返回二维数组中最后出现的边。答案边 [u, v]
 * 应满足相同的格式 u < v。
 *
 * 示例 1：
 *
 * 输入: [[1,2], [1,3], [2,3]]
 * 输出: [2,3]
 * 解释: 给定的无向图为:
 * ⁠ 1
 * ⁠/ \
 * 2 - 3
 *
 *
 * 示例 2：
 *
 * 输入: [[1,2], [2,3], [3,4], [1,4], [1,5]]
 * 输出: [1,4]
 * 解释: 给定的无向图为:
 * 5 - 1 - 2
 * ⁠   |   |
 * ⁠   4 - 3
 *
 *
 * 注意:
 *
 *
 * 输入的二维数组大小在 3 到 1000。
 * 二维数组中的整数在1到N之间，其中N是输入数组的大小。
 *
 *
 * 更新(2017-09-26):
 * 我们已经重新检查了问题描述及测试用例，明确图是无向 图。对于有向图详见冗余连接II。对于造成任何不便，我们深感歉意。
 *
 */
#include "Mylib.h"
// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define VISITRETURN
bool PointArrive(int *stack, int size, int end) {
    for (int i = 0; i < size; i++) {
        if (stack[i] == end) {
            return true;
        }
    }
    return false;
}
int UpdateTreeStack(int **map, int mSize, int *stack, int sLen, int flag) {
    int nStack[mSize];
    int nSlen = 0;

    for (int i = 0; i < sLen; i++) {
        for (int j = 0; j < mSize; j++) {
            if (map[stack[i]][j] <= flag && map[stack[i]][j] != 0) {
                nStack[nSlen] = j;
                nSlen++;
                map[stack[i]][j] = flag + 1;
                map[j][stack[i]] = flag + 1;
            }
        }
    }
    if (nSlen != 0) {
        memcpy(stack, nStack, sizeof(int) * nSlen);
    }
    return nSlen;
}
int **InitConnectMap(int **edges, int edgesSize) {
    int **map = malloc(sizeof(int *) * edgesSize);
    for (int i = 0; i < edgesSize; i++) {
        map[i] = calloc(edgesSize, sizeof(int));
    }
    for (int i = 0; i < edgesSize; i++) {
        map[edges[i][0] - 1][edges[i][1] - 1] = 1;
        map[edges[i][1] - 1][edges[i][0] - 1] = 1;
    }
    return map;
}
void FreeConnectMap(int **map, int size) {
    for (int i = 0; i < size; i++) {
        free(map[i]);
    }
    free(map);
    return;
}
#ifdef BSFRETURN
bool StartToEndArrive(int **map, int mSize, int start, int end, int flag) {
    int stack[mSize];
    stack[0] = start;
    int sLen = 1;
    map[start][end] = flag + 1;
    map[end][start] = flag + 1;
    while (sLen > 0) {
        if (PointArrive(stack, sLen, end)) {
            return true;
        }
        sLen = UpdateTreeStack(map, mSize, stack, sLen, flag);
    }
    return false;
}
int *GetBsfRedundantRet(int **edges, int edgesSize, int *edgesColSize, int *returnSize, int **map) {
    int *ret = NULL;
    *returnSize = 0;
    for (int i = edgesSize - 1; i >= 0; i--) {
        if (StartToEndArrive(map, edgesSize, edges[i][1] - 1, edges[i][0] - 1, edgesSize - i)) {
            *returnSize = edgesColSize[i];
            ret = edges[i];
            break;
        }
    }
    FreeConnectMap(map, edgesSize);
    return ret;
}
#endif
#ifdef DSFRETURN
bool DfsStartToEndArrive(int **map, int mSize, int site, int end) {
    if (site == end) {
        return true;
    }
    bool ret = false;
    for (int i = 0; i < mSize; i++) {
        if (map[site][i] != 0) {
            map[site][i] = 0;
            map[i][site] = 0;
            ret = ret || DfsStartToEndArrive(map, mSize, i, end);
            map[site][i] = 1;
            map[i][site] = 1;
        }
    }
    return ret;
}
int *GetDsfRedundantRet(int **edges, int edgesSize, int *edgesColSize, int *returnSize, int **map) {
    int *ret = NULL;
    *returnSize = 0;
    for (int i = edgesSize - 1; i >= 0; i--) {
        map[edges[i][0] - 1][edges[i][1] - 1] = 0;
        map[edges[i][1] - 1][edges[i][0] - 1] = 0;
        if (DfsStartToEndArrive(map, edgesSize, edges[i][1] - 1, edges[i][0] - 1)) {
            *returnSize = edgesColSize[i];
            ret = edges[i];
            break;
        }
        map[edges[i][0] - 1][edges[i][1] - 1] = 1;
        map[edges[i][1] - 1][edges[i][0] - 1] = 1;
    }
    FreeConnectMap(map, edgesSize);
    return ret;
}
#endif
#ifdef VISITRETURN
int *InitVisitArray(int edgesSize) {
    int *visit = malloc(sizeof(int) * edgesSize);
    for (int i = 0; i < edgesSize; i++) {
        visit[i] = i;
    }
    return visit;
}
int FindVisitNum(int site, int *visit) {
    if (visit[site] == site) {
        return site;
    }
    return FindVisitNum(visit[site], visit);
}

int *GetVisitRedundantRet(int **edges, int edgesSize, int *edgesColSize, int *returnSize, int *visit) {
    int xVisit, yVisit;
    int *ret = NULL;
    *returnSize = 0;
    for (int i = 0; i < edgesSize; i++) {
        xVisit = FindVisitNum(edges[i][0] - 1, visit);
        yVisit = FindVisitNum(edges[i][1] - 1, visit);
        if (xVisit == yVisit) {
            *returnSize = edgesColSize[i];
            ret = edges[i];
            break;
        }
        visit[xVisit] = yVisit;
        visit[edges[i][0] - 1] = yVisit;
        visit[edges[i][1] - 1] = yVisit;
    }
    free(visit);
    return ret;
}
#endif
int *findRedundantConnection(int **edges, int edgesSize, int *edgesColSize, int *returnSize) {
#ifndef VISITRETURN
    int **map = InitConnectMap(edges, edgesSize);
#endif
#ifdef DSFRETURN
    return GetDsfRedundantRet(edges, edgesSize, edgesColSize, returnSize, map);
#endif
#ifdef BSFRETURN
    return GetBsfRedundantRet(edges, edgesSize, edgesColSize, returnSize, map);
#endif
#ifdef VISITRETURN
    int *visit = InitVisitArray(edgesSize);
    return GetVisitRedundantRet(edges, edgesSize, edgesColSize, returnSize, visit);
#endif
}

// @lc code=end
