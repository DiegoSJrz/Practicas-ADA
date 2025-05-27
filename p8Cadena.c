#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool areAnagrams(const char* s1, const char* s2, int len) {
    int count[26] = {0};
    for (int i = 0; i < len; i++) {
        count[s1[i] - 'a']++;
        count[s2[i] - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) return false;
    }
    return true;
}

bool isScrambleUtil(const char* s1, const char* s2, int len) {
    if (strncmp(s1, s2, len) == 0) return true;
    if (!areAnagrams(s1, s2, len)) return false;

    for (int i = 1; i < len; i++) {
        // Case 1: No swap
        if (isScrambleUtil(s1, s2, i) && isScrambleUtil(s1 + i, s2 + i, len - i)) {
            return true;
        }
        // Case 2: Swap
        if (isScrambleUtil(s1, s2 + len - i, i) && isScrambleUtil(s1 + i, s2, len - i)) {
            return true;
        }
    }
    return false;
}

bool isScramble(const char* s1, const char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2) return false;
    return isScrambleUtil(s1, s2, len1);
}

int main() {
    char s1[31], s2[31];

    printf("Ingrese s1: ");
    scanf("%s", s1);

    printf("Ingrese s2: ");
    scanf("%s", s2);

    if (isScramble(s1, s2)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}