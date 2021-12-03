#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int isogram(char *s);

int main(void)
{
    assert(isogram("programming") == 0);
    assert(isogram("housewarmings") == 0);
    assert(isogram("abductions") == 1);
    assert(isogram("housewarming") == 1);
    assert(isogram("hydromagnetics") == 1);
    assert(isogram("uncopyrightable") == 1);
    return 0;
}

int isogram(char *s)
{
    int letter[26]={0};
    int l=strlen(s);

    for(int i=0; i<l;i++){
        for(int j='a';j<'a'+26;j++){
            if(s[i] == j){
                letter[j-'a']++;
            }
        }
    }

    for(int i=0;i<26;i++){
        if(letter[i]>1){
            return 0;
        }
    }

    return 1;

}