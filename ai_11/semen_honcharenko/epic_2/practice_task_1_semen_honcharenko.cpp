/*
    Практичне завдання
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>

int main() {
    int length = 0;
    char numbers = 0;
    char big = 0;
    char special = 0;
    int choice = 0;
    int types = 0;
    
    std::cout << "Довжина пароля: ";
    std::cin >> length;
    std::cout << "Чи є цифри (y/n): ";
    std::cin >> numbers;
    std::cout << "Чи є великі літери (y/n): ";
    std::cin >> big;
    std::cout << "Чи є спеціальні символи (y/n): ";
    std::cin >> special;
    std::cout << " " << std::endl;
    
    if (length < 1 or length > 64) {
        std::cout << "Помилка: Довжина мусить бути від 1 до 64." << std::endl;
        return 1;
    }
    if ((numbers !='y' and numbers !='n') or (big !='y' and big !='n') or (special !='y' and special !='n')) {
        std::cout << "Помилка: Відповідь повинна бути y або n." << std::endl;
        return 1;
    }
    if (numbers == 'y') {
        types++;
    }
    if (big == 'y') {
        types++;
    }
    if (special == 'y') {
        types++;
    }
    if (length < 6) {
        choice = 1;
    }
    else if (length < 8 or types == 0) {
        choice = 2;
    }
    else if (types == 1) {
        choice = 3;
    }
    else if (length >= 12 and types == 3) {
        choice = 5;
    }
    else {
        choice = 4;
    }
    
    if (length >= 8 and types >= 2) {
    std::cout << "Мінімальні вимоги: ПРОЙДЕНО" << std::endl;
    }
    else {
    std::cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << std::endl;
    }
    
    switch (choice) {
        case 1:
            std::cout << "Рівень надійності: 1 - Дуже слабкий" << std::endl;
            std::cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << std::endl;
            break;
        case 2:
            std::cout << "Рівень надійності: 2 - Слабкий" << std::endl;
            std::cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << std::endl;
            break;
        case 3:
            std::cout << "Рівень надійності: 3 - Середній" << std::endl;
            std::cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << std::endl;
            break;
        case 4:
            std::cout << "Рівень надійності: 4 - Надійний" << std::endl;
            std::cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << std::endl;
            break;
        case 5:
            std::cout << "Рівень надійності: 5 - Дуже надійний" << std::endl;
            std::cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << std::endl;
            break;
        default:
            std::cout << "Помилка виконання програми" << std::endl;
            break;
    }
    if (numbers == 'n' and special == 'n') {
        std::cout << "Попередження: Пароль тільки з літер підбирається швидше." << std::endl;
    }
    return 0;
}