/*
Задача:  Зуби
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

int findLongestGroup(int sharpness[], int teethCount, int limit);

int main() {
    int teethCount;
    int limit;
    int sharpness[100000];

    cin >> teethCount >> limit;

    for (int i = 0; i < teethCount; i++) {
        cin >> sharpness[i];
    }

    int result = findLongestGroup(sharpness, teethCount, limit);
    cout << result << endl;

    return 0;
}

int findLongestGroup(int sharpness[], int teethCount, int limit) {
    int current = 0;
    int maximum = 0;

    for (int i = 0; i < teethCount; i++) {
        if (sharpness[i] >= limit) {
            current++;

            if (current > maximum) {
                maximum = current;
            }
        }
        else {
            current = 0;
        }
    }

    return maximum;
}