/*
 * @lc app=leetcode.cn id=17 lang=c
 *
 * [17] 电话号码的字母组合
 *
 * https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * algorithms
 * Medium (53.52%)
 * Likes:    760
 * Dislikes: 0
 * Total Accepted:    123.1K
 * Total Submissions: 229.2K
 * Testcase Example:  '"23"'
 *
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
 *
 * 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
 *
 *
 *
 * 示例:
 *
 * 输入："23"
 * 输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 *
 *
 * 说明:
 * 尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。
 *
 */
#include "Mylib.h"
// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **InitLetterComRetArray(char *digits, int *returnSize) {
    int size = strlen(digits);
    int sum = 1;
    for (int i = 0; i < size; i++) {
        sum = (digits[i] == '7' || digits[i] == '9') ? sum * 4 : sum * 3;
    }
    char **ret = malloc(sizeof(char *) * sum);
    for (int i = 0; i < sum; i++) {
        ret[i] = calloc(size + 1, sizeof(char));
    }
    *returnSize = sum != 1 ? sum : 0;
    return ret;
}
void FillLetterComRetArray(char *digits, char *str, int *rSize, char **retArray) {
    int loop = (digits[0] == '7' || digits[0] == '9') ? 4 : 3;
    char map[8][5] = {
        "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz",
    };
    for (int i = 0; i < loop; i++) {
        str[0] = map[digits[0] - '2'][i];
        strcpy(retArray[*rSize], str);
        *rSize = *rSize + 1;
    }
    return;
}
void MakeLetterComRetArray(char *digits, int dSite, int *rSize, char **retArray, char *str) {
    if (dSite == 0) {
        FillLetterComRetArray(digits, str, rSize, retArray);
        return;
    }
    int loop = ((digits[dSite] == '7') || (digits[dSite] == '9')) ? 4 : 3;
    char map[8][5] = {
        "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz",
    };
    for (int i = 0; i < loop; i++) {
        str[dSite] = map[digits[dSite] - '2'][i];
        MakeLetterComRetArray(digits, dSite - 1, rSize, retArray, str);
    }
    return;
}
char **letterCombinations(char *digits, int *returnSize) {
    char **retArray = InitLetterComRetArray(digits, returnSize);
    if (*returnSize == 0) {
        return NULL;
    }
    int size = strlen(digits);
    int rSize = 0;
    char *str = calloc(size + 1, sizeof(char));
    MakeLetterComRetArray(digits, size - 1, &rSize, retArray, str);
    free(str);
    return retArray;
}

// @lc code=end
