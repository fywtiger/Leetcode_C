/*
 * @lc app=leetcode.cn id=24 lang=c
 *
 * [24] 两两交换链表中的节点
 *
 * https://leetcode-cn.com/problems/swap-nodes-in-pairs/description/
 *
 * algorithms
 * Medium (65.65%)
 * Likes:    597
 * Dislikes: 0
 * Total Accepted:    140.4K
 * Total Submissions: 211.1K
 * Testcase Example:  '[1,2,3,4]'
 *
 * 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
 *
 * 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 *
 *
 *
 * 示例:
 *
 * 给定 1->2->3->4, 你应该返回 2->1->4->3.
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
    LISTNODE *pre;
} SWAPRET;
void SwapListNode(LISTNODE *head, LISTNODE *pre, SWAPRET *retNode) {
    if (head->next == NULL) {
        retNode->head = NULL;
        return;
    }
    if (pre != NULL) {
        pre->next = head->next;
    }
    LISTNODE *next = head->next->next;
    head->next->next = head;
    head->next = next;
    retNode->head = next;
    retNode->pre = head;
    return;
}
struct ListNode *swapPairs(struct ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    LISTNODE *retList = head->next;
    LISTNODE *pre = NULL;
    LISTNODE *node = head;
    SWAPRET retNode;
    while (node != NULL) {
        SwapListNode(node, pre, &retNode);
        node = retNode.head;
        pre = retNode.pre;
    }
    return retList;
}

// @lc code=end
