/*Epic 5 - Буквозабирання
Данило Бурбан
Ші - 14*/
#include <iostream>
#include <string>

using namespace std;
void solver() {
    string s, t;
    cin >> s >> t;

    int n = s.length();
    int m = t.length();
    int k = n - m;

    if (k < 0) {
        cout << "Larry\n";
        return;
    }

    if (k == 0) {
        cout << (s == t ? "Sergei\n" : "Larry\n");
        return;
    }

    int half = k / 2;
    bool sergeiWins = false;

    if (k % 2 == 1) {
        sergeiWins = (s.substr(half, m) == t) && (s.substr(half + 1, m) == t);
    } else {
        sergeiWins = (s.substr(half, m) == t) || (s.substr(half - 1, m) == t && s.substr(half + 1, m) == t);
    }

    cout << (sergeiWins ? "Sergei\n" : "Larry\n");
}

int main(){
    int n;
    cin>>n;
    while(n>0){
        solver();
        n--;
    }
    return 0;
}