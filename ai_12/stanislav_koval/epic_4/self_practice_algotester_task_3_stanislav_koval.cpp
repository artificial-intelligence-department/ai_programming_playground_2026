/*
Алготестер Щасливий результат
Станіслав Коваль
ШІ-12
*/

#include <iostream>
using namespace std;

int main() {
    int x;
    cin >> x;
    int z;
    int count=0;
    while(x>1) {
        z=x%10;
        x=x/10;
        if (z == 4 || z == 7){
            count++;
        }
    }
    cout << count;
    return 0;
}