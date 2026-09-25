/*
 * Epic_1 self practice Algotester task "Marichka and cookies"
 * semen_honcharenko
 * ai_11
 */
#include <iostream>

int main() {
    int n; 
    std::cin >> n; // packs of cookies quantity input
    long long can_eat = 0; // long long for giant numbers
    
    for ( int i = 0; i < n; i++) {
        long long a;
        std::cin >> a;
        can_eat += ( a - 1 );
    }

    std::cout << can_eat << std::endl;

    return 0;
}
