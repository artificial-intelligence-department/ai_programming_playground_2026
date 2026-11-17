/*
Task: lab 6 task 1 option 5
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <cstring> 
#include <cctype>
#include <cstdio>

using namespace std;


const int MAXSIZE = 255;

int main (){
    char s[MAXSIZE+2];

    fgets(s, 255, stdin);

    int len = strlen(s);

    for(int i = 0; i < len; i++){
        if(isalpha((unsigned char)s[i])){
            printf("%c", s[i]);
        }
    }
    for(int i = 0; i < len; i++){
        if(isdigit((unsigned char)s[i])){
            printf("%c", s[i]);
        }
    }
    printf("\n");



    return 0;
}