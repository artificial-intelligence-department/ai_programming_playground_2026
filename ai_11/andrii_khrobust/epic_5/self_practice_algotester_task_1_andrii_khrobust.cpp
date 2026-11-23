/*Задача 0835, Хробуст Андрій

*/
#include <iostream>
using namespace std;

int main() {
    char s[1000];
    int k = 0;
    char c;
    while (cin.get(c) && c != '\0') {
        s[k] = c;
        k++;
    }
    s[k] = '\0';
    int count = 0;
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == ' ' || s[i] == '\n') {
            i++;
            continue;
        }
        int start = i;
        while (s[i] != ' ' && s[i] != '\n' && s[i] != '\0') {
            i++;
        }
        int end = i - 1;
        int l = start;
        int r = end;
        while (l < r) {
            char a = s[l];
            char b = s[r];
            if (a >= 'A' && a <= 'Z') {
                a += 32;
            }
            if (b >= 'A' && b <= 'Z') {
                b += 32;
            }
            if (a != b) {
                break;
            }
            l++;
            r--;
        }
        if (l >= r) {
            count++;
        }
    }
    cout << count;
    return 0;
}