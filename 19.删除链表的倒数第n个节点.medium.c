/*
 * @lc app=leetcode.cn id=19 lang=c
 *
 * [19] 删除链表的倒数第N个节点
 *
 * https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/description/
 *
 * algorithms
 * Medium (38.60%)
 * Likes:    893
 * Dislikes: 0
 * Total Accepted:    198.1K
 * Total Submissions: 507.8K
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
 *
 * 示例：
 *
 * 给定一个链表: 1->2->3->4->5, 和 n = 2.
 *
 * 当删除了倒数第二个节点后，链表变为 1->2->3->5.
 *
 *
 * 说明：
 *
 * 给定的 n 保证是有效的。
 *
 * 进阶：
 *
 * 你能尝试使用一趟扫描实现吗？
 *
 */
#include "Mylib.h"

struct ListNode {
    int val;
    struct ListNode *next;
};
// @lc code=start
struct ListNode *removeNthFromEnd(struct ListNode *head, int n) {
    struct ListNode *fast = head;
    struct ListNode *slow = head;
    struct ListNode *slowPre = head;

    int step = 1;
    while (fast != NULL) {
        if (step > n) {
            slowPre = slow;
            slow = slow->next;
        }
        step++;
        fast = fast->next;
    }
    if (slow == slowPre) {
        return head->next;
    }
    slowPre->next = slow->next;
    return head;
}

// @lc code=end
