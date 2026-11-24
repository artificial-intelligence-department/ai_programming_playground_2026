/*
Епік 5. Self Practice (Algotester: Патріотична стрічка)
Автор: Туревич Олександр
Група: ШІ-12
*/

#include <iostream>

using namespace std;

int main() {
    char s[100005];
    cin >> s;

    int diff1 = 0; // для варіанту BYBYBY...
    int diff2 = 0; // для варіанту YBYBYB...

    for (int i = 0; s[i] != '\0'; ++i) {
        if (i % 2 == 0) {
            if (s[i] != 'B') {
                diff1++;
            }
            if (s[i] != 'Y') {
                diff2++;
            }
        } else {
            if (s[i] != 'Y') {
                diff1++;
            }
            if (s[i] != 'B') {
                diff2++;
            }
        }
    }

    if (diff1 < diff2) {
        cout << diff1 << endl;
    } else {
        cout << diff2 << endl;
    }

    return 0;
}
