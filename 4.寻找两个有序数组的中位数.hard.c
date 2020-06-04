/*
 * @lc app=leetcode.cn id=4 lang=c
 *
 * [4] 寻找两个有序数组的中位数
 *
 * https://leetcode-cn.com/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (37.34%)
 * Likes:    2504
 * Dislikes: 0
 * Total Accepted:    180.7K
 * Total Submissions: 483.9K
 * Testcase Example:  '[1,3]\n[2]'
 *
 * 给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
 *
 * 请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
 *
 * 你可以假设 nums1 和 nums2 不会同时为空。
 *
 * 示例 1:
 *
 * nums1 = [1, 3]
 * nums2 = [2]
 *
 * 则中位数是 2.0
 *
 *
 * 示例 2:
 *
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 *
 * 则中位数是 (2 + 3)/2 = 2.5
 *
 *
 */
#include "Mylib.h"
// @lc code=start
int InsertNumToList(int iNum, int *numList, int numListLen) {

    int startSite = 0;
    int endSite = numListLen - 1;
    if (iNum >= numList[endSite]) {
        return numListLen;
    }
    if (iNum <= numList[startSite]) {
        return 0;
    }

    int nSite = 0;
    while (endSite > startSite) {
        nSite = (endSite + startSite) / 2;
        if (iNum < numList[nSite]) {
            endSite = nSite;
        } else if (iNum > numList[nSite]) {
            startSite = nSite + 1;
            nSite++;
        } else {
            return nSite;
        }
    }
    return nSite;
}
double GetMidResult(int *nums, int numsSize) {
    double dresult = (numsSize % 2)
                         ? (double)(nums[numsSize / 2])
                         : ((double)nums[numsSize / 2 - 1] + (double)nums[numsSize / 2]) / 2;
    return dresult;
}
double GetMidResultEQ(int *nums, int numsSize, int nums1Size, int *nums2, int nums2Size, int inSite,
                      int nums2Site) {
    if ((nums1Size + nums2Size) % 2 != 0) {
        return (double)nums2[nums2Site];
    } else {
        if ((nums2Site + 1) == nums2Size) {
            return ((double)nums2[nums2Site] + (double)nums[inSite]) / 2;
        } else {
            if (inSite >= numsSize) {
                return ((double)nums2[nums2Site] + (double)nums2[nums2Site + 1]) / 2;
            } else if (nums2[nums2Site + 1] <= nums[inSite]) {
                return ((double)nums2[nums2Site] + (double)nums2[nums2Site + 1]) / 2;
            } else {
                return ((double)nums2[nums2Site] + (double)nums[inSite]) / 2;
            }
        }
    }
}
double GetMidResultDy(int *nums, int AllMidSite, int nums1Size, int *nums2, int nums2Size,
                      int inSite, int nums2Site) {
    if (0 != (nums1Size + nums2Size) % 2) {
        return (double)nums[AllMidSite];
    } else {
        if (inSite > AllMidSite + 1) {
            return (double)(nums[AllMidSite] + nums[AllMidSite + 1]) / 2;
        } else {
            return (double)(nums[AllMidSite] + nums2[nums2Site]) / 2;
        }
    }
}
int GetMidSite(int nums1Size, int nums2Size) {
    return (nums1Size + nums2Size) % 2 ? (nums1Size + nums2Size) / 2
                                       : (nums1Size + nums2Size) / 2 - 1;
}
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size) {
    int j, inSite, numsSize;
    if (nums1Size == 0) {
        return GetMidResult(nums2, nums2Size);
    }
    if (nums2Size == 0) {
        return GetMidResult(nums1, nums1Size);
    }

    int *nums = malloc(sizeof(int) * (nums1Size + nums2Size));
    memcpy(nums, nums1, sizeof(int) * nums1Size);
    numsSize = nums1Size;
    int midSite = GetMidSite(nums1Size, nums2Size);
    double dresult = 0;
    for (j = 0; j < nums2Size; j++) {
        inSite = InsertNumToList(nums2[j], nums, numsSize);
        if (inSite < midSite) {
            if (inSite < numsSize) {
                memmove(&nums[inSite + 1], &nums[inSite], sizeof(int) * (numsSize - inSite));
            }
            numsSize++;
            nums[inSite] = nums2[j];
        }
        if (inSite == midSite) {
            dresult = GetMidResultEQ(nums, numsSize, nums1Size, nums2, nums2Size, inSite, j);
            free(nums);
            return dresult;
        }

        if (inSite > midSite) {
            dresult = GetMidResultDy(nums, midSite, nums1Size, nums2, nums2Size, inSite, j);
            free(nums);
            return dresult;
        }
    }
    dresult = GetMidResult(nums, numsSize);
    free(nums);
    return dresult;
}

// @lc code=end
