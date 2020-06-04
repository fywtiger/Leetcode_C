/*
 * @lc app=leetcode.cn id=23 lang=c
 *
 * [23] 合并K个排序链表
 *
 * https://leetcode-cn.com/problems/merge-k-sorted-lists/description/
 *
 * algorithms
 * Hard (51.43%)
 * Likes:    648
 * Dislikes: 0
 * Total Accepted:    117K
 * Total Submissions: 227.4K
 * Testcase Example:  '[[1,4,5],[1,3,4],[2,6]]'
 *
 * 合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
 *
 * 示例:
 *
 * 输入:
 * [
 * 1->4->5,
 * 1->3->4,
 * 2->6
 * ]
 * 输出: 1->1->2->3->4->4->5->6
 *
 */
#include "Mylib.h"
struct ListNode {
    int val;
    struct ListNode *next;
};
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode LISTNODE;
void MergerTwoList(LISTNODE *one, LISTNODE *two);
struct ListNode *mergeKLists(struct ListNode **lists, int listsSize) {

    LISTNODE *one = NULL;
    LISTNODE *two = NULL;
    int i;
    switch (listsSize) {
    case 0:
        break;
    case 1:
        one = lists[0];
        break;
    default:
        one = lists[0];
        for (i = 1; i < listsSize; i++) {
            if (one == NULL) {
                one = lists[i];
                MergerTwoList(one, NULL);
            } else if (lists[i] == NULL) {
                MergerTwoList(one, NULL);
            } else {
                if (one->val < lists[i]->val) {
                    two = lists[i];
                } else {
                    two = one;
                    one = lists[i];
                }
                MergerTwoList(one, two);
            }
        }
        break;
    }
    return one;
}

void MergerTwoList(LISTNODE *one, LISTNODE *two) {
    LISTNODE *oneHead = NULL;
    LISTNODE *onePre = NULL;
    LISTNODE *twoHead = NULL;
    LISTNODE *twoNode = NULL;
    oneHead = one;
    onePre = one;
    twoHead = two;
    while (twoHead != NULL) {
        while (twoHead->val >= oneHead->val) {
            onePre = oneHead;
            oneHead = oneHead->next;
            if (oneHead == NULL) {
                onePre->next = twoHead;
                return;
            }
        }
        onePre->next = twoHead;
        twoNode = twoHead->next;
        twoHead->next = oneHead;
        oneHead = twoHead;
        twoHead = twoNode;
    }
    return;
}

// @lc code=end
