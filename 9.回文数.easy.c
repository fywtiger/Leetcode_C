/*
 * @lc app=leetcode.cn id=9 lang=c
 *
 * [9] 回文数
 *
 * https://leetcode-cn.com/problems/palindrome-number/description/
 *
 * algorithms
 * Easy (57.52%)
 * Likes:    1053
 * Dislikes: 0
 * Total Accepted:    336.4K
 * Total Submissions: 584.3K
 * Testcase Example:  '121'
 *
 * 判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
 *
 * 示例 1:
 *
 * 输入: 121
 * 输出: true
 *
 *
 * 示例 2:
 *
 * 输入: -121
 * 输出: false
 * 解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
 *
 *
 * 示例 3:
 *
 * 输入: 10
 * 输出: false
 * 解释: 从右向左读, 为 01 。因此它不是一个回文数。
 *
 *
 * 进阶:
 *
 * 你能不将整数转为字符串来解决这个问题吗？
 *
 */
#include "Mylib.h"
// @lc code=start
bool GetPalindromeRet(int x) {
    double val = 0, y = x;
    while (x) {
        val = val * 10 + x % 10;
        x = x / 10;
    }
    return val == y ? true : false;
}

bool isPalindrome(int x) {
    return x < 0 ? false : GetPalindromeRet(x);
}

// @lc code=end
