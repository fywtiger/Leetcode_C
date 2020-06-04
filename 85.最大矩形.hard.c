/*
 * @lc app=leetcode.cn id=85 lang=c
 *
 * [85] 最大矩形
 *
 * https://leetcode-cn.com/problems/maximal-rectangle/description/
 *
 * algorithms
 * Hard (45.71%)
 * Likes:    406
 * Dislikes: 0
 * Total Accepted:    26.4K
 * Total Submissions: 57.5K
 * Testcase Example:
 * '[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]'
 *
 * 给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。
 *
 * 示例:
 *
 * 输入:
 * [
 * ⁠ ["1","0","1","0","0"],
 * ⁠ ["1","0","1","1","1"],
 * ⁠ ["1","1","1","1","1"],
 * ⁠ ["1","0","0","1","0"]
 * ]
 * 输出: 6
 *
 */
#include "Mylib.h"
// @lc code=start

int getMinValue(int a, int b) {
    return a < b ? a : b;
}

int getMaxValue(int a, int b) {
    return a > b ? a : b;
}

int calMaxValue(int **newMatrix, int matrixSize, int lineNO, int lineSize) {
    int curArea , maxArea;
    int maxWidth = newMatrix[lineNO][lineSize];
    for (int i = lineNO; i < matrixSize; i++) {
        maxWidth = getMinValue(maxWidth, newMatrix[i][lineSize]);
        curArea = maxWidth * (i + 1 - lineNO);
        maxArea = getMaxValue(maxArea, curArea);
        if (maxWidth == 0) {
            return maxArea;
        }
    }
    return maxArea;
}

int **MakeNerMatrix(char **matrix, int matrixSize, int *matrixColSize) {
    int **newMatrix = (int **)malloc(sizeof(int *) * matrixSize);
    int tmp;
    for (int i = 0; i < matrixSize; i++) {
        tmp = 0;
        newMatrix[i] = malloc(sizeof(int) * matrixColSize[i]);
        for (int j = 0; j < matrixColSize[i]; j++) {
            newMatrix[i][j] = matrix[i][j] - '0';
            if (newMatrix[i][j] == 1) {
                newMatrix[i][j] = newMatrix[i][j] + tmp;
                tmp = newMatrix[i][j];
            } else if (newMatrix[i][j] == 0) {
                tmp = 0;
            }
        }
    }
    return newMatrix;
}
int GetMatrixMaxValue(int **newMatrix, int matrixSize, int *matrixColSize) {
    int result = 0;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[0]; j++) {
            result = getMaxValue(result, calMaxValue(newMatrix, matrixSize, i, j));
        }
    }
    return result;
}
void FreeMatrixMemory(int **newMatrix, int matrixSize) {
    for (int i = 0; i < matrixSize; i++) {
        free(newMatrix[i]);
    }
    free(newMatrix);
    return;
}
void PrintMatrix(int **matrix,int matrixSize,int *matrixColSize)
{
    for(int i=0;i<matrixSize;i++)
    {
        for(int j=0;j<matrixColSize[i];j++)
        {
            printf("%2d ",matrix[i][j]);
        }
        printf("\n");
    }
    return;
}
int maximalRectangle(char **matrix, int matrixSize, int *matrixColSize) {
    int **newMatrix = MakeNerMatrix(matrix, matrixSize, matrixColSize);
    PrintMatrix(newMatrix, matrixSize, matrixColSize);
    int result = GetMatrixMaxValue(newMatrix, matrixSize, matrixColSize);
    FreeMatrixMemory(newMatrix, matrixSize);
    return result;
}
// @lc code=end
