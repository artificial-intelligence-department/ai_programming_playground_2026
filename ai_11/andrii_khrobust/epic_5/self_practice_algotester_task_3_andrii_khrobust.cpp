/*Задача 1633, Хробуст Андрій

*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    long long s4 = 0, s7 = 0;
    long long t4 = 0, t7 = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '4') {
            s4++;
        }
        else {
            s7++;
        }
    }
    for(int i = 0; i < m; i++) {
        if(t[i] == '4') {
            t4++;
        }
        else {
            t7++;
        }
    }
    long long sum = (n + 1) * (m + 1) - s4 * t4 - s7 * t7 - 1;
    cout << sum;
    return 0;
}