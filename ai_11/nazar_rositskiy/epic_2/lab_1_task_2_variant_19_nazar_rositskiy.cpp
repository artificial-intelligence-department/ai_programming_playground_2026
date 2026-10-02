#include <iostream>

int main(){
    
    //оголошення n i m
    float n,m;
    
    //введення n i m відповідно
    std::cout << "Enter n: ";
    std::cin >> n;
    std::cout << "Enter m: ";
    std::cin >> m;
    std::cout << m << " " << n << std::endl;
    //послідовне виконання та виведення першої другої та третьої дії відповідно
    std::cout << "1) --m - ++n: " << (--m - ++n) << std::endl;
    std::cout << "2) m*n < n++: " << (m*n < n++) << std::endl;
    std::cout << "3) n-- > m++: " << (n-- > m++) << std::endl;

}