/*
 * @lc app=leetcode.cn id=15 lang=c
 *
 * [15] 三数之和
 *
 * https://leetcode-cn.com/problems/3sum/description/
 *
 * algorithms
 * Medium (27.02%)
 * Likes:    2168
 * Dislikes: 0
 * Total Accepted:    230.8K
 * Total Submissions: 848K
 * Testcase Example:  '[-1,0,1,2,-1,-4]'
 *
 * 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0
 * ？请你找出所有满足条件且不重复的三元组。
 *
 * 注意：答案中不可以包含重复的三元组。
 *
 *
 *
 * 示例：
 *
 * 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
 *
 * 满足要求的三元组集合为：
 * [
 * ⁠ [-1, 0, 1],
 * ⁠ [-1, -1, 2]
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
#define SUMRETNUMLEN 3
struct sumListNode {
    int nums[SUMRETNUMLEN];
    struct sumListNode *next;
};
typedef struct sumListNode SLISTNODE;
typedef struct {
    int num;
    SLISTNODE *head;
    SLISTNODE *trail;
} SLISTHEAD;
void InsertSumListNode(SLISTHEAD *head, SLISTNODE *node) {
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
int **InitThreeSumRetNums(SLISTHEAD *head) {
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
int CompaerIntThreeSum(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}
int FindNextMaxSite(int start, int end, int *nums, int val) {
    for (int i = end - 1; i > start; i--) {
        if (nums[i] != val) {
            return i;
        }
    }
    return -1;
}
int FindNextMinSite(int start, int end, int *nums, int val) {
    for (int i = start + 1; i < end; i++) {
        if (nums[i] != val) {
            return i;
        }
    }
    return end + 1;
}
SLISTNODE *InitThreeSumRetNode(int num0, int num1, int num2) {
    SLISTNODE *node = malloc(sizeof(SLISTNODE));
    node->next = NULL;
    node->nums[0] = num0;
    node->nums[1] = num1;
    node->nums[2] = num2;
    return node;
}
void CalthreeSumRetNums(int *nums, int start, int end, int sum, SLISTHEAD *head) {
    if (start >= end) {
        return;
    }
    if (nums[start] + nums[end] + sum == 0) {
        SLISTNODE *node = InitThreeSumRetNode(sum, nums[start], nums[end]);
        InsertSumListNode(head, node);
        start = FindNextMinSite(start, end, nums, nums[start]);
        end = FindNextMaxSite(start, end, nums, nums[end]);
        CalthreeSumRetNums(nums, start, end, sum, head);
        return;
    }
    if (nums[start] + nums[end] + sum > 0) {
        end = FindNextMaxSite(start, end, nums, nums[end]);
        CalthreeSumRetNums(nums, start, end, sum, head);
        return;
    }
    if (nums[start] + nums[end] + sum < 0) {
        start = FindNextMinSite(start, end, nums, nums[start]);
        CalthreeSumRetNums(nums, start, end, sum, head);
        return;
    }
}
SLISTHEAD *InitThreeSumRetHead() {
    SLISTHEAD *head = malloc(sizeof(SLISTHEAD));
    head->num = 0;
    head->head = NULL;
    head->trail = NULL;
    return head;
}
SLISTHEAD *MakethreeSumRetNums(int *nums, int numsSize) {
    SLISTHEAD *head = InitThreeSumRetHead();
    if (numsSize == 0) {
        return head;
    }
    int val = nums[0] - 1;
    for (int i = 0; i < numsSize; i++) {
        if (val < nums[i]) {
            val = nums[i];
            CalthreeSumRetNums(nums, i + 1, numsSize - 1, val, head);
        }
    }
    return head;
}
int MakeRetSumSize(int ColumnSizes, int **returnColumnSizes) {
    *returnColumnSizes = malloc(sizeof(int) * ColumnSizes);
    for (int i = 0; i < ColumnSizes; i++) {
        (*returnColumnSizes)[i] = SUMRETNUMLEN;
    }
    return ColumnSizes;
}
void FreeThreeSumMemory(SLISTHEAD *head) {
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
int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), CompaerIntThreeSum);
    SLISTHEAD *head = MakethreeSumRetNums(nums, numsSize);
    int **retNums = InitThreeSumRetNums(head);
    *returnSize = MakeRetSumSize(head->num, returnColumnSizes);
    FreeThreeSumMemory(head);
    return retNums;
}
// @lc code=end
