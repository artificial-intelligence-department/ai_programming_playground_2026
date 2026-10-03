#include <iostream>
using namespace std;

int main(){
    int n;
    int m;
    
    cout << "Ввведіть значення n: " << endl;
    cin >> n;
    cout << "Введіть значення m: " << endl;
    cin >> m;
    int step1 = ++n * ++m;
    int step2 = m++ < n;
    int step3 = n++ > m;

    cout << "Операція 1 (""++n * ++m""): " << step1 << endl;
    cout << "Операція 2 (""m++ < n""): " << step2 << endl;
    cout << "Операція 3 (""n++ > n""): " << step3 << endl;

    return 0;
} 