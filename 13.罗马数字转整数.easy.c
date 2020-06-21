/*
 * @lc app=leetcode.cn id=13 lang=c
 *
 * [13] 罗马数字转整数
 *
 * https://leetcode-cn.com/problems/roman-to-integer/description/
 *
 * algorithms
 * Easy (61.54%)
 * Likes:    923
 * Dislikes: 0
 * Total Accepted:    210.1K
 * Total Submissions: 340.6K
 * Testcase Example:  '"III"'
 *
 * 罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。
 *
 * 字符          数值
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 *
 * 例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V +
 * II 。
 *
 * 通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5
 * 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
 *
 *
 * I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
 * X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
 * C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
 *
 *
 * 给定一个罗马数字，将其转换成整数。输入确保在 1 到 3999 的范围内。
 *
 * 示例 1:
 *
 * 输入: "III"
 * 输出: 3
 *
 * 示例 2:
 *
 * 输入: "IV"
 * 输出: 4
 *
 * 示例 3:
 *
 * 输入: "IX"
 * 输出: 9
 *
 * 示例 4:
 *
 * 输入: "LVIII"
 * 输出: 58
 * 解释: L = 50, V= 5, III = 3.
 *
 *
 * 示例 5:
 *
 * 输入: "MCMXCIV"
 * 输出: 1994
 * 解释: M = 1000, CM = 900, XC = 90, IV = 4.
 *
 */
#include "Mylib.h"
// @lc code=start
#define XSITENUM 4
#define YSITENUME 9
#define NUMSTRLEN 5

int GetXsite(char op) {
    if (op == 'M') {
        return 3;
    }
    if (op == 'C' || op == 'D') {
        return 2;
    }
    if (op == 'X' || op == 'L') {
        return 1;
    }
    return 0;
}
int GetYsite(char *s, char map[YSITENUME][NUMSTRLEN], int size, int *step) {
    int ret = 0;
    for (int i = 0; i < size; i++) {
        if (strncmp(s, map[i], strlen(map[i])) == 0) {
            ret = i;
        }
    }
    *step = strlen(map[ret]);
    return ret;
}
int GetRetVal(int x, int y) {
    int ret = y + 1;
    while (x) {
        ret = ret * 10;
        x--;
    }
    return ret;
}
int romanToInt(char *s) {
    char map[XSITENUM][YSITENUME][NUMSTRLEN] = {
        {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
        {"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
        {"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
        {"M", "MM", "MMM"},
    };

    int ret = 0;
    int sLen = strlen(s);
    int site = 0;
    int x, y, mSize, step;
    while (site < sLen) {
        x = GetXsite(s[site]);
        mSize = x != (XSITENUM - 1) ? YSITENUME : (XSITENUM - 1);
        y = GetYsite(&s[site], map[x], mSize, &step);
        ret += GetRetVal(x, y);
        site += step;
    }
    return ret;
}

// @lc code=end
