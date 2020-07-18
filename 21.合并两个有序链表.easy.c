/*
 * @lc app=leetcode.cn id=21 lang=c
 *
 * [21] 合并两个有序链表
 *
 * https://leetcode-cn.com/problems/merge-two-sorted-lists/description/
 *
 * algorithms
 * Easy (62.48%)
 * Likes:    1142
 * Dislikes: 0
 * Total Accepted:    310.4K
 * Total Submissions: 490.5K
 * Testcase Example:  '[1,2,4]\n[1,3,4]'
 *
 * 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
 *
 *
 *
 * 示例：
 *
 * 输入：1->2->4, 1->3->4
 * 输出：1->1->2->3->4->4
 *
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
typedef struct {
    LISTNODE *head;
    LISTNODE *insert;
} INSERTRESULT;

void InsertListNodeMergeTwo(INSERTRESULT *insertResult, LISTNODE *node) {
    LISTNODE *head = insertResult->insert;
    LISTNODE *pre = head;
    LISTNODE *now = head;
    while (now != NULL) {
        if (node->val < now->val) {
            if (now == head) {
                node->next = head;
                insertResult->head = node;
                insertResult->insert = node;
                return;
            }
            pre->next = node;
            node->next = now;
            insertResult->insert = node;
            return;
        }
        pre = now;
        now = now->next;
    }
    node->next = NULL;
    pre->next = node;
    insertResult->insert = node;
    return;
}
struct ListNode *mergeTwoLists(struct ListNode *l1, struct ListNode *l2) {
    if (l1 == NULL) {
        return l2;
    }
    LISTNODE *node = NULL;
    INSERTRESULT insertRet;
    insertRet.head = l1;
    insertRet.insert = l1;
    while (l2 != NULL) {
        node = l2;
        l2 = l2->next;
        InsertListNodeMergeTwo(&insertRet, node);
    }
    return insertRet.head;
}
// @lc code=end
