#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    char s[256], sc[256] = {'\0'};
    cout << "Введіть текст до 255 символів: " << endl;
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\n';
    int j = 0;
    for(int i=0; i<255; i++){
        if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
            sc[j] = s[i];
            j++;
        }
        if(s[i] == '\0'){
            break;
        }
    }
    for(int i=0; i<255; i++){
        if(s[i] >= '0' && s[i] <= '9') {
            sc[j] = s[i];
            j++;
        }
        if(s[i] == '\0'){
            break;
        }
    }
    printf( "Відсортований текст: %s" , sc);
    return 0;
}