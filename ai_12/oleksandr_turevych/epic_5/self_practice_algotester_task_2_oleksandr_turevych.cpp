/*
Епік 5. Self Practice (Algotester: Найкращий акумулятор)
Автор: Туревич Олександр
Група: ШІ-12
*/

#include <iostream>
#include <cstring>

using namespace std;

int main() {
    int n;
    char c;
    cin >> n >> c;

    char s[100005];
    char candidate[100005];
    char best[100005];
    bool hasBest = false;

    for (int i = 0; i < n; ++i) {
        cin >> s;
        int len = strlen(s);

        int insertPos = len;
        for (int j = 0; j < len; ++j) {
            if (c < s[j]) {
                insertPos = j;
                break;
            }
        }

        for (int j = 0; j < insertPos; ++j) {
            candidate[j] = s[j];
        }
        candidate[insertPos] = c;
        for (int j = insertPos; j < len; ++j) {
            candidate[j + 1] = s[j];
        }
        candidate[len + 1] = '\0';

        if (!hasBest || strcmp(candidate, best) < 0) {
            strcpy(best, candidate);
            hasBest = true;
        }
    }

    cout << best << endl;

    return 0;
}