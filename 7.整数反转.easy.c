/*
 * @lc app=leetcode.cn id=7 lang=c
 *
 * [7] 整数反转
 *
 * https://leetcode-cn.com/problems/reverse-integer/description/
 *
 * algorithms
 * Easy (34.18%)
 * Likes:    1934
 * Dislikes: 0
 * Total Accepted:    368.3K
 * Total Submissions: 1.1M
 * Testcase Example:  '123'
 *
 * 给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。
 *
 * 示例 1:
 *
 * 输入: 123
 * 输出: 321
 *
 *
 * 示例 2:
 *
 * 输入: -123
 * 输出: -321
 *
 *
 * 示例 3:
 *
 * 输入: 120
 * 输出: 21
 *
 *
 * 注意:
 *
 * 假设我们的环境只能存储得下 32 位的有符号整数，则其数值范围为 [−2^31,  2^31 − 1]。请根据这个假设，如果反转后整数溢出那么就返回
 * 0。
 *
 */
#include "Mylib.h"
#define INT_MAX 2147483647
#define INT_MIN -2147483648
// @lc code=start
int reverse(int x) {
    double val = 0;
    while (x) {
        val = val * 10 + x % 10;
        x = x / 10;
    }

    return (val > INT_MAX || val < INT_MIN) ? 0 : (int)val;
}

// @lc code=end
