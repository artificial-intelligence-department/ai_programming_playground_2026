#include<iostream>
#include <string>
#include <iomanip> // Обязательно для setprecision и fixed
int main(){
    float C = 1.56;
    std::cout << std::fixed << std::setprecision(1)  << "Паспортна ємність: " << C << " Вт·год" << std::endl;
}