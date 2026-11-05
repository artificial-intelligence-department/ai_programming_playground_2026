/*
Алготестер Зробити паліндром
Станіслав Коваль
ШІ-12
*/

#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;
    char ch = 'a';
    int odd = 0;
    for (int i = 0; i < 26; i++){
        int count = 0;
        int code = static_cast<int>(ch+i);
        for (int j = 0; j < s.length(); j++){
            if (code == static_cast<int>(s[j])){
                count++;
            }
        }
        if (count % 2 == 1){
            odd++;
        }
    }
    if (odd <= 1){
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}