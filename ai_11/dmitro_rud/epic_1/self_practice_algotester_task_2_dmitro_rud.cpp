#include <iostream>

int main() {
    int n;
    int k;
    std::cout << "";
    std::cin >> n >> k;
    int sertificates;
    int deploms;
    deploms = (n / 2) / (k + 1);
    sertificates = deploms * k;
    int lox = n - (sertificates + deploms);
    std::cout << deploms << " " << sertificates << " " << lox << std::endl;



}
