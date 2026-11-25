/*
 * Задача: self_practice_algotester_task_2
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
//визначити чи слово палідром чи якщо так то видалити букви і порахувати скільки раз це можна зроибти
#include <cstdio>

char s[100001];

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", s);

    //  всі букви однакові 
    bool same = true;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[0]) same = false;
    }
    if (same) {
        printf("-1\n");
        return 0;
    }

    // букви чергуються через одну, довжина непарна
    if (n % 2 == 1) {
        bool alt = true;
        for (int i = 2; i < n; i++) {
            if (s[i] != s[i - 2]) alt = false;
        }
        if (alt) {
            printf("-1\n");
            return 0;
        }
    }

    // всі однакові крім середньої 
    if (n % 2 == 1) {
        int mid = n / 2;
        bool midOnly = true;
        for (int i = 0; i < n; i++) {
            if (i == mid) continue;
            if (s[i] != s[0]) midOnly = false;
        }
        if (midOnly) {
            printf("-1\n");
            return 0;
        }
    }

    //  чи слово паліндром
    bool pal = true;
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - 1 - i]) pal = false;
    }

    if (!pal) printf("1\n");
    else printf("2\n");

    return 0;
}