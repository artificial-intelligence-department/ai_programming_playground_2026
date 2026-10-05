#include <iostream>

int main() {
    //Ввід даних
    int password_lenght{};
    std::cout << "Довжина пароля: ";
    std::cin >> password_lenght;
    if (password_lenght < 1 || password_lenght > 64) {
        std::cout << "Довжина пароля це число від 1 до 64";
        return 1;
    }

    char inp_consists_numbers{};
    std::cout << "Чи є цифри? (y/n): ";
    std::cin >> inp_consists_numbers;
    if (inp_consists_numbers != 'y' && inp_consists_numbers != 'n') {
        std::cout << "Ви повинні ввести y або n";
        return 1;
    }
    bool consist_numbers = inp_consists_numbers == 'y' ? true : false;

    char inp_consists_big_letters{};
    std::cout << "Чи є великі літери? (y/n): ";
    std::cin >> inp_consists_big_letters;
    if (inp_consists_big_letters != 'y' && inp_consists_big_letters != 'n') {
        std::cout << "Ви повинні ввести y або n";
        return 1;
    }
    bool consist_big_letters = inp_consists_big_letters == 'y' ? true : false;

    char inp_consists_special_characters{};
    std::cout << "Чи є спецілаьні символи? (y/n): ";
    std::cin >> inp_consists_special_characters;
    if (inp_consists_special_characters != 'y' && inp_consists_special_characters != 'n') {
        std::cout << "Ви повинні ввести y або n";
        return 1;
    }
    bool consist_special_characters = inp_consists_special_characters == 'y' ? true : false;

    std::cout << std::endl;

    //кількість різних типів сиволів
    int types_of_characters = consist_numbers + consist_big_letters + consist_special_characters;

    //Перевірка на мінімальні умови
    std::cout << "Мінімальні вимоги: ";
    if (password_lenght >= 8 && types_of_characters >= 2) {
        std::cout << "ПРОЙДЕНО" << std::endl;
    } else {
        std::cout << "НЕ ПРОЙДЕНО" << std::endl;
    }

    //Рівень надійності
    int level{};
    std::cout << "Рівень надійності: ";
    if (password_lenght < 6) {
        level = 1;
        std::cout << "1 - Дуже слабкий" << std::endl;
    } else if (password_lenght < 8 || types_of_characters == 0) {
        level = 2;
        std::cout << "2 - Слабкий" << std::endl;
    } else if (types_of_characters == 1) {
        level = 3;
        std::cout << "3 - Середній" << std::endl;
    } else if (password_lenght < 12 || types_of_characters < 3) {
        level = 4;
        std::cout << "4 - Надійний" << std::endl;
    } else {
        level = 5;
        std::cout << "5 - Дуже надійний" << std::endl;
    }

    std::cout << "Рекомендація: ";
    switch (level)
    {
    case 1:
        std::cout << "Пароль надто короткий. Мінімум 8 символів." << std::endl;
        break;

    case 2:
        std::cout << "Збільште довжину до 8+ символів і додайте цифри," <<
                     "великі літери або спеціальні символи." << std::endl;
        break;

    case 3:
        std::cout << "Додайте ще один тип символів або збільште довжину до 12." << std::endl;
        break;

    case 4:
        std::cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів."
                  << std::endl;
        break;

    case 5:
        std::cout << "Відмінно. Змінювати нічого не потрібно." << std::endl;
        break;

    default:
        std::cout << "Неправильне значення level.";
        break;
    }



    return 0;
}