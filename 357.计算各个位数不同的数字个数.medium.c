/*
 * @lc app=leetcode.cn id=357 lang=c
 *
 * [357] 计算各个位数不同的数字个数
 *
 * https://leetcode-cn.com/problems/count-numbers-with-unique-digits/description/
 *
 * algorithms
 * Medium (50.63%)
 * Likes:    60
 * Dislikes: 0
 * Total Accepted:    9.2K
 * Total Submissions: 18.2K
 * Testcase Example:  '2'
 *
 * 给定一个非负整数 n，计算各位数字都不同的数字 x 的个数，其中 0 ≤ x < 10^n 。
 *
 * 示例:
 *
 * 输入: 2
 * 输出: 91
 * 解释: 答案应为除去 11,22,33,44,55,66,77,88,99 外，在 [0,100) 区间内的所有数字。
 *
 *
 */
#include "Mylib.h"
// @lc code=start

int countNumbersWithUniqueDigits(int n) {
    if (n == 0) {
        return 1;
    }
    if (n > 10) {
        return countNumbersWithUniqueDigits(10);
    }
    int ret = 9;
    for (int i = 1; i < n; i++) {
        ret = ret * (10 - i);
    }
    ret = ret + countNumbersWithUniqueDigits(n - 1);
    return ret;
}

// @lc code=end
