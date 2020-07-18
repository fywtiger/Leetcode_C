/*
 * @lc app=leetcode.cn id=20 lang=c
 *
 * [20] 有效的括号
 *
 * https://leetcode-cn.com/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (41.63%)
 * Likes:    1694
 * Dislikes: 0
 * Total Accepted:    328.6K
 * Total Submissions: 782.6K
 * Testcase Example:  '"()"'
 *
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
 *
 * 有效字符串需满足：
 *
 *
 * 左括号必须用相同类型的右括号闭合。
 * 左括号必须以正确的顺序闭合。
 *
 *
 * 注意空字符串可被认为是有效字符串。
 *
 * 示例 1:
 *
 * 输入: "()"
 * 输出: true
 *
 *
 * 示例 2:
 *
 * 输入: "()[]{}"
 * 输出: true
 *
 *
 * 示例 3:
 *
 * 输入: "(]"
 * 输出: false
 *
 *
 * 示例 4:
 *
 * 输入: "([)]"
 * 输出: false
 *
 *
 * 示例 5:
 *
 * 输入: "{[]}"
 * 输出: true
 *
 */
#include "Mylib.h"
// @lc code=start

bool StrCharIsPush(char op) {
    return (op == '(' || op == '{' || op == '[');
}
bool MatchCharFromStack(char *stack, int site, char b) {
    if (site < 0) {
        return true;
    }
    if (stack[site] == '(' && b == ')') {
        return false;
    }
    if (stack[site] == '[' && b == ']') {
        return false;
    }
    if (stack[site] == '{' && b == '}') {
        return false;
    }
    return true;
}
bool isValid(char *s) {
    int size = strlen(s);
    char *stack = calloc(size, sizeof(char));
    int sLen = 0;
    for (int i = 0; i < size; i++) {
        if (StrCharIsPush(s[i])) {
            stack[sLen] = s[i];
            sLen++;
        } else {
            if (MatchCharFromStack(stack, sLen - 1, s[i])) {
                return false;
            }
            sLen--;
        }
    }
    return sLen == 0;
}

// @lc code=end
