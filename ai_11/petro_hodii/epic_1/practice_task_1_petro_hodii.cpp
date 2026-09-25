/*  
Автономність портативної зарядної станції
Годій Петро
Група: ШІ-11
*/
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

int main() {
    //задаю сталі
    const double degradation_per_year = 2.0;//деградація ємності батареї

    //задаю змінні
    std::string name; //назва
    double C; //паспортна ємність
    int years; //вік
    int charge; //заряд
    double eff; //ККД
    double P; //потужність

    //отримую значення від користувача і перевіряю обмеження
    std::cout << "Модель станції: ";
    std::cin >> name;
    if(name.length() > 31){
        std::cout << "Помилка: назва має бути не довше 31 символа\n";
        return 1;
    }

    std::cout << "Паспортна ємність (Вт·год): ";
    std::cin >> C;
    if(C<=0.){
        std::cout << "Помилка: паспортна ємність має бути більше 0\n";
        return 1;
    }

    std::cout << "Вік станції (років): ";
    std::cin >> years;
    if(years < 0 || years > 20){
        std::cout << "Помилка: вік станції має бути від 0 до 20\n";
        return 1;
    }

    std::cout << "Рівень заряду (%): ";
    std::cin >> charge;
    if(charge < 0 || charge > 100){
        std::cout << "Помилка: рівень заряду має бути від 0 до 100\n";
        return 1;
    }

    std::cout << "ККД інвертора (%): ";
    std::cin >> eff;
    if(eff <= 0. || eff > 100.){
        std::cout << "Помилка: ККД інвентора має бути більше 0 і не більше 100\n";
        return 1;
    }

    std::cout << "Потужність приладу (Вт): ";
    std::cin >> P;
    if(P<=0.){
        std::cout << "Помилка: потужність приладу має бути більше 0\n";
        return 1;
    }

    //обчислюю певні значення
    double C_eff = C * std::pow(1.0 - degradation_per_year/100.0, years);
    double E_stored = C_eff * charge / 100.0;
    double E_useful = E_stored * eff / 100.0;
    double E_loss = E_stored - E_useful;
    double T = E_useful / P;
    int h = int(T);
    int m = int((T - h) * 60.0);

    //виводжу результат
    std::cout << "Модель:                 " << name << std::endl;
    std::cout << "Паспортна ємність:      " << std::fixed << std::setprecision(1) << C << " Вт·год" << std::endl;
    std::cout << "Вік станції:            " << years << " р." << std::endl;
    std::cout << "Фактична ємність:       " << std::fixed << std::setprecision(1) << C_eff << " Вт·год" << std::endl;
    std::cout << "Рівень заряду:          " << charge << " %" << std::endl;
    std::cout << "ККД інвертора:          " << std::fixed << std::setprecision(2) << eff << " %" << std::endl;  
    std::cout << "Запас енергії:          " << std::fixed << std::setprecision(1) << E_stored << " Вт·год" << std::endl;
    std::cout << "Корисна енергія:        " << std::fixed << std::setprecision(1) << E_useful << " Вт·год" << std::endl;
    std::cout << "Втрати на перетворенні: " << std::fixed << std::setprecision(1) << E_loss << " Вт·год" << std::endl;
    std::cout << "Час роботи:             " << std::fixed << std::setprecision(2) << T << " год" << " = " << h << " год " << std::right << std::setfill('0') << std::setw(2) << m << " хв " << std::endl;



    return 0;
}
