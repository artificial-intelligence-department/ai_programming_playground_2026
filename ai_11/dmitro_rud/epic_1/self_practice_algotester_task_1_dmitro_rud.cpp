#include<iostream>
#include<string>
#include<vector>
#include <algorithm>


int main() {
    int cars, a, b;
    std::cout << "";
    std::cin >> cars >> a >> b;

    if (std::cin.fail()) {
        std::cout << "Помилка: введено не число." << std::endl;
        exit(0);
    }

    if (cars < 0|| a < 0 || b < 0) {
        exit(0);
    }
    std::vector<int> garages = {a , b};
    std::sort(garages.begin(), garages.end());

    long long x = 0; // кількість гаражів типу a
    long long y = 0; // кількість гаражів типу b
    long long big_garage = cars / garages[1];
    long long big_garages_size = garages[1] * big_garage;// кількість машин, які можна розмістити в гаражах типу b
    if (big_garages_size == cars) {
        std::cout << big_garage << std::endl;
        return 0;
    }
while (big_garages_size/garages[1]  >= 0) {  
    long long small_garages_size = cars - big_garages_size;// кількість машин, які залишилися після заповнення гаражів типу b
    if (small_garages_size % garages[0] == 0) {
        x = small_garages_size / garages[0];
        y = big_garages_size / garages[1];
        std::cout << x + y << std::endl;
        return 0;
    } else {
        big_garages_size -= garages[1];
    }

}
    std::cout << -1 << std::endl;
    return 0;
}

