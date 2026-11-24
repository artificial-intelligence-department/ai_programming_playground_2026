/*
    Задача: Яблука
    Михайловська Анна
    ШІ-14
*/

#include <iostream>
using namespace std;

struct Basket {long long apples, price, cheapest;};

Basket a[2005];

int main() {
    int n;
    long long b;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i].apples;

    cin >> b;

    for (int i = 0; i < n; i++) {
        cin >> a[i].price;
        a[i].cheapest = a[i].price;
    }

    long long answer = -1;

    for (int k = 0; k < n; k++) {
        long long sum = k * b;

        for (int i = 0; i < n; i++) {
            int j = (i + k) % n;

            if (a[j].price < a[i].cheapest)
                a[i].cheapest = a[j].price;

            sum = sum + a[i].apples * a[i].cheapest;
        }

        if (answer == -1 || sum < answer)
            answer = sum;
    }

    cout << answer;
    return 0;
}