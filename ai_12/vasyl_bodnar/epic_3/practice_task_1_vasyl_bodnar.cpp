#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Рекурсивна функція для знаходження суми
double calculateTotalRecursive(double expenses[], int size) {
    if (size == 0) {
        return 0.0;
    }
    return expenses[size - 1] + calculateTotalRecursive(expenses, size - 1);
}

// Пошук мінімуму та максимуму через параметри-посилання
void findExtremes(double expenses[], int size, double& minVal, double& maxVal) {
    minVal = expenses[0];
    maxVal = expenses[0];

    for (int i = 1; i < size; i++) {
        if (expenses[i] < minVal) {
            minVal = expenses[i];
        }
        if (expenses[i] > maxVal) {
            maxVal = expenses[i];
        }
    }
}

// Показуємо витрати по днях з обходом масиву
void displayExpenses(double expenses[], int size) {
    cout << "\n" << left << setw(10) << "День" << "Витрати, грн" << endl;
    for (int i = 0; i < size; i++) {
        cout << right << setw(4) << (i + 1) << setw(17) 
             << fixed << setprecision(2) << expenses[i] << endl;
    }
}

// Статистика витрат
void printStats(double expenses[], int size, double monthlyBudget) {
    double minExpense, maxExpense;
    
    // Отримуємо мінімум та максимум
    findExtremes(expenses, size, minExpense, maxExpense);
    
    // Отримуємо суму рекурсивно
    double totalSpent = calculateTotalRecursive(expenses, size);

    cout << "\nМінімальні витрати за день:       " << fixed << setprecision(2) << minExpense << " грн" << endl;
    cout << "Максимальні витрати за день:   " << maxExpense << " грн" << endl;
    cout << "Сумарні витрати:               " << totalSpent << " грн" << endl;

    // Модуль від'ємного залишку 
    if (totalSpent > monthlyBudget) {
        cout << "Перевитрата понад бюджет:      " << abs(totalSpent - monthlyBudget) << " грн" << endl;
    } else {
        cout << "Залишок бюджету:               " << (monthlyBudget - totalSpent) << " грн" << endl;
    }

    int activeDays = 0;
    double activeDaysSum = 0;

    // Цикл для розрахунку середнього
    for (int i = 0; i < size; i++) {
        if (expenses[i] == 0.0) {
            continue;
        }
        activeDaysSum += expenses[i];
        activeDays++;
    }

    cout << "Днів з покупками:                    " << activeDays << endl;
    if (activeDays > 0) {
        cout << "Середні витрати за такий день: " << (activeDaysSum / activeDays) << " грн" << endl;
    }

    // Пошук дня вичерпання бюджету
    double accumulated = 0;
    int currentDay = 0;
    
    while (currentDay < size) {
        accumulated += expenses[currentDay];
        if (accumulated > monthlyBudget) {
            cout << "Бюджет вичерпано на дні " << (currentDay + 1) 
                 << ", накопичено " << accumulated << " грн." << endl;
            break;
        }
        currentDay++;
    }
    
    if (currentDay == size) {
        cout << "Бюджету вистачило на всі дні обліку." << endl;
    }
}

// 3. Перевищення ліміту
void checkLimit(double expenses[], int size, double threshold = 1000.0) {
    int exceedCount = 0;
    
    cout << "\nЛіміт: " << fixed << setprecision(2) << threshold << " грн" << endl;
    
    for (int i = 0; i < size; i++) {
        if (expenses[i] > threshold) {
            cout << "  день " << (i + 1) << ": " << expenses[i] << " грн" << endl;
            exceedCount++;
        }
    }
    
    cout << "Разом днів з перевищенням: " << exceedCount << endl;
}

// 4. Три найдорожчі дні
void showTopExpenses(double expenses[], int size) {
    double copyArr[31];
    
    // Копіюємо елементи масиву[cite: 8]
    for (int i = 0; i < size; i++) {
        copyArr[i] = expenses[i];
    }

    // Використовуємо вкладені цикли
    for (int i = 0; i < size - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (copyArr[j] > copyArr[maxIndex]) {
                maxIndex = j;
            }
        }
        // Обмін значень
        double temp = copyArr[i];
        copyArr[i] = copyArr[maxIndex];
        copyArr[maxIndex] = temp;
    }

    int topCount = (size < 3) ? size : 3;

    cout << "\nТоп-" << topCount << " витрат: ";
    for (int i = 0; i < topCount; i++) {
        cout << fixed << setprecision(2) << copyArr[i];
        if (i < topCount - 1) {
            cout << ", ";
        }
    }
    cout << " грн" << endl;
}

int main() {
    double monthlyBudget;
    int daysCount;
    double dailyExpenses[31];

    cout << "Бюджет на місяць (грн): ";
    cin >> monthlyBudget;
    
    if (cin.fail() || monthlyBudget < 0) {
        cout << "Некоректний ввід бюджету!" << endl;
        return 1;
    }

    cout << "Кількість днів обліку: ";
    cin >> daysCount;
    
    // Валідація кількості днів
    if (cin.fail() || daysCount < 1 || daysCount > 31) {
        cout << "Помилка! Кількість днів повинна бути від 1 до 31." << endl;
        return 1;
    }

    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < daysCount; i++) {
        cin >> dailyExpenses[i];
        if (cin.fail() || dailyExpenses[i] < 0) {
            cout << "Некоректний ввід витрат!" << endl;
            return 1;
        }
    }

// Мітка для повернення у меню при некоректному вводі
MainMenu: 

    int userChoice;
    
    do {
        cout << "\n===== МЕНЮ =====" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Ваш вибір: ";
        cin >> userChoice;

        // Перевірка на нечислові символи з перенаправленням через goto
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка вводу! Введіть число." << endl;
            goto MainMenu; 
        }

        switch (userChoice) {
            case 1:
                displayExpenses(dailyExpenses, daysCount);
                break;
            case 2:
                printStats(dailyExpenses, daysCount, monthlyBudget);
                break;
            case 3: {
                double customLimit;
                cout << "\nДенний ліміт (грн, 0 = за замовчуванням): ";
                cin >> customLimit;
                
                if (cin.fail() || customLimit < 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Неправильний формат ліміту!" << endl;
                    goto MainMenu;
                }
                
                if (customLimit == 0) {
                    checkLimit(dailyExpenses, daysCount);
                } else {
                    checkLimit(dailyExpenses, daysCount, customLimit);
                }
                break;
            }
            case 4:
                showTopExpenses(dailyExpenses, daysCount);
                break;
            case 0:
                cout << "Завершення програми..." << endl;
                break;
            default:
                cout << "Неправильний пункт меню! Спробуйте ще раз." << endl;
                goto MainMenu;
        }
    } while (userChoice != 0);

    return 0;
}