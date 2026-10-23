#include <iostream>

//Функція що виводить меню
int _menu(){
    //мітка goto
    invalidOption:
    //ініціалізація answear
    int answear;
    //виведення меню
    std::cout << std::endl;
    std::cout << "1   Показати витрати по днях" << std::endl;
    std::cout << "2   Статистика витрат" << std::endl;
    std::cout << "3   Дні з перевищенням денного ліміту" << std::endl;
    std::cout << "4   Три найдорожчі дні" << std::endl;
    std::cout << "0   Вийти" << std::endl;
    //відпоівідь
    std::cin >> answear;
    //перевірка на помилку і виведення ще раз за потреби
    if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        goto invalidOption;
    }  
    //повернення відповіді
    return answear;
}

//Функція що повертає найменше значення
void _findMinMax(int N, float spending[], float &minVal, float &maxVal) {
    if (N <= 0) return;
    minVal = spending[0];
    maxVal = spending[0];
    //Цикл що знаходить мінімальне та максимальне значення
    for (int i = 1; i < N; i++) {
        if (spending[i] < minVal) {
            minVal = spending[i];
        }
        if (spending[i] > maxVal) {
            maxVal = spending[i];
        }
    }
}

//Функція що рекурсивно знаходить суму витрат
float _CountSum(int N, float spending[], float sum, int i){
    if (i < N){
        return _CountSum(N, spending, sum + spending[i], i + 1);
    } else {
        return sum;
    }
}

//Функція що виводить 1-й пункт меню
void _menu1(int N, float spending[]){
    std::cout << "День     Витрати, грн" << std::endl;
    //Так що виводить витрати по д
    for (int i = 0; i < N; i++){
        std::cout << i+1 << "           " << spending[i] << std::endl;
    }
}

//Функція що виводить 2-й пункт меню
void _menu2(int N, float spending[], float budget){
    //Отримання мінімальних максимальних значень
    float max = spending[0];
    float min = spending[0];
    float sum = _CountSum(N, spending, 0, 0);
    int moneydays = 0;
    _findMinMax(N, spending, min, max);
    //Вирахування днів коли були витрати
    for(int i = 0; i<N; i++){
        if(spending[i]!=0){
            moneydays++;
        } else{
            continue;
        }
    }
    //Виведення результатів
    std::cout << "Мінімальні витрати за день:       " << min <<  " грн" << std::endl;
    std::cout << "Максимальні витрати за день:      " << max <<  " грн" << std::endl;
    std::cout << "Сумарні витрати:                  " << sum << " грн" << std::endl;
    if(sum > budget){
        std::cout << "Перевитрата понад бюджет:         " << abs(budget-sum) << " грн" << std::endl;
    }
    std::cout << "Днів з покупками:                  " << moneydays << std::endl;
    int i = 0;
    std::cout << "Середні витрати за такий день:    " << sum/moneydays << " грн" << std::endl;
    //Виведення дня на якому витратився бюджет або залишку бюджету
    if (budget-sum <= 0){
        sum = 0;
        while(i < N){
            sum = sum + spending[i];
            if (sum >= budget){
                std::cout << "Бюджет вичерпано на дні " << i << ", накопичено " << sum << " грн" << std::endl;
                break;
            }
            i++;
        }
    } else{
        std::cout << "Залишок:           " << budget - sum << " грн" << std::endl;
    }

}

//функція що виводить 3-й пункт меню
void _menu3(int N, float spending[], float default_limit = 1000){
    //І цивілізація змінних та введення ліміту користувача або 0 за замовчуванням
    float limit = 0;
    int over = 0;
    limiterr:
    std::cout << "Денний ліміт (грн, 0 = за замовчуванням):";
    std::cin >> limit;
    if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        goto limiterr;
    } 
    if (limit == 0) {
        limit = default_limit; 
    }
    //Цикл що виводить дні з перевищеннями
    for(int i = 0; i < N; i++){
        if(spending[i]>limit){
            std::cout << "    день " << i+1 << ": " << spending[i] << " грн" << std::endl;
            over++;
        }
    }
    if(over > 0){
        std::cout <<"Разом днів з перевищенням: " << over << std::endl;
    } else if (over == 0){
        std::cout << "Немає перевищень" << std::endl;
    }
}

//Функція що виводить 4-й пун
void _menu4(int N, float spending0[]){
    std::cout<< "Топ-3 витрат: ";
    float spending[N];
    for(int i = 0; i < N; i++){
        spending[i]=spending0[i];
    }
    //цикл Що виводить 3 найбільші витрати
    for(int i = 0; i<((N < 3) ? N : 3); i++){
        int max = spending[0];
        int max_i = 0;
        for(int j = 0; j<N; j++){
            if (spending[j] >= max){
                max = spending[j];
                max_i = j;
            }
        }
        spending[max_i]=0;
        if(i < 2){
            std::cout << max << ", ";
        } else{
            std::cout << max;
        }
    }
    
}



int main(){
    //Ініціалізація змінних
    bool exit = 0;
    int answear;
    float budget;
    int N;
    inputerr:
    //Отримання бюджету і кількості днів обліку та витрат по днях
    std::cout << "Бюджет на місяць (грн): ";
    std::cin >> budget;
    if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        goto inputerr;
    } 
    std::cout << "Кількість днів обліку: ";
    std::cin >> N;
    if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        goto inputerr;
    } 
    float spending[N];
    std::cout << "Витрати по днях (грн): ";
    for(int i = 0; i<N; i++){
        std::cin >> spending[i];
        if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        goto inputerr;
    } 
    }

    //цикл що викликає меню та виводить його пункти та дії при виборі пунктів меню
    do {
        answear = _menu();
        switch (answear)
        {
        case 0:
            exit = 1;
            break;
        case 1:
            _menu1(N, spending);
            break;
        case 2:
            _menu2(N, spending, budget);
            break;
        case 3:
            _menu3(N, spending);
            break;
        case 4:
            _menu4(N, spending);
            break;
        default:
            break;
        }
    } while (!exit); 
}