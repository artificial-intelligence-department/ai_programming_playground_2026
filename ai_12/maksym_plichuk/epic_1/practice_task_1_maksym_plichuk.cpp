/*Автономність портативної зарядної станції
        Плічук Максим
        ШІ - 12*/
#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{ 
    // встановив локалцізаію
    setlocale(LC_ALL, "uk_UA");

    std::string name;
    int c;
    int years;
    int charge;
    double eff;
    double p;

    std::cout << "Модель станції: ";
    std::cin >> name;

    if (!(name.length() > 0 && name.length() <= 31))
    {
        std::cout << "Назва має бути від 1 до 31 символів" << std::endl;
        return 1;
    }

    std::cout << "Паспортна ємність (Вт·год): ";
    // перевіряємо, чи введене значення є числом
    if (!(std::cin >> c))
    {
        std::cout << "Ємність має бути числом" << std::endl;
        return 1;
    }
    else if (!(c > 0))
    {
        std::cout << "Ємність має бути > 0" << std::endl;
        return 1;
    }

    std::cout << "Вік станції (років): ";
    if (!(std::cin >> years))
    {
        std::cout << "Вік має бути числом" << std::endl;
        return 1;
    }
    else if (!(years >= 0 && years <= 20))
    {
        std::cout << "Вік має бути від 0 до 20" << std::endl;
        return 1;
    }

    std::cout << "Рівень заряду (%): ";
    if (!(std::cin >> charge))
    {
        std::cout << "Рівень заряду має бути числом" << std::endl;
        return 1;
    }
    else if (!(charge >= 0 && charge <= 100))
    {
        std::cout << "Рівень заряду має бути від 0 до 100" << std::endl;
        return 1;
    }

    std::cout << "ККД інвертора (%): ";
    if (!(std::cin >> eff))
    {
        std::cout << "ККД інвертора має бути числом" << std::endl;
        return 1;
    }
    else if (!(eff > 0 && eff <= 100))
    {
        std::cout << "ККД інвертора має бути від 0 до 100" << std::endl;
        return 1;
    }

    std::cout << "Потужність приладу (Вт): ";
    if (!(std::cin >> p))
    {
        std::cout << "Потужність приладу має бути числом" << std::endl;
        return 1;
    }
    else if (!(p > 0))
    {
        std::cout << "Потужність приладу має бути > 0" << std::endl;
        return 1;
    }

    // обчислюємо фактичну ємність з урахуванням деградації 2% на рік
    double C_eff = c * std::pow((1 - 2 / 100), years);

    // обчсилюємо запас енергії відповідно до поточного рівня заряду
    double E_stored = C_eff * charge / 100;

    // обчислємо корисну енергію після втрат в інверторі
    double E_useful = E_stored * eff / 100;

    // обчислємо втрати енергії під час перетворення напруги
    double E_loss = E_stored - E_useful;

    // обчислюємо час роботи приладу в годинах
    double T = E_useful / p;

    // виділяємо повні години з часу роботи
    int h = (int) T;

    // виділяємо хвилини, що залишилися після повних годин
    int m = int((T - h) * 60);

    // Виводимо результати з потрібною точністю
    std::cout << std::fixed << std::setprecision(1);

    std::cout << "\nМодель:                 " << name << std::endl;
    std::cout << "Паспортна ємність:           " << c << " Вт·год" << std::endl;
    std::cout << "Вік станції:                  " << years << " р." << std::endl;
    std::cout << "Фактична ємність:            " << C_eff << " Вт·год" << std::endl;
    std::cout << "Рівень заряду:                 " << charge << " %" << std::endl;

    std::cout << std::setprecision(2);
    std::cout << "ККД інвертора:               " << eff << " %" << std::endl;

    std::cout << std::setprecision(1);
    std::cout << "Запас енергії:               " << E_stored << " Вт·год" << std::endl;
    std::cout << "Корисна енергія:             " << E_useful << " Вт·год" << std::endl;
    std::cout << "Втрати на перетворенні:      " << E_loss << " Вт·год" << std::endl;

    std::cout << std::setprecision(2);
    std::cout << "Час роботи:                   " << T << " год = ";

    std::cout << h << " год " << std::setfill('0') << std::setw(2) << m << " хв" << std::endl;

    return 0;
}