/*
 * @lc app=leetcode.cn id=47 lang=c
 *
 * [47] 全排列 II
 *
 * https://leetcode-cn.com/problems/permutations-ii/description/
 *
 * algorithms
 * Medium (58.70%)
 * Likes:    300
 * Dislikes: 0
 * Total Accepted:    60.9K
 * Total Submissions: 103.6K
 * Testcase Example:  '[1,1,2]'
 *
 * 给定一个可包含重复数字的序列，返回所有不重复的全排列。
 *
 * 示例:
 *
 * 输入: [1,1,2]
 * 输出:
 * [
 * ⁠ [1,1,2],
 * ⁠ [1,2,1],
 * ⁠ [2,1,1]
 * ]
 *
 */
#include "Mylib.h"
// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **InitRetArray2(int size, int **returnColumnSizes) {
    int **retArray = malloc(sizeof(int *) * size);
    if (retArray == NULL) {
        return NULL;
    }
    *returnColumnSizes = malloc(sizeof(int) * size);
    if (*returnColumnSizes == NULL) {
        free(retArray);
        return NULL;
    }
    return retArray;
}
int CalRetSize2(int numsSize) {
    int size = 1;
    for (int i = 1; i <= numsSize; i++) {
        size = size * i;
    }
    return size;
}
void MakePermuteArray2(int *nums, int numsSize, int site, int **retArray, int *rSize, int **returnColumnSizes,
                       int *tNums, int *visit) {
    if (site == numsSize) {
        (*returnColumnSizes)[*rSize] = numsSize;
        retArray[*rSize] = malloc(sizeof(int) * numsSize);
        if (retArray[*rSize] != NULL) {
            memcpy(retArray[*rSize], tNums, sizeof(int) * numsSize);
            *rSize = *rSize + 1;
        }
        return;
    }
    int val = nums[0] - 1;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > val && visit[i] == 0) {
            val = nums[i];
            tNums[site] = nums[i];
            visit[i] = 1;
            MakePermuteArray2(nums, numsSize, site + 1, retArray, rSize, returnColumnSizes, tNums, visit);
            visit[i] = 0;
        }
    }
    return;
}
int ComparePermute(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}
int **permuteUnique(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    int size = CalRetSize2(numsSize);
    int **retArray = InitRetArray2(size, returnColumnSizes);
    if (retArray == NULL) {
        *returnSize = 0;
        return NULL;
    }
    qsort(nums, numsSize, sizeof(int), ComparePermute);
    int rSize = 0;
    int *tNums = malloc(sizeof(int) * numsSize);
    if (tNums == NULL) {
        free(retArray);
        free(*returnColumnSizes);
        *returnSize = 0;
        return NULL;
    }
    int *visit = calloc(numsSize, sizeof(int));
    if (visit == NULL) {
        free(tNums);
        free(retArray);
        free(*returnColumnSizes);
        *returnSize = 0;
        return NULL;
    }
    MakePermuteArray2(nums, numsSize, 0, retArray, &rSize, returnColumnSizes, tNums, visit);
    free(tNums);
    free(visit);
    *returnSize = rSize;
    return retArray;
}
// @lc code=end
