/*
Епік 6. Self Practice: Algotester, задача "Яблука"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
using namespace std;

struct Basket {
    long long apples, price, cheapest;
};

Basket arr[2001];

int main () {

    int n;
    cin >> n;

    for (int i = 0; i<n; i++) cin >> arr[i].apples;

    long long b;
    cin >> b;

    for (int i = 0; i<n; i++) {
        cin >> arr[i].price;
        arr[i].cheapest = arr[i].price;
    }

    long long result = -1;

    for (int i = 0; i<n; i++) {
        long long sum = i*b;
        for (int j = 0; j<n; j++) {
            int k = (j+i) % n;
            if (arr[k].price < arr[j].cheapest) arr[j].cheapest = arr[k].price;
            sum = sum+arr[j].apples * arr[j].cheapest;
        }
        if (result == -1 || sum<result) result = sum;
    }

    cout << result;

    return 0;
}