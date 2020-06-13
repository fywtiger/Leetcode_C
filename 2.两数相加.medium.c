/*
 * @lc app=leetcode.cn id=2 lang=c
 *
 * [2] 两数相加
 *
 * https://leetcode-cn.com/problems/add-two-numbers/description/
 *
 * algorithms
 * Medium (37.41%)
 * Likes:    4416
 * Dislikes: 0
 * Total Accepted:    438.9K
 * Total Submissions: 1.2M
 * Testcase Example:  '[2,4,3]\n[5,6,4]'
 *
 * 给出两个 非空
 * 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
 *
 * 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
 *
 * 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 *
 * 示例：
 *
 * 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
 * 输出：7 -> 0 -> 8
 * 原因：342 + 465 = 807
 *
 *
 */
#include "Mylib.h"

struct ListNode {
    int val;
    struct ListNode *next;
};
// @lc code=start
typedef struct {
    struct ListNode *head;
    struct ListNode *trail;
} RETNODE;

int InsertNodeToList(RETNODE *retList, struct ListNode *l1, struct ListNode *l2, int step) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->next = NULL;
    int val1 = l1 == NULL ? 0 : l1->val;
    int val2 = l2 == NULL ? 0 : l2->val;
    int val = val1 + val2 + step;
    int ret = val / 10;
    node->val = ret ? val - 10 : val;
    if (retList->head == NULL) {
        retList->head = node;
        retList->trail = node;
    } else {
        retList->trail->next = node;
        retList->trail = node;
    }
    return ret;
}
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    struct ListNode *head1 = l1, *head2 = l2;
    int step = 0;
    RETNODE retList;
    retList.head = NULL;
    retList.trail = NULL;
    while (head1 != NULL || head2 != NULL || step != 0) {
        step = InsertNodeToList(&retList, head1, head2, step);
        head1 = head1 == NULL ? NULL : head1->next;
        head2 = head2 == NULL ? NULL : head2->next;
    }
    return retList.head;
}

// @lc code=end
