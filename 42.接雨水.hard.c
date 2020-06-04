/*
 * @lc app=leetcode.cn id=42 lang=c
 *
 * [42] 接雨水
 *
 * https://leetcode-cn.com/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (50.77%)
 * Likes:    1242
 * Dislikes: 0
 * Total Accepted:    95.8K
 * Total Submissions: 188.7K
 * Testcase Example:  '[0,1,0,2,1,0,1,3,2,1,2,1]'
 *
 * 给定 n 个非负整数表示每个宽度为 1
 * 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 *
 *
 *
 * 上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6
 * 个单位的雨水（蓝色部分表示雨水）。 感谢 Marcos 贡献此图。
 *
 * 示例:
 *
 * 输入: [0,1,0,2,1,0,1,3,2,1,2,1]
 * 输出: 6
 *
 */
#include "Mylib.h"
// @lc code=start
#define MAXAREA(a, b) ((a) > (b) ? (a) : (b))
#define MINAREA(a, b) ((a) < (b) ? (a) : (b))
int trap(int *height, int heightSize) {
    int sum = 0, localArea = 0;
    int i, j, leftMax, rightMax;
    if (heightSize == 0) {
        return 0;
    }
    leftMax = height[0];
    rightMax = height[heightSize - 1];
    for (i = 1; i < heightSize - 1; i++) {
        for (j = i - 1; j < i; j++) {
            leftMax = MAXAREA(leftMax, height[j]);
        }
        if (height[i] == rightMax || i == 1) {
            rightMax = height[heightSize - 1];
            for (j = i + 1; j < heightSize; j++) {
                rightMax = MAXAREA(rightMax, height[j]);
            }
        }
        localArea = MINAREA(leftMax, rightMax) - height[i];
        sum = sum + MAXAREA(localArea, 0);
    }
    return sum;
}

// @lc code=end
