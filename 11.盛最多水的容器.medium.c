/*
 * @lc app=leetcode.cn id=11 lang=c
 *
 * [11] 盛最多水的容器
 *
 * https://leetcode-cn.com/problems/container-with-most-water/description/
 *
 * algorithms
 * Medium (63.28%)
 * Likes:    1488
 * Dislikes: 0
 * Total Accepted:    215.7K
 * Total Submissions: 340.5K
 * Testcase Example:  '[1,8,6,2,5,4,8,3,7]'
 *
 * 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线
 * i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 *
 * 说明：你不能倾斜容器，且 n 的值至少为 2。
 *
 *
 *
 *
 *
 * 图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
 *
 *
 *
 * 示例：
 *
 * 输入：[1,8,6,2,5,4,8,3,7]
 * 输出：49
 *
 */
#include "Mylib.h"
// @lc code=start
typedef struct {
    int site;
    int height;
} HEIGHTNODE;

HEIGHTNODE *GetLeftHeight(int *height, int heightSize, int *rLen) {
    HEIGHTNODE *heightArr = calloc(heightSize, sizeof(HEIGHTNODE));
    int len = 0, maxHeight = 0;
    for (int i = 0; i < heightSize; i++) {
        if (height[i] > maxHeight) {
            heightArr[len].height = height[i];
            heightArr[len].site = i;
            maxHeight = height[i];
            len++;
        }
    }
    *rLen = len;
    return heightArr;
}

HEIGHTNODE *GetRightHeight(int *height, int heightSize, int *rLen) {
    HEIGHTNODE *heightArr = calloc(heightSize, sizeof(HEIGHTNODE));
    int len = 0, maxHeight = 0;
    for (int i = heightSize - 1; i >= 0; i--) {
        if (height[i] > maxHeight) {
            heightArr[len].height = height[i];
            heightArr[len].site = i;
            maxHeight = height[i];
            len++;
        }
    }
    *rLen = len;
    return heightArr;
}
int GetAreaMinVal(int a, int b) {
    return a < b ? a : b;
}
int GetAreaMaxVal(int a, int b) {
    return a > b ? a : b;
}
int CalMaxArea(HEIGHTNODE *right, int rightLen, HEIGHTNODE *left, int leftLen) {
    int maxArea = 0;
    for (int i = 0; i < leftLen; i++) {
        for (int j = 0; j < rightLen; j++) {
            if (right[j].site > left[i].site) {
                int tmpArea = (right[j].site - left[i].site) * GetAreaMinVal(right[j].height, left[i].height);
                maxArea = GetAreaMaxVal(maxArea, tmpArea);
            } else {
                break;
            }
        }
    }
    return maxArea;
}
int maxArea(int *height, int heightSize) {
    int rightLen = 0;
    HEIGHTNODE *right = GetRightHeight(height, heightSize, &rightLen);
    int leftLen = 0;
    HEIGHTNODE *left = GetLeftHeight(height, heightSize, &leftLen);
    int maxArea = CalMaxArea(right, rightLen, left, leftLen);
    free(right);
    free(left);
    return maxArea;
}

// @lc code=end
