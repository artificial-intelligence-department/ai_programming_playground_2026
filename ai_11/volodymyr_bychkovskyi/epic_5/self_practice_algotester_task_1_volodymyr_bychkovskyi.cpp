/*
Назва: Фібонета
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <cstdio>

using namespace std;

int main() {
    long long n = 0;
    long long first = 0;
    long long null = 0;
    scanf("%lld %lld %lld", &n, &null, &first);

    long long step = 0;
    if (n == 0) {
        step = null;
    }
    if (n == 1) {
        step = first;
    } else {
        if (n > 1) {
            long long past1 = first;
            long long past2 = null;
            for (long long i = 2; i <= n; i++) {
                step = 0;
                step = past1 + past2;
                if ((step > 0 && past1 > 0) || (step < 0 && past1 < 0) || (step == 0 && past1 == 0)) {
                    break;
                }
                past2 = past1;
                past1 = step;
            }
        }
        
    }

    if (step > 0) {
        printf("+");
    } else if (step < 0) {
        printf("-");
    } else if (step == 0) {
        printf("0");
    }

    return 0;
}