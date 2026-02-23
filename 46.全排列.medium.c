/*
 * @lc app=leetcode.cn id=46 lang=c
 *
 * [46] 全排列
 *
 * https://leetcode-cn.com/problems/permutations/description/
 *
 * algorithms
 * Medium (75.97%)
 * Likes:    686
 * Dislikes: 0
 * Total Accepted:    122.6K
 * Total Submissions: 161.4K
 * Testcase Example:  '[1,2,3]'
 *
 * 给定一个 没有重复 数字的序列，返回其所有可能的全排列。
 *
 * 示例:
 *
 * 输入: [1,2,3]
 * 输出:
 * [
 * ⁠ [1,2,3],
 * ⁠ [1,3,2],
 * ⁠ [2,1,3],
 * ⁠ [2,3,1],
 * ⁠ [3,1,2],
 * ⁠ [3,2,1]
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
int **InitRetArray(int size, int numsSize, int *returnSize, int **returnColumnSizes) {
    int **retArray = malloc(sizeof(int *) * size);
    if (retArray == NULL) {
        return NULL;
    }
    *returnColumnSizes = malloc(sizeof(int) * size);
    if (*returnColumnSizes == NULL) {
        free(retArray);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        (*returnColumnSizes)[i] = numsSize;
        retArray[i] = malloc(sizeof(int) * numsSize);
        if (retArray[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(retArray[j]);
            }
            free(retArray);
            free(*returnColumnSizes);
            return NULL;
        }
    }
    *returnSize = size;
    return retArray;
}
int CalRetSize(int numsSize) {
    int size = 1;
    for (int i = 1; i <= numsSize; i++) {
        size = size * i;
    }
    return size;
}
void SwapNumber(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
void MakePermuteArray(int *nums, int numsSize, int site, int **retArray, int *rSize) {
    if (site == numsSize - 1) {
        memcpy(retArray[*rSize], nums, sizeof(int) * numsSize);
        *rSize = *rSize + 1;
        return;
    }
    for (int i = site; i < numsSize; i++) {
        SwapNumber(&nums[site],&nums[i]);
        MakePermuteArray(nums, numsSize, site + 1, retArray, rSize);
        SwapNumber(&nums[site],&nums[i]);
    }
    return;
}
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    int size = CalRetSize(numsSize);
    int **retArray = InitRetArray(size, numsSize, returnSize, returnColumnSizes);
    if (retArray == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int rSize = 0;
    MakePermuteArray(nums, numsSize, 0, retArray, &rSize);
    return retArray;
}

// @lc code=end
