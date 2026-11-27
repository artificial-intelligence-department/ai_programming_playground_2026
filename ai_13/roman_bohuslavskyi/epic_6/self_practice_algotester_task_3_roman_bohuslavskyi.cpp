/*
Задача:  Гори акумуляторів
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

struct Interval {
    int left;
    int right;
};

int countLifted(int positions[], int n, int p);

int main() {
    int n;
    cin >> n;

    int* positions = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> positions[i];
    }

    int p;
    cin >> p;

    cout << countLifted(positions, n, p) << '\n';

    delete[] positions;
    return 0;
}

int countLifted(int positions[], int n, int p) {
    Interval lifted{p, p};
    int count = 0;

    for (int i = 0; i < n; i++) {
        int left = positions[i];
        int right = positions[i] + 1;

        if (left <= lifted.right && right >= lifted.left) {
            count++;

            if (left < lifted.left) {
                lifted.left = left;
            }
            if (right > lifted.right) {
                lifted.right = right;
            }
        }
    }

    return count;
}
