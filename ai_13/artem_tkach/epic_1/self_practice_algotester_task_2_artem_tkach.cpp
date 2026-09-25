// № 40261
#include <iostream>

int main() {
    int lviv, kyiv, donetsk, kharkiv;

    if (std::cin >> lviv >> kyiv >> donetsk >> kharkiv) {
        int total_souvenirs = lviv + kyiv + donetsk + kharkiv;
        std::cout << total_souvenirs << std::endl;
    }

    return 0;
}