// лабораторна 6 варіант 20

#include <iostream>
#include <cstdio>

using namespace std;

int main(){
    char s[256];  
    int len = 0;
    int maxLen = 0;  

    fgets(s, 256, stdin);

    for (int i=0; s[i] != '\0'; i++){
        if (s[i] != ' ' && s[i] != '.'){
            len++;
        }
        else {
            if (len > maxLen){
                maxLen = len;
            }
            len =0;
        }
    }
    cout << maxLen<<endl;
    return 0;
}