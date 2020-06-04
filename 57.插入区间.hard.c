/*
 * @lc app=leetcode.cn id=57 lang=c
 *
 * [57] 插入区间
 *
 * https://leetcode-cn.com/problems/insert-interval/description/
 *
 * algorithms
 * Hard (37.23%)
 * Likes:    133
 * Dislikes: 0
 * Total Accepted:    21.1K
 * Total Submissions: 56.6K
 * Testcase Example:  '[[1,3],[6,9]]\n[2,5]'
 *
 * 给出一个无重叠的 ，按照区间起始端点排序的区间列表。
 *
 * 在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。
 *
 * 示例 1:
 *
 * 输入: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * 输出: [[1,5],[6,9]]
 *
 *
 * 示例 2:
 *
 * 输入: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * 输出: [[1,2],[3,10],[12,16]]
 * 解释: 这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。
 *
 *
 */
#include "Mylib.h"
// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int GetInsertSite(int **intervals, int searchStatr, int searchEnd, int insertVal);
void printArray(int **array, int size);
int fillReturnVals(int **returnVals, int returnValSite, int **intervals, int strartSite,
                   int endSite);
int insertNewValsToReturnVals(int **returnVals, int returnValSite, int **intervals,
                              int intervalsSize, int *newInterval, int leftInsertSite,
                              int rightInsertSite);
int **insert(int **intervals, int intervalsSize, int *intervalsColSize, int *newInterval,
             int newIntervalSize, int *returnSize, int **returnColumnSizes) {
    int **returnVals = NULL;
    returnVals = malloc(sizeof(int *) * (intervalsSize + 1));
    int i;
    if (newIntervalSize == 0) {
        *returnSize = intervalsSize;
        *returnColumnSizes = malloc(sizeof(int) * intervalsSize);
        for (i = 0; i < intervalsSize; i++) {
            (*returnColumnSizes)[i] = intervalsColSize[i];
            returnVals[i] = malloc(sizeof(int) * intervalsColSize[i]);
            returnVals[i][0] = intervals[i][0];
            returnVals[i][1] = intervals[i][1];
        }
        return returnVals;
    }
    if (intervalsSize == 0) {
        *returnSize = 1;
        *returnColumnSizes = malloc(sizeof(int));
        (*returnColumnSizes)[0] = newIntervalSize;
        returnVals[0] = malloc(sizeof(int) * newIntervalSize);
        returnVals[0][0] = newInterval[0];
        returnVals[0][1] = newInterval[1];
        return returnVals;
    }

    for (i = 0; i <= intervalsSize; i++) {
        returnVals[i] = malloc(sizeof(int) * intervalsColSize[0]);
    }
    int leftInsertSite = GetInsertSite(intervals, 0, intervalsSize, newInterval[0]);
    int rightInsertSite =
        GetInsertSite(intervals, leftInsertSite / 2, intervalsSize, newInterval[1]);
    int returnValSite = fillReturnVals(returnVals, 0, intervals, 0, leftInsertSite / 2);
    int intervalSite =
        insertNewValsToReturnVals(returnVals, returnValSite, intervals, intervalsSize, newInterval,
                                  leftInsertSite, rightInsertSite);
    returnValSite =
        fillReturnVals(returnVals, returnValSite + 1, intervals, intervalSite, intervalsSize);
    *returnSize = returnValSite;
    *returnColumnSizes = malloc(sizeof(int) * returnValSite);
    for (i = 0; i < returnValSite; i++) {
        (*returnColumnSizes)[i] = intervalsColSize[0];
    }
    return returnVals;
}
int GetInsertSite(int **intervals, int searchStatr, int searchEnd, int insertVal) {
    int insertSite;
    insertSite = 2 * searchEnd;
    for (int i = searchStatr; i < searchEnd; i++) {
        if (insertVal <= intervals[i][0]) {
            insertSite = 2 * i;
            return insertSite;
        }
        if (insertVal <= intervals[i][1]) {
            insertSite = 2 * i + 1;
            return insertSite;
        }
    }
    return insertSite;
}

int fillReturnVals(int **returnVals, int returnValSite, int **intervals, int strartSite,
                   int endSite) {
    int site = returnValSite;
    for (int i = strartSite; i < endSite; i++) {
        returnVals[site][0] = intervals[i][0];
        returnVals[site][1] = intervals[i][1];
        site++;
    }
    return site;
}

int insertNewValsToReturnVals(int **returnVals, int returnValSite, int **intervals,
                              int intervalsSize, int *newInterval, int leftInsertSite,
                              int rightInsertSite) {
    if (leftInsertSite % 2 == 0) {
        returnVals[returnValSite][0] = newInterval[0];
    } else {
        returnVals[returnValSite][0] = intervals[leftInsertSite / 2][0];
    }
    if (rightInsertSite == 2 * intervalsSize) {
        returnVals[returnValSite][1] = newInterval[1];
        return intervalsSize;
    }
    if (rightInsertSite % 2 == 0) {
        if (newInterval[1] < intervals[rightInsertSite / 2][0]) {
            returnVals[returnValSite][1] = newInterval[1];
            return rightInsertSite / 2;
        } else {
            returnVals[returnValSite][1] = intervals[rightInsertSite / 2][1];
            return (rightInsertSite / 2 + 1);
        }
    } else {
        returnVals[returnValSite][1] = intervals[rightInsertSite / 2][1];
        return (rightInsertSite / 2 + 1);
    }
}
void printArray(int **array, int size) {
    printf("array:");
    for (int i = 0; i < size; i++) {
        printf("[%d %d] ", array[i][0], array[i][1]);
    }
    printf("\n");
}

// @lc code=end
