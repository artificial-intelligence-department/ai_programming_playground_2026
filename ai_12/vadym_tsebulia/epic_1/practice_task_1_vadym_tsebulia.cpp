/* 
Автономність портативної зарядної станції, 
Цебуля Вадим 
СШІ-12
*/


#include <iostream>
#include <cmath>
#include <iomanip>
#include <string> 
int main()
{
        // Введення моделі станції

        std::string name;
        std::cout << "Введіть назву станції: ";
        std::cin >> name;
        if (name.length() > 31)
        {
                std::cout << "Помилка: назва станції повинна бути не довша за 31 символ." << std::endl;
                return 1;
        }

        // Введення паспортної ємності станції Вт·годинах

        double C; // Паспортна ємність (Вт·год)
        std::cout << "Введіть паспортну ємність (Вт·год): ";
        if (!(std::cin >> C))
        {
                std::cout << "Помилка: потрібно ввести число." << std::endl;
                return 1;
        }
        if (C <= 0)
        {
                std::cout << "Помилка: паспортна ємність має бути більшою за 0." << std::endl;
                return 1;
        }
        // Введення віку станції у роках 

        int years; //   Вік станції (років)
        std::cout << "Введіть вік станції (років): ";
        if (!(std::cin >> years))
        {
                std::cout << "Помилка: потрібно ввести число." << std::endl;
                return 1;
        }
        if (years < 0 || years > 20)
        {
                std::cout << "Помилка: вік станції має бути від 0 до 20 років." << std::endl;
                return 1;
        }

        // Введення рівню заряду станції у процентах

        int charge; //  Рівень заряду (%)
        std::cout << "Введіть рівень заряду (%): ";
        if (!(std::cin >> charge))
        {
                std::cout << "Помилка: потрібно ввести число." << std::endl;
                return 1;
        }
        if (charge < 0 || charge > 100)
        {
                std::cout << "Помилка: рівень заряду має бути від 0 до 100." << std::endl;
                return 1;
        }
        // Введення ККД інвертора станції у процентах

        double eff; //   ККД інвертора (%)
        std::cout << "Введіть ККД інвертора (%): ";
        if (!(std::cin >> eff))
        {
                std::cout << "Помилка: потрібно ввести число." << std::endl;
                return 1;
        }
        if (eff <= 0 || eff > 100)
        {
                std::cout << "Помилка: ККД інвертора має бути більше за 0 та не більше за 100." << std::endl;
                return 1;
        }
        // Введення потужності приладу станції (Вт)

        double P; //     Потужність приладу
        std::cout << "Введіть потужність приладу (Вт): ";
        if (!(std::cin >> P))
        {
                std::cout << "Помилка: потрібно ввести число." << std::endl;
                return 1;
        }
        if (P <= 0)
        {
                std::cout << "Помилка: потужність повинна бути більша за 0." << std::endl;
                return 1;
        }

        const double degradation = 2.0; // 2.0 - це відсоток втрати ємності на рік;

        // Обчислення фактичної ємності станції з врахуванням зносу у Вт·год
        double C_eff = C * std::pow(1 - degradation / 100, years); // 100 - переведення відсотків у частку

        // Обчислення запасу енергії у Вт·год
        double E_stored = C_eff * charge / 100; 

        // Обчислення корисної енергії у Вт·год
        double E_useful = E_stored * eff / 100; 

        // Обчислення втрат на перетворенні напруги у Вт·год
        double E_loss = E_stored - E_useful;

        // Обчислення часу роботи у годинах
        double T = E_useful / P;

        // Повні години : присвоєння double в int відкидає дробову частину
        int h = T;

        // Залишок годин переводимо у хвилини, дробову частину знову відкидаємо
        int m = (T - h) * 60;

        //Виведення результатів
        std::cout << "Модель: " << std::setw(29) << name << std::endl;
        std::cout << std::fixed << std::setprecision(1) << "Паспортна ємність: " << std::setw(18) << C << " Вт·год" << std::endl;
        std::cout << "Вік станції: " << std::setw(24) << years << " р." << std::endl;
        std::cout << std::setprecision(1) << "Фактична ємність: " << std::setw(19) << C_eff << " Вт·год" << std::endl;
        std::cout << "Рівень заряду: " << std::setw(22) << charge << " %" << std::endl;
        std::cout << std::setprecision(2) << "ККД інвертора: " << std::setw(22) << eff << " %" << std::endl;
        std::cout << std::setprecision(1) << "Запас енергії: " << std::setw(22) << E_stored << " Вт·год" << std::endl;
        std::cout << std::setprecision(1) << "Корисна енергія: " << std::setw(20) << E_useful << " Вт·год" << std::endl;
        std::cout << std::setprecision(1) << "Втрати на перетворенні: " << std::setw(13) << E_loss << " Вт·год" << std::endl;
        std::cout << std::setprecision(2) << "Час роботи: " << std::setw(25) << T << " год = ";
        std::cout << h << " год ";
        std::cout << std::setfill('0') << std::setw(2) << m << " хв" << std::endl;
        return 0;
}