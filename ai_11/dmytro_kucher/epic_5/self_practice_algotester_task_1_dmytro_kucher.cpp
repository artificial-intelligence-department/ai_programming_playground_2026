/*
Епік 5. Self Practice: Algotester, задача "Фібонета"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <cstdio>
using namespace std;

int main() {

    int n, a0, a1;
    scanf("%d %d %d", &n, &a0, &a1);

    if (n == 0) {
        printf("%c", a0 > 0 ? '+' : a0 < 0 ? '-' : '0');
        return 0;
    }

    for (int i = 2; i<=n; i++) {

        if ((a0 >= 0 && a1 >= 0) || (a0 <= 0 && a1 <= 0)) {
            int x = a1 != 0 ? a1 : a0;
            printf("%c", x > 0 ? '+' : x < 0 ? '-' : '0');
            return 0;
        }

        int next = a0+a1;
        a0 = a1;
        a1 = next;
    }

    printf("%c", a1 > 0 ? '+' : a1 < 0 ? '-' : '0');

    return 0;
}
