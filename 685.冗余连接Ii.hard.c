/*
 * @lc app=leetcode.cn id=685 lang=c
 *
 * [685] 冗余连接 II
 *
 * https://leetcode-cn.com/problems/redundant-connection-ii/description/
 *
 * algorithms
 * Hard (34.29%)
 * Likes:    68
 * Dislikes: 0
 * Total Accepted:    3.3K
 * Total Submissions: 9.4K
 * Testcase Example:  '[[1,2],[1,3],[2,3]]'
 *
 * 在本问题中，有根树指满足以下条件的有向图。该树只有一个根节点，所有其他节点都是该根节点的后继。每一个节点只有一个父节点，除了根节点没有父节点。
 *
 * 输入一个有向图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N)
 * 的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。
 *
 * 结果图是一个以边组成的二维数组。 每一个边 的元素是一对 [u, v]，用以表示有向图中连接顶点 u 和顶点 v 的边，其中 u 是 v
 * 的一个父节点。
 *
 * 返回一条能删除的边，使得剩下的图是有N个节点的有根树。若有多个答案，返回最后出现在给定二维数组的答案。
 *
 * 示例 1:
 *
 * 输入: [[1,2], [1,3], [2,3]]
 * 输出: [2,3]
 * 解释: 给定的有向图如下:
 * ⁠ 1
 * ⁠/ \
 * v   v
 * 2-->3
 *
 *
 * 示例 2:
 *
 * 输入: [[1,2], [2,3], [3,4], [4,1], [1,5]]
 * 输出: [4,1]
 * 解释: 给定的有向图如下:
 * 5 <- 1 -> 2
 * ⁠    ^    |
 * ⁠    |    v
 * ⁠    4 <- 3
 *
 *
 * 注意:
 *
 *
 * 二维数组大小的在3到1000范围内。
 * 二维数组中的每个整数在1到N之间，其中 N 是二维数组的大小。
 *
 *
 */
#include "Mylib.h"
// @lc code=start
int *InitDirectVisitArray(int edgesSize) {
    int *visit = malloc(sizeof(int) * edgesSize);
    if (visit == NULL) {
        return NULL;
    }
    for (int i = 0; i < edgesSize; i++) {
        visit[i] = i;
    }
    return visit;
}
int FindDirectVisitNum(int site, int *visit) {
    if (visit[site] == site) {
        return site;
    }
    return FindDirectVisitNum(visit[site], visit);
}
int *GetDirectVisitRedundantRet(int **edges, int edgesSize, int *edgesColSize, int *returnSize, int *visit) {
    int xVisit, yVisit;
    int *ret = NULL;
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][0] > 0) {
            xVisit = FindDirectVisitNum(edges[i][0] - 1, visit);
            yVisit = FindDirectVisitNum(edges[i][1] - 1, visit);
            if (xVisit == yVisit) {
                *returnSize = edgesColSize[i];
                ret = edges[i];
                break;
            }
            visit[xVisit] = yVisit;
            visit[edges[i][0] - 1] = yVisit;
            visit[edges[i][1] - 1] = yVisit;
        }
    }
    free(visit);
    return ret;
}
int *GetRpFatherPoint(int **edges, int edgesSize, int *edgesColSize) {
    int *fatherPoint = calloc(edgesSize, sizeof(int));
    if (fatherPoint == NULL) {
        return NULL;
    }
    int *ret = NULL;
    for (int i = 0; i < edgesSize; i++) {
        if (fatherPoint[edges[i][1] - 1] != 0 && fatherPoint[edges[i][1] - 1] != edges[i][0]) {
            ret = malloc(sizeof(int) * edgesColSize[i]);
            memcpy(ret, edges[i], sizeof(int) * edgesColSize[i]);
            edges[i][0] = 0;
            return ret;
        }
        fatherPoint[edges[i][1] - 1] = edges[i][0];
    }
    return ret;
}
int *GetRetRpFatherPoint(int **edges, int edgesSize, int point) {
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][1] == point && edges[i][0] > 0) {
            return edges[i];
        }
    }
    return NULL;
}
int *findRedundantDirectedConnection(int **edges, int edgesSize, int *edgesColSize, int *returnSize) {
    int *visit = InitDirectVisitArray(edgesSize);
    if (visit == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int *ret = GetRpFatherPoint(edges, edgesSize, edgesColSize);
    *returnSize = ret == NULL ? 0 : edgesColSize[0];
    int *ret1 = GetDirectVisitRedundantRet(edges, edgesSize, edgesColSize, returnSize, visit);
    if (ret1 == NULL) {
        return ret;
    }
    if (ret == NULL) {
        return ret1;
    }
    int point = ret[1];
    free(ret);
    return GetRetRpFatherPoint(edges, edgesSize, point);
}

// @lc code=end
