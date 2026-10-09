#include <iostream>

int main(){
    
    //оголошення n i m
    float n,m;
    float a,b;
    
    //введення n i m відповідно
    std::cout << "Enter n: ";
    std::cin >> n;
    std::cout << "Enter m: ";
    std::cin >> m;
    std::cout << m << " " << n << std::endl;
    a=n;
    b=m;
    //послідовне виконання та виведення першої другої та третьої дії відповідно
    a=n;
    b=m;
    std::cout << "1) --m - ++n: " << (--b - ++a) << std::endl;
    a=n;
    b=m;
    std::cout << "2) m*n < n++: " << (b*a < a++) << std::endl;
    a=n;
    b=m;
    std::cout << "3) n-- > m++: " << (a-- > b++) << std::endl;

}