/*
Task: self_practice_algotester_task_2 (Щасливі рядки)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <cstdio>

char s[100005], t[100005];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", s);
    scanf("%s", t);

    long long s4 = 0, s7 = 0, t4 = 0, t7 = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '4') s4++;
        else s7++;
    }
    for (int i = 0; i < m; i++) {
        if (t[i] == '4') t4++;
        else t7++;
    }
    //загальна кількість комбінацій 
    long long total = (long long)(n + 1) * (m + 1);

    //віднімаємо зайві дублікати
    long long bad = s4 * t4 + s7 * t7;

    //виводимо і віднімаємо ще додатково 1(пустий рядок)
    printf("%lld\n", total - bad - 1);
    return 0;
}