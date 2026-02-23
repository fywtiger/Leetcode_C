/*
 * @lc app=leetcode.cn id=1 lang=c
 *
 * [1] 两数之和
 *
 * https://leetcode-cn.com/problems/two-sum/description/
 *
 * algorithms
 * Easy (48.28%)
 * Likes:    8152
 * Dislikes: 0
 * Total Accepted:    1M
 * Total Submissions: 2.1M
 * Testcase Example:  '[2,7,11,15]\n9'
 *
 * 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
 *
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
 *
 *
 *
 * 示例:
 *
 * 给定 nums = [2, 7, 11, 15], target = 9
 *
 * 因为 nums[0] + nums[1] = 2 + 7 = 9
 * 所以返回 [0, 1]
 *
 *
 */
#include "Mylib.h"
// @lc code=start

typedef struct {
    int val;
    int site;
} RNUMS;

int compareRNUMS(const void *a, const void *b) {
    RNUMS *A = (RNUMS *)a;
    RNUMS *B = (RNUMS *)b;
    return A->val - B->val;
}
int GetNextEndSite(RNUMS *nums, int start, int end) {
    for (int i = end - 1; i > start; i--) {
        if (nums[i].val != nums[end].val) {
            return i;
        }
    }
    return start;
}
int GetNextStartSite(RNUMS *nums, int start, int end) {
    for (int i = start + 1; i < end; i++) {
        if (nums[i].val != nums[start].val) {
            return i;
        }
    }
    return end;
}
int *MakeTwoSumRetArray(RNUMS *nums, int start, int end, int target) {
    int *retArray = NULL;
    if (start >= end) {
        return retArray;
    }
    if (nums[start].val + nums[end].val == target) {
        retArray = malloc(sizeof(int) * 2);
        retArray[0] = nums[start].site;
        retArray[1] = nums[end].site;
        return retArray;
    }

    if (nums[start].val + nums[end].val > target) {
        end = GetNextEndSite(nums, start, end);
        retArray = MakeTwoSumRetArray(nums, start, end, target);
        return retArray;
    }

    if (nums[start].val + nums[end].val < target) {
        start = GetNextStartSite(nums, start, end);
        retArray = MakeTwoSumRetArray(nums, start, end, target);
        return retArray;
    }
    return retArray;
}
RNUMS *InitTwoSumNums(int *nums, int numsSize) {
    RNUMS *rNums = malloc(sizeof(RNUMS) * numsSize);
    if (rNums == NULL) {
        return NULL;
    }
    for (int i = 0; i < numsSize; i++) {
        rNums[i].site = i;
        rNums[i].val = nums[i];
    }
    return rNums;
}
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    RNUMS *rNums = InitTwoSumNums(nums, numsSize);
    if (rNums == NULL) {
        *returnSize = 0;
        return NULL;
    }
    qsort(rNums, numsSize, sizeof(RNUMS), compareRNUMS);
    int *retArray = MakeTwoSumRetArray(rNums, 0, numsSize - 1, target);
    *returnSize = retArray == NULL ? 0 : 2;
    free(rNums);
    return retArray;
}

// @lc code=end
