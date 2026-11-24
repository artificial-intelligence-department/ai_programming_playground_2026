#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// порівняння: спочатку за остачею від ділення на 3, 0 і 2 за зростанням, а 1 за спаданням
bool compare(int x, int y) {
    int rx = x % 3;
    int ry = y % 3;

    if (rx != ry) {
        return rx < ry;
    }

    if (rx == 1) {
        return x > y;
    }

    return x < y;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end(), compare);

    a.erase(unique(a.begin(), a.end()), a.end());

    cout << a.size() << '\n';

    for (int x : a) {
        cout << x << " ";
    }

    return 0;
}