/*
 * @lc app=leetcode.cn id=1036 lang=c
 *
 * [1036] 逃离大迷宫
 *
 * https://leetcode-cn.com/problems/escape-a-large-maze/description/
 *
 * algorithms
 * Hard (26.50%)
 * Likes:    22
 * Dislikes: 0
 * Total Accepted:    1.4K
 * Total Submissions: 5.2K
 * Testcase Example:  '[[0,1],[1,0]]\n[0,0]\n[0,2]'
 *
 * 在一个 10^6 x 10^6 的网格中，每个网格块的坐标为 (x, y)，其中 0 <= x, y <
 * 10^6。
 *
 * 我们从源方格 source 开始出发，意图赶往目标方格 target。每次移动，我们都可以走到网格中在四个方向上相邻的方格，只要该方格不在给出的封锁列表
 * blocked 上。
 *
 * 只有在可以通过一系列的移动到达目标方格时才返回 true。否则，返回 false。
 *
 *
 *
 * 示例 1：
 *
 * 输入：blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
 * 输出：false
 * 解释：
 * 从源方格无法到达目标方格，因为我们无法在网格中移动。
 *
 *
 * 示例 2：
 *
 * 输入：blocked = [], source = [0,0], target = [999999,999999]
 * 输出：true
 * 解释：
 * 因为没有方格被封锁，所以一定可以到达目标方格。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 0 <= blocked.length <= 200
 * blocked[i].length == 2
 * 0 <= blocked[i][j] < 10^6
 * source.length == target.length == 2
 * 0 <= source[i][j], target[i][j] < 10^6
 * source != target
 *
 *
 */
#include "Mylib.h"
// @lc code=start

int DfsMaze(int **mapSite, int *site, int *end, int blockedSize, bool *arriveFlag);
void FreeMazeMap(int **mapSite, int blockedSize);
int **InitMapSite_dfs(int **blocked, int blockedSize, int *source, int *target);
int arriveFlag = 0;
bool isEscapePossible(int **blocked, int blockedSize, int *blockedColSize,
                      int *source, int sourceSize, int *target,
                      int targetSize) {
    if (blockedSize == 0)
        return true;
    int **mapSite = InitMapSite_dfs(blocked, blockedSize, source, target);
    int start[2], end[2];
    start[0] = blockedSize;
    start[1] = blockedSize;
    end[0] = target[0] + blockedSize - source[0];
    end[1] = target[1] + blockedSize - source[1];
    bool arriveFlag = false;
    int ret;
    ret = DfsMaze(mapSite, start, end, blockedSize,&arriveFlag);
    if (arriveFlag) {
        FreeMazeMap(mapSite, blockedSize);
        return true;
    }
    if (ret > 0) {
        FreeMazeMap(mapSite, blockedSize);
        mapSite = InitMapSite_dfs(blocked, blockedSize, target, source);
        end[0] = source[0] + blockedSize - target[0];
        end[1] = source[1] + blockedSize - target[1];
        ret = DfsMaze(mapSite, start, end, blockedSize,&arriveFlag);
        return ret > 0 ? true : false;
    } else {
        FreeMazeMap(mapSite, blockedSize);
        return false;
    }
}
int DfsMaze(int **mapSite, int *site, int *end, int blockedSize,bool *arriveFlag) {
    int xSite = site[0];
    int ySite = site[1];
    if (xSite < 0 || xSite > (2 * blockedSize) || ySite < 0 ||
        ySite > (2 * blockedSize) || mapSite[xSite][ySite] == -1 ||
        *arriveFlag || mapSite[xSite][ySite] == 1) {
        return 0;
    }
    if (memcmp(site, end, sizeof(int) * 2) == 0) {
        *arriveFlag = true;
        return 1;
    }
    if ((abs(site[0] - blockedSize) + abs(site[1] - blockedSize)) >
        blockedSize) {
        return 1;
    }
    int direct[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int nSite[2];
    mapSite[xSite][ySite] = 1;
    int ret = 0;
    for (int i = 0; i < 4; i++) {
        nSite[0] = xSite + direct[i][0];
        nSite[1] = ySite + direct[i][1];
        ret = ret + DfsMaze(mapSite, nSite, end, blockedSize,arriveFlag);
    }
    return ret;
}

int **InitMapSite_dfs(int **blocked, int blockedSize, int *source,
                      int *target) {
    int gapSite[2];
    gapSite[0] = blockedSize - source[0];
    gapSite[1] = blockedSize - source[1];
    int mapSize = 2 * blockedSize + 1;
    int **MapSite = malloc(sizeof(int *) * mapSize);
    for (int i = 0; i < mapSize; i++) {
        MapSite[i] = malloc(sizeof(int) * mapSize);
        for (int j = 0; j < mapSize; j++) {
            if (i - gapSite[0] < 0 || i - gapSite[0] >= 1000000 ||
                j - gapSite[1] < 0 || j - gapSite[1] >= 1000000) {
                MapSite[i][j] = -1;
            } else {
                MapSite[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < blockedSize; i++) {
        if (blocked[i][0] + gapSite[0] >= 0 &&
            blocked[i][0] + gapSite[0] < mapSize &&
            blocked[i][1] + gapSite[1] >= 0 &&
            blocked[i][1] + gapSite[1] < mapSize) {
            MapSite[blocked[i][0] + gapSite[0]][blocked[i][1] + gapSite[1]] =
                -1;
        }
    }
    return MapSite;
}
void FreeMazeMap(int **mapSite, int blockedSize) {
    for (int i = 0; i < (2 * blockedSize + 1); i++) {
        free(mapSite[i]);
    }
    free(mapSite);
    return;
}

// @lc code=end
