/*
 * @lc app=leetcode.cn id=30 lang=c
 *
 * [30] 串联所有单词的子串
 *
 * https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/description/
 *
 * algorithms
 * Hard (30.34%)
 * Likes:    260
 * Dislikes: 0
 * Total Accepted:    32.3K
 * Total Submissions: 106.1K
 * Testcase Example:  '"barfoothefoobarman"\n["foo","bar"]'
 *
 * 给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words
 * 中所有单词串联形成的子串的起始位置。
 *
 * 注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。
 *
 *
 *
 * 示例 1：
 *
 * 输入：
 * ⁠ s = "barfoothefoobarman",
 * ⁠ words = ["foo","bar"]
 * 输出：[0,9]
 * 解释：
 * 从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
 * 输出的顺序不重要, [9,0] 也是有效答案。
 *
 *
 * 示例 2：
 *
 * 输入：
 * ⁠ s = "wordgoodgoodgoodbestword",
 * ⁠ words = ["word","good","best","word"]
 * 输出：[]
 *
 *
 */
#include "Mylib.h"
// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct myStruct {
    char *key;
    int cnt;     /* 单词表中key单词出现的次数 */
    int usedCnt; /* 子串中已经被使用的次数，由于顺序无所谓，所以只统计次数是否用完即可 */
    UT_hash_handle hh;
} WordNode;

WordNode *map;

void Init(char **words, int wordsSize) {
    map = NULL;
    WordNode *s = NULL;
    for (int i = 0; i < wordsSize; i++) {
        HASH_FIND_STR(map, words[i], s);
        if (s == NULL) {
            s = calloc(1, sizeof(WordNode));
            s->key = words[i];
            s->cnt++;
            HASH_ADD_STR(map, key, s);
        } else {
            s->cnt++;
        }
    }
    return;
}
void ResetMap() {
    WordNode *s, *tmp;
    HASH_ITER(hh, map, s, tmp) {
        s->usedCnt = 0;
    }
    return;
}

void FreeAllMemory(int *visit) {
    WordNode *current_user, *tmp;
    HASH_ITER(hh, map, current_user, tmp) {
        HASH_DEL(map, current_user);
        free(current_user);
    }
    free(visit);
    return;
}

int *findSubstring(char *s, char **words, int wordsSize, int *returnSize) {
    if ((s == NULL) || (words == NULL) || (wordsSize == 0)) {
        *returnSize = 0;
        return NULL;
    }
    Init(words, wordsSize);
    int len = strlen(s);
    int *res = calloc(len, sizeof(int));
    int *visit = calloc(len, sizeof(int));
    int cnt = 0;
    int wordLen = strlen(words[0]);
    char *tmp = calloc(wordLen + 1, sizeof(char));
    WordNode *t;
    for (int i = 0; i <= len - (wordLen * wordsSize); i++) { /* 每个字母进行向后移位 */
        int j;
        ResetMap(); /* 重置map中的used计数 */
        for (j = i; j < i + (wordLen * wordsSize); j += wordLen) {
            if (visit[j] == -1) {
                break;
            }
            strncpy(tmp, &s[j], wordLen);
            HASH_FIND_STR(map, tmp, t);
            if (t == NULL) {
                visit[j] = -1;
                break;
            }
            if (t->usedCnt == t->cnt) {
                break;
            }
            t->usedCnt++; /* 使用次数+1 */
        }
        if (j == i + (wordLen * wordsSize)) { /* 所有单词都能匹配上 */
            res[cnt++] = i;
        }
    }
    *returnSize = cnt;
    FreeAllMemory(visit);
    return res;
}

// @lc code=end
