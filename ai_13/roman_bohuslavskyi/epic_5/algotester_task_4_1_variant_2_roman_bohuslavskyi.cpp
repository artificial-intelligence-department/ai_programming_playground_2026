/*
Задача:  Алготестер Lab4v2
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> numbers(n);

    for (int i = 0; i < n; i++) cin >> numbers[i];

    sort(numbers.begin(), numbers.end());
    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
    n = numbers.size();
    k %= n;
    int first = numbers[k];
    
    auto check = [first](int value) {
        return value >= first;
    };

    auto middle = partition(numbers.begin(), numbers.end(), check);

    sort(numbers.begin(), middle);
    sort(middle, numbers.end());

    cout << n << endl;
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << numbers[i];
    }
    cout << endl;
    return 0;
}