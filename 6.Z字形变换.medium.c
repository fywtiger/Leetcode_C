/*
 * @lc app=leetcode.cn id=6 lang=c
 *
 * [6] Z 字形变换
 *
 * https://leetcode-cn.com/problems/zigzag-conversion/description/
 *
 * algorithms
 * Medium (47.88%)
 * Likes:    696
 * Dislikes: 0
 * Total Accepted:    133.7K
 * Total Submissions: 278.7K
 * Testcase Example:  '"PAYPALISHIRING"\n3'
 *
 * 将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。
 *
 * 比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：
 *
 * L   C   I   R
 * E T O E S I I G
 * E   D   H   N
 *
 *
 * 之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。
 *
 * 请你实现这个将字符串进行指定行数变换的函数：
 *
 * string convert(string s, int numRows);
 *
 * 示例 1:
 *
 * 输入: s = "LEETCODEISHIRING", numRows = 3
 * 输出: "LCIRETOESIIGEDHN"
 *
 *
 * 示例 2:
 *
 * 输入: s = "LEETCODEISHIRING", numRows = 4
 * 输出: "LDREOEIIECIHNTSG"
 * 解释:
 *
 * L     D     R
 * E   O E   I I
 * E C   I H   N
 * T     S     G
 *
 */
#include "Mylib.h"
// @lc code=start

void FreeCoverMap(char **map, int line) {
    for (int i = 0; i < line; i++) {
        free(map[i]);
    }
    free(map);
    return;
}
int CalCoverMax(int a, int b) {
    return a > b ? a : b;
}
int CalCoverMin(int a, int b) {
    return a < b ? a : b;
}
int CalMapCol(int len, int numRows) {
    int col = 0;
    if (len % (2 * numRows - 2) != 0) {
        col = CalCoverMax(len % (2 * numRows - 2) + 1 - numRows, 1);
    }
    return col + (len / (2 * numRows - 2)) * (numRows - 1);
}
char **InitCovertMap(char *s, int mLine, int *mCol) {
    int len = strlen(s);
    char **map = malloc(sizeof(char *) * mLine);
    if (map == NULL) {
        return NULL;
    }
    int col = CalMapCol(len, mLine);
    for (int i = 0; i < mLine; i++) {
        map[i] = calloc(col, sizeof(char));
        if (map[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(map[j]);
            }
            free(map);
            return NULL;
        }
    }
    *mCol = col;
    return map;
}
int MakeCoverMapNode(char *s, char **map, int mLine, int mCol) {
    int sLen = 0;
    int col = 0;
    int step = mCol / (mLine - 1);
    while (step--) {
        for (int i = 0; i < mLine; i++) {
            map[i][col] = s[sLen++];
        }
        for (int j = 1; j < mLine - 1; j++) {
            col++;
            map[mLine - j - 1][col] = s[sLen++];
        }
        col++;
    }
    return sLen;
}

void MakeCoverMapTrail(char *s, int site, char **map, int mLine, int mCol) {
    int col = mCol - mCol % (mLine - 1);
    int sLen = strlen(s);
    if (col != mCol) {
        int end = CalCoverMin(sLen - site + 1, mLine);
        for (int i = 0; i < end; i++) {
            map[i][col] = s[site++];
        }
        end = CalCoverMin(sLen - site + 1, mLine - 1);
        for (int j = 1; j < end; j++) {
            col++;
            map[mLine - j - 1][col] = s[site++];
        }
    }
    return;
}
void UpdateCoverMap(char *s, char **map, int mLine, int mCol) {
    int site = MakeCoverMapNode(s, map, mLine, mCol);
    MakeCoverMapTrail(s, site, map, mLine, mCol);
    return;
}
char *MakeCoverRetStr(char *s, char **map, int mLine, int mCol) {
    int sLen = strlen(s);
    char *retStr = calloc(sLen + 1, sizeof(char));
    if (retStr == NULL) {
        return NULL;
    }
    int rLen = 0;
    for (int i = 0; i < mLine; i++) {
        for (int j = 0; j < mCol; j++) {
            if (map[i][j] != '\0') {
                retStr[rLen] = map[i][j];
                rLen++;
            }
        }
    }
    return retStr;
}
char *convert(char *s, int numRows) {
    if (numRows == 1) {
        return s;
    }
    int mCol;
    char **map = InitCovertMap(s, numRows, &mCol);
    if (map == NULL) {
        return NULL;
    }
    UpdateCoverMap(s, map, numRows, mCol);
    char *retStr = MakeCoverRetStr(s, map, numRows, mCol);
    FreeCoverMap(map, numRows);
    return retStr;
}

// @lc code=end
