#include <iostream>
int main() {
    int A, B;
    std:: cin >> A >> B;
    if(A >= 0 && A <= 100 && B >= 0 && B <= 100 ) {
        std :: cout << A + B;
    }
    return 0;
}
