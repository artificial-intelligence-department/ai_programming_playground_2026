#include <iostream>
#include <string>
using namespace std;
int main(){
    string num;
    cin >> num;
    int n = num.length();
    long long count[26] = {0};
    int res = 0;
    for(int i = 0; i < num.length(); i++){
        count[num[i] - 'a']++;
    } 
    for(int k = 1; k <= n; k++){
        long long f = n/k;
        long long min = 0;
        long long max = 0;
        bool check = true;
        for(int h = 0; h < 26;h++){
            long long c = count[h];
            if(c==0){
                continue;
            }
        long long menshe = (c+f)/(f+1);
        long long bilshe = c/f;
        if(menshe > bilshe){
            check = false;
        }
        min += menshe;
        max += bilshe;
    }
     if(check == true && min <= k && k <= max){
            res = k;
            break;
        }
}
cout << res;
return 0;
}
