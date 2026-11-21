// Self Practice, задача 3 - "Знайди паліндром" (Algotester)
// довжина найбільшого підрядка-паліндрома
// n <= 7000, тому можна розширювати паліндром від кожного центру - O(n^2)
#include <iostream>
#include <string>
using namespace std;

// розширюю вліво і вправо, поки букви однакові, повертаю довжину паліндрома
int expand(const string &s, int left, int right) {
    int n = s.length();
    while (left >= 0 && right < n && s[left] == s[right]) {
        left--;
        right++;
    }
    // після циклу left і right вже на одну позицію "зайві"
    return right - left - 1;
}

int main() {
    int n;
    string s;
    cin >> n >> s;

    int best = 1;
    for (int i = 0; i < n; i++) {
        // центр - буква (непарна довжина)
        int odd = expand(s, i, i);
        // центр між буквами i та i+1 (парна довжина)
        int even = expand(s, i, i + 1);
        if (odd > best) {
            best = odd;
        }
        if (even > best) {
            best = even;
        }
    }

    cout << best << endl;
    return 0;
}
