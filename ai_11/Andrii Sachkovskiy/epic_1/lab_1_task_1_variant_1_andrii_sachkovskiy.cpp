/*
 * Задача: Автономність портативної зарядної станції
 * Автор: Сачковський Андрій
 * Група: AI-11
 */
#include <iostream> //бібліотеки
#include <locale>
#include <cmath>
#include <string>
#include <iomanip>
/*Сталі:  31 - максимальна довжина моделі станції
20 -максимально допустимий вік станції (років)
100 межа допустимого рівня заряду (%)
2 - відсоток втрати ємності акумулятора за рік
100 - переведення відсотка деградації у частку (2% → 0.02)
60 - переведення дробової частини години у хвилини
100 -переведення ККД інвертора з відсотків у частку
100 -переведення рівня заряду з відсотків у частку */
int main(){

    using namespace std; //ведення назви моделі
    std::string model; 
    std::setlocale(LC_ALL, "");
std::cout << "Введіть модель станції: " ; 
     std::getline(std::cin, model);
    if (model.length()   > 31){
        std::cout << "Помилка: довжина моделі станції не повинна перевищувати 31 символ." << std::endl;
        return 1;
    }
    
    float capacity; // введення паспортної ємності оримання даних від користовача
   std::cout <<"Паспортна ємність, Вт·год: " ;

   std::cin >> capacity; 
if (std::cin.fail()){ 
    std::cout << "Помилка: некоректне значення." << std::endl;
    return 1;
}
   if (capacity <= 0){
std::cout << "Паспортна ємність мусить бути більше 0" << std::endl;
 return 1; 
}
//ведення віку станції
   int years;
std:: cout <<"Вік станції, років: " ;
std::cin >>years; 
 
if (std::cin.fail()){ 
    std::cout << "Помилка: некоректне значення." << std::endl;
    return 1;
}
if (years < 0 || years > 20){ 
    std::cout << "Вік станції мусить бути від 0 до 20." << std::endl;
    return 1; 
}
//ведення рівня заряду
 float  charge_level;
std:: cout <<"Рівень заряду, %: " ;
std::cin >> charge_level; // введення рівня заряду оримання даних від користовача
if (std::cin.fail()){ 
    std::cout << "Помилка: некоректне значення." << std::endl;
    return 1;
}

if (charge_level < 0 || charge_level > 100) {
 std::cout << "рівень заряду мусить бути від 0 до 100 " << std::endl;
 return 1; 
}
//ведення ККД інвертора
float efficiency;
std:: cout <<"ККД інвертора, %: " ;
std::cin >> efficiency; // введення ККД інвертора оримання даних від користовача
if (std::cin.fail()){ 
    std::cout << "Помилка: некоректне значення." << std::endl;
    return 1;
}
if (efficiency <= 0 || efficiency >  100) {// межа допустимого ККД інвертора (%)
std::cout <<"ККД інвестора мусить бути від 0% - 100% "<<std::endl;
 return 1; 
}
//ведення потужності приладу=
 int power; 
std:: cout <<"Потужність, Вт: " ;
std::cin >> power; // введення потужності оримання даних від користовача
if (std::cin.fail()){ 
    std::cout << "Помилка: некоректне значення." << std::endl;
    return 1;
}
if (power <= 0)	{
std::cout <<"Потужність повина бути більше 0 "<<std::endl;
 return 1;
} 
// Обчислення всіх отриманих даних за формулами:

float actual_capacity; 
 //Формула фактична ємність з урахуванням віку, Вт·год
actual_capacity = capacity * pow(1 - 2.0/100, years);


float energy ; // Запас енергії при поточному заряді, Вт·год
energy = actual_capacity * charge_level / 100; 

float E_useful; // Корисна енергія, що дійде до приладу, Вт·год
E_useful = energy * efficiency / 100;

float E_loss; // Втрати на перетворенні напруги, Вт·год
E_loss = energy - E_useful;

float time; // Час роботи приладу, год
time = E_useful / power;

int hours; // години цілі 
hours = (int)time;


int minutes; // залишок хвилин
minutes = (int)((time - hours) * 60);
        // Виведення результатів обчислень на екран з форматуванням
std::cout << std::left << std::setw(35)
          << "Модель:"
          << model << std::endl;

std::cout << std::left << std::setw(45)
          << "Паспортна ємність:"
          << std::fixed << std::setprecision(1)
          << capacity << " Вт·год" << std::endl;

std::cout << std::left << std::setw(39)
          << "Вік станції:"
          << years << " р." << std::endl;

std::cout << std::left << std::setw(44)
          << "Фактична ємність:"
          << std::fixed << std::setprecision(1)
          << actual_capacity << " Вт·год" << std::endl;

std::cout << std::left << std::setw(41)
          << "Рівень заряду:"
          << std::fixed << std::setprecision(2)
          << charge_level << " %" << std::endl;

std::cout << std::left << std::setw(41)
          << "ККД інвертора:"
          << std::fixed << std::setprecision(2)
          << efficiency << " %" << std::endl;

std::cout << std::left << std::setw(41)
          << "Запас енергії:"
          << std::fixed << std::setprecision(1)
          << energy << " Вт·год" << std::endl;

std::cout << std::left << std::setw(43)
          << "Корисна енергія:" 
          << std::fixed << std::setprecision(1)
          << E_useful << " Вт·год" << std::endl;

std::cout << std::left << std::setw(49)
          << "Втрати на перетворенні:"
          << std::fixed << std::setprecision(1)
          << E_loss << " Вт·год" << std::endl;

std::cout << std::left << std::setw(38)
          << "Час роботи:"
          << hours<< " год  " 
          <<" "
          << minutes << " хв "
          << std::endl;
          
}// 
