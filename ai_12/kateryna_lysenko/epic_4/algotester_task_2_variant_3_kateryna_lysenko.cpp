/*
Назва:Task 2
Автор: Катерина Лисенко
Група: ШІ-12
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[1005];

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int left = 1;
    int right = n;

    string result;

    while (true) {

        // Дрони знаходяться в одній клітинці
        if (left == right) {
            result = "Collision";
            break;
        }

        // Лівий дрон опинився правіше правого
        if (left > right) {
            result = "Miss";
            break;
        }

        // Дрони знаходяться в сусідніх клітинках
        if (right - left == 1) {
            result = "Stopped";
            break;
        }

        // Одночасне переміщення дронів
        int newLeft = left + a[left];
        int newRight = right - a[right];

        left = newLeft;
        right = newRight;
    }

    cout << left << " " << right << endl;
    cout << result << endl;

    return 0;
}
