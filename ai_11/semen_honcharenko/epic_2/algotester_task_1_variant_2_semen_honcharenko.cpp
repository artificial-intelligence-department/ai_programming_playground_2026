/*
    Лабораторна робота 1. Алготестер. Варіант 2.
    Гончаренко Семен
    ШІ-11
*/
#include <iostream> // input, output library

long long get_min(long long h1, long long h2, long long h3, long long h4) {
    long long min = h1;
    if (h2 < min) {
        min = h2;
    }
    if (h3 < min) {
        min = h3;
    }
    if (h4 < min) {
        min = h4;
    }
    return min;
}
long long get_max(long long h1, long long h2, long long h3, long long h4) {
    long long max = h1;
    if (h2 > max) {
        max = h2;
    }
    if (h3 > max) {
        max = h3;
    }
    if (h4 > max) {
        max = h4;
    }
    return max;
}

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

    std::cin >> h1 >> h2 >> h3 >> h4;

    std::cin >> d1 >> d2 >> d3 >> d4;

    h1 = h1 - d1;
    long long min_h = get_min(h1, h2, h3, h4);
    long long max_h = get_max(h1, h2, h3, h4);
    if ( max_h >= min_h*2 and h1>0 and h2>0 and h3>0 and h4>0 ) {
        flip = 1;
    }
    if ( h1 < 0 or h2 < 0 or h3 < 0 or h4 < 0 ) {
        std::cout << "ERROR" << std::endl;
        return 0;
    }
    h2 = h2 - d2;
    min_h = get_min(h1, h2, h3, h4);
    max_h = get_max(h1, h2, h3, h4);
    if ( max_h >= min_h*2 and h1>0 and h2>0 and h3>0 and h4>0 ) {
        flip = 1;
    }
    if ( h1 < 0 or h2 < 0 or h3 < 0 or h4 < 0 ) {
        std::cout << "ERROR" << std::endl;
        return 0;
    }
    h3 = h3 - d3;
    min_h = get_min(h1, h2, h3, h4);
    max_h = get_max(h1, h2, h3, h4);
    if ( max_h >= min_h*2 and h1>0 and h2>0 and h3>0 and h4>0 ) {
        flip = 1;
    }
    if ( h1 < 0 or h2 < 0 or h3 < 0 or h4 < 0 ) {
        std::cout << "ERROR" << std::endl;
        return 0;
    }
    h4 = h4 - d4;
    min_h = get_min(h1, h2, h3, h4);
    max_h = get_max(h1, h2, h3, h4);
    if ( max_h >= min_h*2 and h1>0 and h2>0 and h3>0 and h4>0 ) {
        flip = 1;
    }
    if ( h1 < 0 or h2 < 0 or h3 < 0 or h4 < 0 ) {
        std::cout << "ERROR" << std::endl;
        return 0;
    }

    min_h = get_min(h1, h2, h3, h4);
    max_h = get_max(h1, h2, h3, h4);
    
    if ( flip == 0 and min_h != 0 and h1 == h2 and h2 == h3 and h3 == h4 ) {
        std::cout << "YES" << std::endl;
        return 0;
    }
    if ( flip == 1 ) {
        std::cout << "NO" << std::endl;
        return 0;
    }
    else { 
        std::cout << "NO" << std::endl;
        return 0;
    }
    return 0;
}