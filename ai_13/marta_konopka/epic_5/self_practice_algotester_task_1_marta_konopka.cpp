#include <iostream>
#include <cstring>
using namespace std;

const int MAX_N = 100005;
char t[MAX_N];
char s[MAX_N];
int k[MAX_N][26];

int main(){
    cin >> t >> s;
    int n = strlen(t);
    int m = strlen(s);

    for(int i = 0; i < n; i++){
        for(int c = 0; c < 26; c++){
            k[i + 1][c] = k[i][c];
        }
        k[i + 1][t[i] - 'a']++;
    }
    long long a = 0;
    for(int j = 0; j < m; j++){
        int L = j;
        int R = n - m + j;

        if(L <= R){
            int c = s[j] - 'a';
            int matches = k[R + 1][c] - k[L][c];
            a += (long long)matches * (j + 1);
        }
    }
    cout << a;
    return 0;
}
