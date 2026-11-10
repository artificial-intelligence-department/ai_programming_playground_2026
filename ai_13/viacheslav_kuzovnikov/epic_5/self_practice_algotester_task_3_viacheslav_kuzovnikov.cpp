/*
Назва для покемона
Кузовніков В'ячеслав Євгеніойвич
ШІ-13
*/


#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main () {
    string s1, s2;
    cin >> s1 >> s2;

    int l1 = s1.length();
    int l2 = s2.length();

    if (l1 < l2) {
        cout << "NO";
        return 0;
    }

    char arr1[l1 + 1];
    char arr2[l2 + 1];
    strcpy(arr1, s1.c_str());
    strcpy(arr2, s2.c_str());

    bool found = false;

    for (int i = 0; i <= l1 - l2; i++) {
        bool match = true;

        for (int j = 0; j < l2; j++) {
            if (arr1[i + j] != '?' && arr1[i + j] != arr2[j]) {
                match = false;
                break;
            }
        }

        if (match) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}