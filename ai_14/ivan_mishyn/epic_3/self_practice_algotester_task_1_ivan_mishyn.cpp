#include <iostream>

using namespace std;

int main() {
    string d;
    long long n;
    cin >> d >> n;

    string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    // пошук який день
    int start = 0;
    for (int i = 0; i < 7; i++) {
        if (days[i] == d) {
            start = i;
            break;
        }
    }

    // кожен день буде n/7 разів
    long long ans[7];
    for (int i = 0; i < 7; i++) {
        ans[i] = n / 7;
    }

    // залишок ділик між іншими починаючи з сьогодні
    int rem = n % 7;
    for (int i = 0; i < rem; i++) {
        ans[(start + i) % 7]++;
    }

    // Вивід
    for (int i = 0; i < 7; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}