/*
 * @lc app=leetcode.cn id=211 lang=c
 *
 * [211] 添加与搜索单词 - 数据结构设计
 *
 * https://leetcode-cn.com/problems/add-and-search-word-data-structure-design/description/
 *
 * algorithms
 * Medium (44.21%)
 * Likes:    115
 * Dislikes: 0
 * Total Accepted:    10.2K
 * Total Submissions: 23.1K
 * Testcase Example:
 '["WordDictionary","addWord","addWord","addWord","search","search","search","search"]\n'
 +
  '[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]'
 *
 * 设计一个支持以下两种操作的数据结构：
 *
 * void addWord(word)
 * bool search(word)
 *
 *
 * search(word) 可以搜索文字或正则表达式字符串，字符串只包含字母 . 或 a-z 。 .
 可以表示任何一个字母。
 *
 * 示例:
 *
 * addWord("bad")
 * addWord("dad")
 * addWord("mad")
 * search("pad") -> false
 * search("bad") -> true
 * search(".ad") -> true
 * search("b..") -> true
 *
 *
 * 说明:
 *
 * 你可以假设所有单词都是由小写字母 a-z 组成的。
 *
 */
#include "Mylib.h"
// @lc code=start

struct wordList {
    char *word;
    struct wordList *next;
};
typedef struct wordList WORDLIST;
#define MAXLEN 2000
struct wordNode {
    WORDLIST *strLenHead[MAXLEN];
};
typedef struct wordNode WordDictionary;

/** Initialize your data structure here. */

WordDictionary *wordDictionaryCreate() {
    WordDictionary *head = malloc(sizeof(WordDictionary));
    for (int i = 0; i < MAXLEN; i++) {
        head->strLenHead[i] = NULL;
    }
    return head;
}

/** Adds a word into the data structure. */
void wordDictionaryAddWord(WordDictionary *obj, char *word) {
    WORDLIST *node = malloc(sizeof(WORDLIST));
    int wLen = strlen(word);
    node->word = malloc(sizeof(char) * (wLen + 1));
    strcpy(node->word, word);
    node->next = obj->strLenHead[wLen];
    obj->strLenHead[wLen] = node;
    return;
}

/** Returns if the word is in the data structure. A word could contain the dot
 * character '.' to represent any one letter. */
bool wordDictionarySearch(WordDictionary *obj, char *word) {
    int wLen = strlen(word);
    WORDLIST *head = obj->strLenHead[wLen];
    int i;
    while (head != NULL) {
        for (i = 0; i < wLen; i++) {
            if (word[i] != '.' && head->word[i] != word[i]) {
                break;
            }
        }
        if (i == wLen) {
            return true;
        }
        head = head->next;
    }
    return false;
}

void wordDictionaryFree(WordDictionary *obj) {
    WORDLIST *head = NULL;
    WORDLIST *node = NULL;
    for (int i = 0; i < MAXLEN; i++) {
        head = obj->strLenHead[i];
        while (head != NULL) {
            node = head;
            head = head->next;
            free(node->word);
            free(node);
        }
    }
    free(obj);
    return;
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);

 * bool param_2 = wordDictionarySearch(obj, word);

 * wordDictionaryFree(obj);
*/
// @lc code=end
