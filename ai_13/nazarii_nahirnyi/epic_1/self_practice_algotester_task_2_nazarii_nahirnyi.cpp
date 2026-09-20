#include <iostream>
using namespace std;

int main() {
    long long n;
    if (!(cin >> n) || n < 1 || n > 1000000000) {
        cout << "Помилка: n має бути цілим числом від 1 до 1000000000.\n";
        return 1;
    }

    int nominals[9] = {500, 200, 100, 50, 20, 10, 5, 2, 1};

    long long count = 0;  

    for (int i = 0; i < 9; i++) {
        count += n / nominals[i];  
        n = n % nominals[i];      
    }

    cout << count << "\n";
    return 0;
}
