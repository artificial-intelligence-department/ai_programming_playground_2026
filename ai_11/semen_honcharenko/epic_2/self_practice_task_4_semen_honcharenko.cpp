/*
    Алготестер. "Зуби"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>

int main() {
    int n = 0;
    int k = 0;
    int a = 0;
    int sum_1 = 0;
    int sum_2 = 0;

    std::cin >> n;
    std::cin >> k;
    for (int i; i < n; i++) {
        std::cin >> a;
        if (a >= k) {
            sum_1 += 1;
            if (sum_1 > sum_2) {
                sum_2 = sum_1;
            }
        }
        else {
            sum_1 = 0;
        }
    }
    std::cout << sum_2 << std::endl;
    return 0;
}