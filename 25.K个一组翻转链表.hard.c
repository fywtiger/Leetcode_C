/*
 * @lc app=leetcode.cn id=25 lang=c
 *
 * [25] K 个一组翻转链表
 *
 * https://leetcode-cn.com/problems/reverse-nodes-in-k-group/description/
 *
 * algorithms
 * Hard (62.67%)
 * Likes:    696
 * Dislikes: 0
 * Total Accepted:    95.1K
 * Total Submissions: 151.8K
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * 给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。
 *
 * k 是一个正整数，它的值小于或等于链表的长度。
 *
 * 如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
 *
 *
 *
 * 示例：
 *
 * 给你这个链表：1->2->3->4->5
 *
 * 当 k = 2 时，应当返回: 2->1->4->3->5
 *
 * 当 k = 3 时，应当返回: 3->2->1->4->5
 *
 *
 *
 * 说明：
 *
 *
 * 你的算法只能使用常数的额外空间。
 * 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
 *
 *
 */
#include "Mylib.h"
struct ListNode {
    int val;
    struct ListNode *next;
};
// @lc code=start
typedef struct ListNode LISTNODE;
typedef struct {
    LISTNODE *head;
    LISTNODE *trail;
} RLIST;
void InsertRetListNode(RLIST *rList, LISTNODE **listArr, int n) {
    rList->head = rList->head == NULL ? listArr[n] : rList->head;
    while (n >= 0) {
        if (rList->trail == NULL) {
            rList->trail = rList->head;
        } else {
            rList->trail->next = listArr[n];
            rList->trail = listArr[n];
        }
        n--;
    }
    return;
}
void InsertRetListNodeBack(RLIST *rList, LISTNODE **listArr, int n) {
    rList->head = rList->head == NULL ? listArr[0] : rList->head;
    if (rList->trail != NULL) {
        rList->trail->next = listArr[0];
    }
    rList->trail = listArr[n];
    return;
}
LISTNODE *MakeSwapRetList(RLIST *rList, LISTNODE **listArr, LISTNODE *head, int k) {
    int n = 0;
    while (head != NULL && n != k) {
        listArr[n] = head;
        head = head->next;
        n++;
    }
    if (n == k) {
        InsertRetListNode(rList, listArr, n - 1);
    } else {
        InsertRetListNodeBack(rList, listArr, n - 1);
    }
    return head;
}
LISTNODE *reverseKGroup(LISTNODE *head, int k) {
    if (head == NULL || k <= 1) {
        return head;
    }
    RLIST ret;
    ret.head = NULL;
    ret.trail = NULL;
    LISTNODE **listArr = malloc(sizeof(LISTNODE *) * k);
    while (head != NULL) {
        head = MakeSwapRetList(&ret, listArr, head, k);
    }
    ret.trail->next = NULL;
    free(listArr);
    return ret.head;
}

// @lc code=end
