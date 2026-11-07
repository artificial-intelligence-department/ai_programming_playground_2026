// Щасливі рядки

#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    long long n, m;
    cin >> n >> m;
    string s, t;
    cin >>s;
    cin >>t;
    // кількість префіксів s - n+1, t - m+1;
    // кількість непорожніх префіксів = (n+1)(m+1)-1
    long long general_n = (m+1)*(n+1)-1;
    // дублікати - s[i]==t[j], рядок складається тільки з 4 та 7 тому
    long long n_4_in_s = count(s.begin(), s.end(), '4');
    long long n_7_in_s = count(s.begin(), s.end(), '7');
    long long n_4_in_t = count(t.begin(), t.end(), '4');
    long long n_7_in_t = count(t.begin(), t.end(), '7');

    long long dublicates = (n_4_in_t*n_4_in_s + n_7_in_t*n_7_in_s);
    long long res=general_n-dublicates;
    cout << res;
    return 0;

}