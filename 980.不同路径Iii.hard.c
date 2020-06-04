/*
 * @lc app=leetcode.cn id=980 lang=c
 *
 * [980] 不同路径 III
 *
 * https://leetcode-cn.com/problems/unique-paths-iii/description/
 *
 * algorithms
 * Hard (70.50%)
 * Likes:    64
 * Dislikes: 0
 * Total Accepted:    5.2K
 * Total Submissions: 7.4K
 * Testcase Example:  '[[1,0,0,0],[0,0,0,0],[0,0,2,-1]]'
 *
 * 在二维网格 grid 上，有 4 种类型的方格：
 *
 *
 * 1 表示起始方格。且只有一个起始方格。
 * 2 表示结束方格，且只有一个结束方格。
 * 0 表示我们可以走过的空方格。
 * -1 表示我们无法跨越的障碍。
 *
 *
 * 返回在四个方向（上、下、左、右）上行走时，从起始方格到结束方格的不同路径的数目，每一个无障碍方格都要通过一次。
 *
 *
 *
 * 示例 1：
 *
 * 输入：[[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
 * 输出：2
 * 解释：我们有以下两条路径：
 * 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
 * 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
 *
 * 示例 2：
 *
 * 输入：[[1,0,0,0],[0,0,0,0],[0,0,0,2]]
 * 输出：4
 * 解释：我们有以下四条路径：
 * 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
 * 2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
 * 3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
 * 4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
 *
 * 示例 3：
 *
 * 输入：[[0,1],[2,0]]
 * 输出：0
 * 解释：
 * 没有一条路能完全穿过每一个空的方格一次。
 * 请注意，起始和结束方格可以位于网格中的任意位置。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= grid.length * grid[0].length <= 20
 *
 *
 */
#include "Mylib.h"
// @lc code=start
int InitStartSite(int **grid, int gridSize, int *gridColSize, int *xSite, int *ySite) {
    int validNum = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 1) {
                *xSite = i;
                *ySite = j;
            } else if (grid[i][j] == 0) {
                validNum++;
            }
        }
    }
    return validNum;
}
bool PointIsValid(int **nGrid, int gridSize, int gridColSize, int xSite, int ySite) {
    if (xSite < 0 || ySite < 0 || xSite >= gridSize || ySite >= gridColSize) {
        return true;
    }
    if (nGrid[xSite][ySite] == -1) {
        return true;
    } else if (nGrid[xSite][ySite] == 1) {
        return false;
    }
    return false;
}

int AccessToEnd(int **nGrid, int gridSize, int gridColSize, int xSite, int ySite, int step,
                int zSize) {
    if (PointIsValid(nGrid, gridSize, gridColSize, xSite, ySite)) {
        return 0;
    }
    if (nGrid[xSite][ySite] == 2) {
        return step == zSize + 1 ? 1 : 0;
    }
    int ret = 0;
    int direction[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    nGrid[xSite][ySite] = -1;
    for (int i = 0; i < 4; i++) {
        ret = ret + AccessToEnd(nGrid, gridSize, gridColSize, xSite + direction[i][0],
                                ySite + direction[i][1], step + 1, zSize);
    }
    nGrid[xSite][ySite] = 0;
    return ret;
}
int uniquePathsIII(int **grid, int gridSize, int *gridColSize) {
    int xSite = -1, ySite = -1;
    int num = InitStartSite(grid, gridSize, gridColSize, &xSite, &ySite);
    int ret = AccessToEnd(grid, gridSize, gridColSize[0], xSite, ySite, 0, num);
    return ret;
}

// @lc code=end
