/*
 * @lc app=leetcode.cn id=18 lang=c
 *
 * [18] 四数之和
 *
 * https://leetcode-cn.com/problems/4sum/description/
 *
 * algorithms
 * Medium (37.60%)
 * Likes:    490
 * Dislikes: 0
 * Total Accepted:    83.7K
 * Total Submissions: 221.9K
 * Testcase Example:  '[1,0,-1,0,-2,2]\n0'
 *
 * 给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c
 * + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
 *
 * 注意：
 *
 * 答案中不可以包含重复的四元组。
 *
 * 示例：
 *
 * 给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。
 *
 * 满足要求的四元组集合为：
 * [
 * ⁠ [-1,  0, 0, 1],
 * ⁠ [-2, -1, 1, 2],
 * ⁠ [-2,  0, 0, 2]
 * ]
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
#define SUMRETNUMLEN 4
struct sumListNode {
    int nums[SUMRETNUMLEN];
    struct sumListNode *next;
};
typedef struct sumListNode SLISTNODE;
typedef struct {
    int num;
    int nums[SUMRETNUMLEN];
    SLISTNODE *head;
    SLISTNODE *trail;
} SLISTHEAD;
void InsertSum4ListNode(SLISTHEAD *head, SLISTNODE *node) {
    head->num++;
    if (head->head == NULL) {
        head->head = node;
        head->trail = node;
    } else {
        head->trail->next = node;
        head->trail = node;
    }
    return;
}
int **InitFourSumRetNums(SLISTHEAD *head) {
    int numsSize = head->num;
    SLISTNODE *node = head->head;
    int **retNums = malloc(sizeof(int *) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        retNums[i] = malloc(sizeof(int) * SUMRETNUMLEN);
        memcpy(retNums[i], node->nums, sizeof(int) * SUMRETNUMLEN);
        node = node->next;
    }
    return retNums;
}
int CompaerIntFourSum(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}
int FindNextMaxSite4(int start, int end, int *nums) {
    for (int i = end - 1; i > start; i--) {
        if (nums[i] != nums[end]) {
            return i;
        }
    }
    return -1;
}
int FindNextMinSite4(int start, int end, int *nums) {
    for (int i = start + 1; i < end; i++) {
        if (nums[i] != nums[start]) {
            return i;
        }
    }
    return end + 1;
}
SLISTNODE *InitFourSumRetNode(SLISTHEAD *head) {
    SLISTNODE *node = malloc(sizeof(SLISTNODE));
    node->next = NULL;
    memcpy(node->nums, head->nums, sizeof(int) * SUMRETNUMLEN);
    return node;
}
void CalThreeSumRetNumsPlus(int *nums, int start, int end, int sum, SLISTHEAD *head) {
    if (start >= end) {
        return;
    }
    if (nums[start] + nums[end] + sum == 0) {
        head->nums[2] = nums[start];
        head->nums[3] = nums[end];
        SLISTNODE *node = InitFourSumRetNode(head);
        InsertSum4ListNode(head, node);
        start = FindNextMinSite4(start, end, nums);
        end = FindNextMaxSite4(start, end, nums);
        CalThreeSumRetNumsPlus(nums, start, end, sum, head);
        return;
    }
    if (nums[start] + nums[end] + sum > 0) {
        end = FindNextMaxSite4(start, end, nums);
        CalThreeSumRetNumsPlus(nums, start, end, sum, head);
        return;
    }
    if (nums[start] + nums[end] + sum < 0) {
        start = FindNextMinSite4(start, end, nums);
        CalThreeSumRetNumsPlus(nums, start, end, sum, head);
        return;
    }
}
SLISTHEAD *InitFourSumRetHead() {
    SLISTHEAD *head = malloc(sizeof(SLISTHEAD));
    head->num = 0;
    head->head = NULL;
    head->trail = NULL;
    return head;
}
void CalFourSumRetNums(int *nums, int start, int end, int target, SLISTHEAD *head) {
    head->nums[1] = nums[start] - 1;
    for (int i = start + 1; i < end; i++) {
        if (head->nums[1] < nums[i]) {
            head->nums[1] = nums[i];
            CalThreeSumRetNumsPlus(nums, i + 1, end - 1, head->nums[1] + target, head);
        }
    }
    return;
}
SLISTHEAD *MakeFourSumRetNums(int *nums, int numsSize, int target) {
    SLISTHEAD *head = InitFourSumRetHead();
    if (numsSize == 0) {
        return head;
    }
    head->nums[0] = nums[0] - 1;
    for (int j = 0; j < numsSize; j++) {
        if (head->nums[0] < nums[j]) {
            head->nums[0] = nums[j];
            CalFourSumRetNums(nums, j, numsSize, head->nums[0] - target, head);
        }
    }
    return head;
}
int MakeRetFourSumSize(int ColumnSizes, int **returnColumnSizes) {
    *returnColumnSizes = malloc(sizeof(int) * ColumnSizes);
    for (int i = 0; i < ColumnSizes; i++) {
        (*returnColumnSizes)[i] = SUMRETNUMLEN;
    }
    return ColumnSizes;
}
void FreeFourSumMemory(SLISTHEAD *head) {
    SLISTNODE *node = head->head;
    SLISTNODE *pre = head->head;
    while (node != NULL) {
        pre = node;
        node = node->next;
        free(pre);
    }
    free(head);
    return;
}

int **fourSum(int *nums, int numsSize, int target, int *returnSize, int **returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), CompaerIntFourSum);
    SLISTHEAD *head = MakeFourSumRetNums(nums, numsSize, target);
    int **retNums = InitFourSumRetNums(head);
    *returnSize = MakeRetFourSumSize(head->num, returnColumnSizes);
    FreeFourSumMemory(head);
    return retNums;
}

// @lc code=end
