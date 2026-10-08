/*
    Лабораторна робота 1. Алготестер. Варіант 2.
    Гончаренко Семен
    ШІ-11
*/
#include <iostream> // input, output library
#include <algorithm> // min(), max() library
#include <cstdlib> // exit() library

int main() {
    //introducing variables
    long long h1 = 0;
    long long h2 = 0;
    long long h3 = 0;
    long long h4 = 0;

    long long d1 = 0;
    long long d2 = 0;
    long long d3 = 0;
    long long d4 = 0;
    //"table flipped?" variable (yes or no)
    bool flip = 0;

    std::cin >> h1;
    std::cin >> h2;
    std::cin >> h3;
    std::cin >> h4;

    std::cin >> d1;
    std::cin >> d2;
    std::cin >> d3;
    std::cin >> d4;

    h1 = h1 - d1;
    long long min_h = std::min({h1, h2, h3, h4});
    long long max_h = std::max({h1, h2, h3, h4});
    if ( max_h >= min_h*2 and h1>0 and h2>0 and h3>0 and h4>0 ) {
        flip = 1;
    }
    if ( h1 < 0 or h2 < 0 or h3 < 0 or h4 < 0 ) {
        std::cout << "ERROR" << std::endl;
        std::exit(0);
    }
    h2 = h2 - d2;
    min_h = std::min({h1, h2, h3, h4});
    max_h = std::max({h1, h2, h3, h4});
    if ( max_h >= min_h*2 and h1>0 and h2>0 and h3>0 and h4>0 ) {
        flip = 1;
    }
    if ( h1 < 0 or h2 < 0 or h3 < 0 or h4 < 0 ) {
        std::cout << "ERROR" << std::endl;
        std::exit(0);
    }
    h3 = h3 - d3;
    min_h = std::min({h1, h2, h3, h4});
    max_h = std::max({h1, h2, h3, h4});
    if ( max_h >= min_h*2 and h1>0 and h2>0 and h3>0 and h4>0 ) {
        flip = 1;
    }
    if ( h1 < 0 or h2 < 0 or h3 < 0 or h4 < 0 ) {
        std::cout << "ERROR" << std::endl;
        std::exit(0);
    }
    h4 = h4 - d4;
    min_h = std::min({h1, h2, h3, h4});
    max_h = std::max({h1, h2, h3, h4});
    if ( max_h >= min_h*2 and h1>0 and h2>0 and h3>0 and h4>0 ) {
        flip = 1;
    }
    if ( h1 < 0 or h2 < 0 or h3 < 0 or h4 < 0 ) {
        std::cout << "ERROR" << std::endl;
        std::exit(0);
    }

    min_h = std::min({h1, h2, h3, h4});
    max_h = std::max({h1, h2, h3, h4});
    
    if ( flip == 0 and min_h != 0 and h1 == h2 and h2 == h3 and h3 == h4 ) {
        std::cout << "YES" << std::endl;
        return 0;
    }
    if ( flip == 1 ) {
        std::cout << "NO" << std::endl;
        std::exit(0);
    }
    else { 
        std::cout << "NO" << std::endl;
        return 0;
    }
    return 0;
}