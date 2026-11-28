/*
Self practice task 3
Emoji
Лисюк Андріана
ШІ-13
*/

#include <iostream>
#include <string>
using namespace std;

string emojis[200005];
int dp[200005];

void quickSort(int left, int right) {
    if (left >= right) return;
    string pivot = emojis[left + (right - left) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (emojis[i] < pivot) i++;
        while (emojis[j] > pivot) j--;
        if (i <= j) {
            string temp = emojis[i];
            emojis[i] = emojis[j];
            emojis[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j) quickSort(left, j);
    if (i < right) quickSort(i, right);
}

bool binarySearch(int k, string target) {
    int left = 0, right = k - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (emojis[mid] == target) return true;
        if (emojis[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

int main() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    for (int i = 0; i < k; ++i) {
        cin >> emojis[i];
    }

    quickSort(0, k - 1);

    dp[0] = 0;
    int prev_colon = -1;

    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] + 1;

        if (s[i - 1] == ':') {
            if (prev_colon != -1) {
                int name_len = (i - 1) - (prev_colon + 1);
                if (name_len > 0) {
                    string word = s.substr(prev_colon + 1, name_len);
                    if (binarySearch(k, word)) {
                        if (dp[prev_colon] + 1 < dp[i]) {
                            dp[i] = dp[prev_colon] + 1;
                        }
                    }
                }
            }
            prev_colon = i - 1;
        }
    }

    cout << dp[n] << "\n";
    return 0;
}
