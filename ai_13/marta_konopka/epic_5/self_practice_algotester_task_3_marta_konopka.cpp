#include <iostream>
#include <cstring>

using namespace std;
char s[100005];
char candidate[100005];
char best[100005];

int main(){
    int n;
    char c;
    cin >> n >> c;
    bool have_best = false;
    for(int i = 0; i < n; i++){
        cin >> s;
        int len = strlen(s);

        int insert_pos = len;
        for(int i = 0; i < len;i++){
            if(s[i] > c){
                insert_pos = i;
                break;
            }
        }
        int k = 0;
        for(int i = 0; i < insert_pos; i++){
            candidate[k++] = s[i];
        }
        candidate[k++] = c;
        for(int i = insert_pos; i < len; i++){
            candidate[k++] = s[i];
        }
        candidate[k] = '\0';
        if(!have_best || strcmp(candidate, best) < 0){
            strcpy(best, candidate);
            have_best = true;
        }
    
    }
    cout << best << endl;
    return 0;
}
