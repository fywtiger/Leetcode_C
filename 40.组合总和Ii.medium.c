/*
 * @lc app=leetcode.cn id=40 lang=c
 *
 * [40] 组合总和 II
 *
 * https://leetcode-cn.com/problems/combination-sum-ii/description/
 *
 * algorithms
 * Medium (61.41%)
 * Likes:    254
 * Dislikes: 0
 * Total Accepted:    54.6K
 * Total Submissions: 88.9K
 * Testcase Example:  '[10,1,2,7,6,1,5]\n8'
 *
 * 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 *
 * candidates 中的每个数字在每个组合中只能使用一次。
 *
 * 说明：
 *
 *
 * 所有数字（包括目标数）都是正整数。
 * 解集不能包含重复的组合。 
 *
 *
 * 示例 1:
 *
 * 输入: candidates = [10,1,2,7,6,1,5], target = 8,
 * 所求解集为:
 * [
 * ⁠ [1, 7],
 * ⁠ [1, 2, 5],
 * ⁠ [2, 6],
 * ⁠ [1, 1, 6]
 * ]
 *
 *
 * 示例 2:
 *
 * 输入: candidates = [2,5,2,1,2], target = 5,
 * 所求解集为:
 * [
 * [1,2,2],
 * [5]
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
struct numNode {
    int *rNode;
    int rLen;
    struct numNode *trail;
    struct numNode *next;
};
typedef struct numNode NUMNODE;
int GetAllArray2(int *candidates, int candidatesSize, int site, int *vSite, int vLen, int target,
                 NUMNODE *head) {
    if (target < 0 || site < -1) {
        return 0;
    }
    if (target == 0) {
        NUMNODE *node = malloc(sizeof(NUMNODE));
        node->rNode = malloc(sizeof(int) * vLen);
        node->rLen = vLen;
        node->next = NULL;
        for (int i = candidatesSize - 1, j = 0; i >= 0; i--) {
            if (vSite[i]) {
                node->rNode[j++] = candidates[i];
            }
        }
        NUMNODE *trail = head->trail;
        trail->next = node;
        head->trail = node;
        return 1;
    }
    int sum = 0;
    int sVal = -1;
    for (int i = site; i >= 0; i--) {
        if (candidates[i] > sVal) {
            sVal = candidates[i];
            target = target - candidates[i];
            vSite[i] = 1;
            vLen++;
            sum = sum + GetAllArray2(candidates, candidatesSize, i - 1, vSite, vLen, target, head);
            target = target + candidates[i];
            vSite[i] = 0;
            vLen--;
        }
    }
    return sum;
}
int CampareInt2(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}
int **combinationSum2(int *candidates, int candidatesSize, int target, int *returnSize,
                      int **returnColumnSizes) {
    NUMNODE head;
    head.trail = &head;
    head.next = NULL;
    int *vSite = malloc(sizeof(int) * candidatesSize);
    memset(vSite, 0, sizeof(int) * candidatesSize);
    qsort(candidates, candidatesSize, sizeof(int), CampareInt2);
    *returnSize =
        GetAllArray2(candidates, candidatesSize, candidatesSize - 1, vSite, 0, target, &head);
    *returnColumnSizes = malloc(sizeof(int) * (*returnSize));
    int **ret = malloc(sizeof(int *) * (*returnSize));
    int i = 0;
    NUMNODE *node = head.next;
    NUMNODE *pre = node;
    while (node != NULL) {
        ret[i] = node->rNode;
        (*returnColumnSizes)[i++] = node->rLen;
        node = node->next;
        free(pre);
        pre = node;
    }

    return ret;
}

// @lc code=end
