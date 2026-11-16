//Задача №1806 "ДНК реп'яховірусу"
#include <cstdio>
#include <cstring>
const int Max = 100001;
int main(){
    char t[Max];
    char s[Max];
    int letters[26]={0};

    scanf("%s", t);
    scanf("%s", s);

    int Vlength=strlen(t);
    int Hlength=strlen(s);
    if(Hlength > Vlength){
        printf("0\n");
        return 0;
    }

    int frame=Vlength-Hlength+1;   

    for(int k=0; k<frame; k++){
        letters[t[k] - 'a']++;
    }

    long long result=0;
    for(int j=0; j<Hlength; j++){
        result += (long long)letters[s[j] - 'a']*(j + 1);

        letters[t[j] - 'a']--;                     
        if(j + frame < Vlength){
            letters[t[j + frame] - 'a']++;        
        }
    }

    printf("%lld\n", result);
    return 0;
}