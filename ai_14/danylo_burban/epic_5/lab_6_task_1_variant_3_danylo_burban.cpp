#include <iostream>
#include <string.h>
#include <cctype>
using namespace std;

int main(){
    char s[255];
    fgets(s,255,stdin);
    s[strcspn(s, "\n")] = '\0';
    char *word;
    word = strtok(s, " ");
    while(word!=nullptr){
        int nOn=0;
        for (int i = 0; word[i] != '\0'; i++) {
            char x = word[i];
            if(isdigit(x)){
                nOn++;
            }
        }
        if(nOn==1){cout<<word<<endl;}
        word=strtok(nullptr, " ");
    }}