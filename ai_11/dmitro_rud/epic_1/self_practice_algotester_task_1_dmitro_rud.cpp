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

    int x = 0; // кількість гаражів типу a
    int y = 0; // кількість гаражів типу b
    int big_garage = cars / garages[1];
    int targetNumber = garages[1] * big_garage;
    if (targetNumber == cars) {
        std::cout << big_garage << std::endl;
    }
while (targetNumber/garages[1]  >= 0) {  
    int low_number = cars - targetNumber;// кількість машин, які залишилися після заповнення гаражів типу b
    if (low_number % garages[0] == 0) {
        x = low_number / garages[0];
        y = targetNumber / garages[1];
        std::cout << x + y << std::endl;
        return 0;
    } else {
        targetNumber -= garages[1];
    }

}
    std::cout << -1 << std::endl;
    return 0;
}