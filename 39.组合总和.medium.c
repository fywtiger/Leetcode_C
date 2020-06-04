/*
 * @lc app=leetcode.cn id=39 lang=c
 *
 * [39] 组合总和
 *
 * https://leetcode-cn.com/problems/combination-sum/description/
 *
 * algorithms
 * Medium (68.86%)
 * Likes:    642
 * Dislikes: 0
 * Total Accepted:    89K
 * Total Submissions: 129.2K
 * Testcase Example:  '[2,3,6,7]\n7'
 *
 * 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 *
 * candidates 中的数字可以无限制重复被选取。
 *
 * 说明：
 *
 *
 * 所有数字（包括 target）都是正整数。
 * 解集不能包含重复的组合。 
 *
 *
 * 示例 1:
 *
 * 输入: candidates = [2,3,6,7], target = 7,
 * 所求解集为:
 * [
 * ⁠ [7],
 * ⁠ [2,2,3]
 * ]
 *
 *
 * 示例 2:
 *
 * 输入: candidates = [2,3,5], target = 8,
 * 所求解集为:
 * [
 * [2,2,2,2],
 * [2,3,3],
 * [3,5]
 * ]
 *
 */
#include "Mylib.h"
// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
struct numNode {
    int *rNode;
    int rLen;
    struct numNode *trail;
    struct numNode *next;
};
typedef struct numNode NUMNODE;
int GetAllArray(int *candidates, int candidatesSize, int site, int *vSite, int vLen, int target,
                NUMNODE *head) {
    if (target < 0 || site < 0) {
        return 0;
    }
    if (target == 0) {
        NUMNODE *node = malloc(sizeof(NUMNODE));
        node->rNode = malloc(sizeof(int) * vLen);
        node->rLen = vLen;
        node->next = NULL;
        int time = -1;
        for (int i = candidatesSize - 1, j = 0; i >= 0; i--) {
            time = vSite[i];
            while (time > 0) {
                node->rNode[j++] = candidates[i];
                time--;
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
            vSite[i]++;
            vLen++;
            sum = sum + GetAllArray(candidates, candidatesSize, i, vSite, vLen, target, head);
            target = target + candidates[i];
            vSite[i]--;
            vLen--;
        }
    }
    return sum;
}
int CampareInt(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}
int **combinationSum(int *candidates, int candidatesSize, int target, int *returnSize,
                     int **returnColumnSizes) {
    NUMNODE head;
    head.trail = &head;
    head.next = NULL;
    int *vSite = malloc(sizeof(int) * candidatesSize);
    memset(vSite, 0, sizeof(int) * candidatesSize);
    qsort(candidates, candidatesSize, sizeof(int), CampareInt);
    *returnSize =
        GetAllArray(candidates, candidatesSize, candidatesSize - 1, vSite, 0, target, &head);
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
