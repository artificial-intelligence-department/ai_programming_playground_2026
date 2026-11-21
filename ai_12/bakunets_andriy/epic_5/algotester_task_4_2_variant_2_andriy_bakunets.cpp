#include <cstdio>

bool present[100];   
int a[100];      

int main() {

    int n, k;

    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) { // видаляємо повтори
        int x;
        scanf("%d", &x);
        present[x] = true;
    }

    int cnt = 0;
    for (int v = 0; v <= 100; v++) { // збираємо унікальні числа
        if (present[v]) {
            a[cnt] = v;
            cnt++;
        }
    }

    printf("%d\n", cnt); // виводимо кількість унікальних чисел

    for (int i = 0; i < cnt; i++) { // виводимо числа , переміщені на k позицій
        printf("%d ", a[(i + k) % cnt]);
    }

    printf("\n");
    return 0;
}