#include <iostream>

using namespace std;

int main() {
    long long n, k;
    cin >> n >> k;
    
    long long maxWinners = n / 2; // максимальна кількість переможців
    long long diplomas = maxWinners / (k + 1); // дипломів d, сертифікатів k*d, переможців d*(k+1) <= maxWinners
    long long certificates = diplomas * k;
    long long nothing = n - diplomas - certificates;   // решта студентів без нагород

    cout << diplomas << " " << certificates << " " << nothing << endl;
    return 0;
}