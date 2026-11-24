#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

bool check(char *s, char *t, int a, int m){
    for(int i=0;i<m;i++){
        if(s[a+i] != t[i]) return false;
    }
    return true;
}

int main(){
    int n, i, j;
    cin >> n;
    cin.ignore(1000, '\n');
    char *start = new char[500002];
    char *end = new char[500002];
    for(i=0;i<n;i++){
        scanf("%s", start);
        scanf("%s", end);
        int s_l = strlen(start);
        int e_l = strlen(end);
        int d = s_l - e_l;
        bool sergei;
        if(d <= 0){
            sergei = (d == 0 && check(start, end, 0, e_l));
        }
        else if(d % 2 == 1){
            sergei = check(start, end, d/2, e_l) && check(start, end, d/2 + 1, e_l);
        }
        else{
            sergei = check(start, end, d/2, e_l) ||
                     (check(start, end, d/2 - 1, e_l) && check(start, end, d/2 + 1, e_l));
        }
        if(sergei) cout << "Sergei" << '\n';
        else cout << "Larry" << '\n';
    }
    delete[] start;
    delete[] end;
    return 0;
}