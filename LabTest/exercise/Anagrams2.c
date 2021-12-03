#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int derange(char s1[], char s2[]);

int main(void)
{
    assert(derange("elvis", "lives") == 0);
    assert(derange("dreads", "sadder") == 1);
    assert(derange("replays", "parsley") == 1);
    assert(derange("listen", "silent") == 0);
    assert(derange("orchestra", "carthorse") == 1);

    return 0;
}

int derange(char s1[], char s2[])
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

        for(int i=0;i<l1;i++){
            if (s1[i] == s2[i]){
                return 0;
            }
        }

    }



    return 1;
}
