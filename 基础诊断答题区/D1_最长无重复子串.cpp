// D1：最长无重复子串
//
// 给定一个字符串，返回其中不包含重复字符的最长连续子串长度。
//
// 示例：
// "abcabcbb" -> 3，最长子串是 "abc"
// "bbbbb"    -> 1
// "pwwkew"   -> 3，最长子串是 "wke"
//
// 要求使用滑动窗口和 unordered_map，目标时间复杂度 O(n)。

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

int lengthOfLongestSubstring(const std::string& s) {
    std::unordered_map<char, int> lastIndex; // 字符 -> 最近一次出现的下标
    int left = 0;
    int best = 0;

    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        char current = s[right];
        if(lastIndex.count(current)>0){
            left = std::max(left,lastIndex[current]+1);
        }
        // TODO 1：如果 current 之前出现过，更新 left。
        // 注意：left 不能向左退回。
        lastIndex[current] = right;
        // TODO 2：记录 current 最新出现的下标。
        best = std::max(best,right - left+1);
        // TODO 3：用当前窗口长度更新 best。
    }

    return best;
}

int main() {
    int passed = 0;
    if (lengthOfLongestSubstring("abcabcbb") == 3) ++passed;
    if (lengthOfLongestSubstring("bbbbb") == 1) ++passed;
    if (lengthOfLongestSubstring("pwwkew") == 3) ++passed;
    if (lengthOfLongestSubstring("") == 0) ++passed;
    if (lengthOfLongestSubstring("dvdf") == 3) ++passed;

    std::cout << "通过 " << passed << "/5 个用例\n";
}
