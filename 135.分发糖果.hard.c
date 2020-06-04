/*
 * @lc app=leetcode.cn id=135 lang=c
 *
 * [135] 分发糖果
 *
 * https://leetcode-cn.com/problems/candy/description/
 *
 * algorithms
 * Hard (42.91%)
 * Likes:    196
 * Dislikes: 0
 * Total Accepted:    20.2K
 * Total Submissions: 47K
 * Testcase Example:  '[1,0,2]'
 *
 * 老师想给孩子们分发糖果，有
 * N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。
 *
 * 你需要按照以下要求，帮助老师给这些孩子分发糖果：
 *
 *
 * 每个孩子至少分配到 1 个糖果。
 * 相邻的孩子中，评分高的孩子必须获得更多的糖果。
 *
 *
 * 那么这样下来，老师至少需要准备多少颗糖果呢？
 *
 * 示例 1:
 *
 * 输入: [1,0,2]
 * 输出: 5
 * 解释: 你可以分别给这三个孩子分发 2、1、2 颗糖果。
 *
 *
 * 示例 2:
 *
 * 输入: [1,2,2]
 * 输出: 4
 * 解释: 你可以分别给这三个孩子分发 1、2、1 颗糖果。
 * ⁠    第三个孩子只得到 1
 * 颗糖果，这已满足上述两个条件。
 *
 */
#include "Mylib.h"
// @lc code=start

#define MAXVAL(a, b) ((a) > (b) ? (a) : (b))
void printfArray(int *Array, int size);
void initArray(int *Array, int size);
int candy(int *ratings, int ratingsSize) {
    int *leftArray = malloc(sizeof(int) * ratingsSize);
    int *rightArray = malloc(sizeof(int) * ratingsSize);
    initArray(leftArray, ratingsSize);
    initArray(rightArray, ratingsSize);
    for (int i = 1; i < ratingsSize; i++) {
        if (ratings[i] > ratings[i - 1]) {
            leftArray[i] = leftArray[i - 1] + 1;
        }
    }

    for (int j = ratingsSize - 1; j > 0; j--) {
        if (ratings[j - 1] > ratings[j]) {
            rightArray[j - 1] = rightArray[j] + 1;
        }
    }

    int count = 0;
    for (int i = 0; i < ratingsSize; i++) {
        count = count + MAXVAL(leftArray[i], rightArray[i]);
    }
    free(leftArray);
    free(rightArray);
    return count;
}
void initArray(int *Array, int size) {
    for (int i = 0; i < size; i++) {
        Array[i] = 1;
    }
    return;
}
void printfArray(int *Array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", Array[i]);
    }
    printf("\n");
    return;
}

// @lc code=end
