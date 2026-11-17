
/*
    Цукерки на столі
    Рубаха Олексій
    ШІ-13
*/

#include <iostream>

int main(){
    int n; std::cin >> n;
    long long a[1000001];
    long long pref[1000001];
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    pref[0] = 0;
    long long sum = 0;

    for (int i = 1; i <= n; i++){
        sum += a[i];
        pref[i] = std::max(pref[i - 1], sum);
    }

    sum = 0;
    long long answer = 0;
    for (int i = 0; i <= n; i++){
        if (sum <= pref[n - i]) answer = std::max(answer, sum);
        if (i < n) sum += a[n - i];
    }

    std::cout << answer;

    return 0;
}