/* 
Завдання 2, лабараторна робота 1
Белаш Матвій Валерійович
ШІ-12
*/
#include <iostream>
 
int main() {

    int m;
    int n;

    std::cout << "Please, enter m: ";
    std::cin >> m;
    std::cout << "Please, enter n: ";
    std::cin >> n;
    
    int a1 = -(-m);
    int b1 = n+1;
    int r1 = a1 - b1;

    int a2 = m * n;
    int b2 = n+1;
    bool r2;
    if (a2 < b2){
        r2= true;
    } else {
        r2= false;
    }

    int a3 = n-1;
    int b3 = m+1;
    bool r3;
    if (a3 > b3) {
        r3= true;
    } else {
        r3= false;
    }

    std::cout << "1)" << r1 << std::endl;
    std::cout << "2)" << (r2 ? "true" : "false") << std::endl;
    std::cout << "3)" << (r3 ? "true" : "false") << std::endl;

    return 0;
}