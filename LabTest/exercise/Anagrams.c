#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int anagram(char s1[], char s2[]);

int main(void)
{
    assert(anagram("elvis", "lives") == 1);
    assert(anagram("dreads", "sadder") == 1);
    assert(anagram("replays", "parsley") == 1);
    assert(anagram("listen", "silent") == 1);
    assert(anagram("orchestra", "carthorse") == 1);
    /* Two identical words are not anagrams */
    assert(anagram("elvis", "elvis") == 0);
    assert(anagram("neill", "neil") == 0);
    assert(anagram("neil", "neill") == 0);
    assert(anagram("horse", "short") == 0);
    return 0;
}

int anagram(char s1[], char s2[])
{
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int cnt1[26]={0};
    int cnt2[26]={0};

    if(s1 == s2){
        return 0;
    }

    if (l1 != l2){
        return 0;
    }
    
    if(l1 == l2){
        for(int i=0;i<l1;i++){
            for(int j='a';j<'a'+26;j++){
                if(s1[i] == j){
                    cnt1[j-'a']++;
                }
                if(s2[i] == j){
                    cnt2[j-'a']++;
                }
            }
        }

        for(int i=0;i<26;i++){
            if(cnt1[i] != cnt2[i]){
                return 0;
            }
        }
    }
    return 1;
}
