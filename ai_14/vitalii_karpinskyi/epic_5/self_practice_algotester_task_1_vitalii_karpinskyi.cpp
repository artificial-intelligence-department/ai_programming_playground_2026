/*
Задача: Снігурочка
Карпінський Віталій
ШІ-14
*/
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string text;
    int count = 0;
    while (cin >> text) {
        size_t size = text.length();
        for (int i = 0; i < size; i++) {
            text[i] = tolower(text[i]);
        }
        int left = 0;
        int right = text.length() - 1;
        bool isPal = true;
        while(right > left) {
            if (text[left] == text[right]) {
                left++;
                right--;
            } else {
                isPal = false;
                break;
            }
        }
        if (isPal) {
            count++;
        }
        
    }
    cout << count;


    return 0;
}