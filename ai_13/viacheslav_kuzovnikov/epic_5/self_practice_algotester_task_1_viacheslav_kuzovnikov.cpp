/*
Допоможе чи заб'є?
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
#include <string>
using namespace std;
int main (){
    int k = 0;
    if (!(cin >> k)) return 0;

    string s;
    cin >> s;

    int count = 0;
    string target = "TOILET";
    size_t pos = s.find(target);

    while (pos != string::npos) {
        count++;
        pos = s.find(target, pos + target.length());
    }

    if (count >= k) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    

    return 0;
}


