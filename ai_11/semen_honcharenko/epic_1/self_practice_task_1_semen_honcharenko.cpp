/*
 * Epic_1 self practice Algotester task "A+B"
 * semen_honcharenko
 * ai_11
 */

 #include <iostream>

int main() {
    int a;
    int b;
    std::cin >> a;
    std::cin >> b;

    if ( a < 0 || a > 100) {
        return 1;
    }
    if ( b < 0 || b > 100) {
        return 1;
    }

    std::cout << a + b << std::endl;

}
