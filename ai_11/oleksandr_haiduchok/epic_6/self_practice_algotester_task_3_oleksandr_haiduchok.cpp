#include <iostream>
using namespace std;
int kody(char s){
    if(s == '1' || s == 'R' || s == 'F' || s == 'D'){
        return 0;
    }
    if(s == '2' || s == 'G' || s == 'P' || s == 'S'){
        return 1;
    }
    return 2;
}
int ret(int a, int b){
    if(a == b){
        return a;
    }
    return 3 - a - b;
}

int main(){
    int n;
    cin >> n;
    long  mog[81] = {0};
    for(int i = 0; i < n; i++){
    char s[5];
    cin >> s;
    int num1 = kody(s[0]);
    int num2 = kody(s[1]);
    int num3 = kody(s[2]);
    int num4 = kody(s[3]);
    int nome = num1 * 27 + num2 * 9 + num3 * 3 + num4;
    mog[nome]++;
    }
    long  res = 0;
    for (int i = 0; i < 81; i++) {
        long  f = mog[i];
        if (f >= 3) {
            res += f * (f - 1) * (f - 2) / 6;
        }
    }
    long  sum = 0;
    for(int j = 0; j < 81; j++){
        if(mog[j] == 0){
            continue;
        }
        int back1[4];
        back1[0] = j/27;
        back1[1] = (j/9)%3;
        back1[2] = (j/3)%3;
        back1[3] = j%3;
        for(int h = j + 1; h < 81; h++){
            if(mog[h] == 0){
            continue;
        }
        int back2[4];
        back2[0] = h/27;
        back2[1] = (h/9)%3;
        back2[2] = (h/3)%3;
        back2[3] = h%3;
        int c = 0;
        int stp = 27;
        for(int k = 0; k < 4; k++){
            c+= ret(back1[k], back2[k]) * stp;
            stp = stp/3;
        }
        sum += mog[j] * mog[h] * mog[c];
        }
    }
    res += sum/3;
    cout << res;
    return 0;
}