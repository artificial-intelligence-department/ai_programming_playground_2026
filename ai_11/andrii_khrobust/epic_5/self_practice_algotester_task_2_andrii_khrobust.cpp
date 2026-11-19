/*Задача 2023, Хробуст Андрій

*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    char c;
    cin >> c;
    string s, best, temp;
    for(int j = 0; j < n; j++) {
        cin >> s;
        int pos = s.length();
        for(int i = 0; i < s.length(); i++) {
            if(s[i] > c) {
                pos = i;
                break;
            }
        }
        temp = s;
        temp.insert(pos, 1, c);
        if(j == 0 || temp < best) {
            best = temp;
        }
    }
    cout << best;
    return 0;
}