#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

//Функція виводу витрат
void spendings(int N, double arr[]){
    int day = 1;
    std::cout << "День\t" << "Витрати, грн\n";
    for(int i = 0; i < N; i++){
        std::cout << day << "\t" << std::fixed << std::setprecision(2) << arr[i] << std::endl;
        day++;
    }
}
//функція для знаходження мінімальних та максимальних витрат
void min_max(int N, double arr[], double &min, double &max){
    min = arr[0];
    max = arr[0];
    for(int i = 1; i < N; i++){
        if(min > arr[i]){
            min = arr[i];
        }
        if(max < arr[i]){
            max = arr[i];
        }
    }
}
//рекурсивна функція для суми витрат
double sum_spend(int N, double arr[]){
    if(N <= 0){
        return 0;
    }
    return arr[N - 1] + sum_spend(N-1, arr);
}
//функція для обчислення використання бюджету
void over_budget(double total_spendings, double budget){
    double remains = budget - total_spendings;
    if(remains < 0){
        std::cout << "Перевитрата понад бюджет: " << std::fixed << std::setprecision(2) << fabs(remains) << " грн" << std::endl;
    } else {
        std::cout << "Залишок бюджету: " << std::fixed << std::setprecision(2)  << remains << " грн" << std::endl;
    }
}
//функція для обчислення к-сті днів з покупками та середніх витрат
void avg_spend(int N, double arr[], double total_spendings){
    int days = 0;
    double avg;
    for(int i = 0; i < N; i++){
        if(arr[i] == 0){
            continue;
        } 
        days++;
    }
    avg = total_spendings / days;
    std::cout << "Днів з покупками: " << days << std::endl;
    std::cout << "Середні витрати за такий день: " << std::fixed << std::setprecision(2) << avg << std::endl;
}
//функція для обчислення вичерпування бюджету
void budget_over(int N, double arr[], double budget){
    double sum = 0;
    int i = 0;
    while(i < N){
        sum += arr[i];
        i++;
        if(sum > budget){
            break;
        }
    }
    if(sum > budget){
        std::cout << "Бюджет вичерпано на дні " << i << ", " << "накопичено " << std::fixed << std::setprecision(2) << sum << std::endl; 
    } else {
        std::cout << "Бюджет не вичерпано, залишок: " << std::fixed << std::setprecision(2) << budget - sum << std::endl;
    }
}
//функція для загального виконання пункту 2
void statistics(int N, double arr[], double budget){
    double min, max;
    min_max(N, arr, min, max);
    std::cout << "Мінімальні витрати за день: " << std::fixed << std::setprecision(2) << min << " грн" << std::endl;
    std::cout << "Максимальні витрати за день: " << std::fixed << std::setprecision(2) << max << " грн" << std::endl;
    double total_spendings = sum_spend(N, arr);
    std::cout << "Сумарні витрати: " << std::fixed << std::setprecision(2) << total_spendings << " грн" << std::endl;
    over_budget(total_spendings, budget);
    avg_spend(N, arr, total_spendings);
    budget_over(N, arr, budget);
}
// функція для виводу денного ліміту та днів з перевищенням
void day_limit(int N, double arr[], double limit = 1000){
    double input;
    std::cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    while(!(std::cin >> input) || input < 0){
        if (std::cin.eof()){
            return;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некоректне значення. Введіть число >= 0: ";
    }
    if (input != 0){
        limit = input;
    }
    std::cout << "Ліміт: " << std::fixed << std::setprecision(2) << limit << " грн\n";
    int count = 0;
    for(int i = 0; i < N; i++){
        if (arr[i] > limit){
            std::cout << "\tДень " << i + 1 << ": " << std::fixed << std::setprecision(2) << arr[i] << std::endl;
            count++;
        }    
    }
    std::cout << "Разом днів з перевищенням: " << count << std::endl;
}
//функція для пошуку топ-3 витрат
void top_spendings(int N, const double arr[]){ 
    //Створюю копію масиву, шоб не змінювати оригінал
    double copy_arr[31];
    for (int i = 0; i < N; i++) {
        copy_arr[i] = arr[i];
    }
    // сортування за спаданням
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (copy_arr[j] < copy_arr[j + 1]) { 
                double element = copy_arr[j];
                copy_arr[j] = copy_arr[j + 1];
                copy_arr[j + 1] = element;
            }
        }
    }
    int top;
    if(N < 3){
        top = N;
    } else {
        top = 3;
    }
    std::cout << "Топ-3 витрат: "; 
    for (int i = 0; i < top; i++) {
        if(i > 0){
            std::cout << ", ";
        }
        std::cout << std::fixed << std::setprecision(2) << copy_arr[i];
    }
    std::cout << " грн" << std::endl;
}   

int main(){
    double budget; //змінна бюджет
    int N; //кількість днів 
    int option; // пункт меню

    std::cout << "Бюджет на місяць, грн: ";
    while(!(std::cin >> budget) || budget <= 0){
        std::cout << "Некоректні дані, повторіть ввід: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Кількість днів обліку: ";
    while(!(std::cin >> N) || N < 1 || N > 31){
        std::cout << "Некоректні дані, повторіть ввід: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    double spending[31];
    std::cout << "Витрати по днях, грн: ";
    for (int i = 0; i < N; i++){
        while(!(std::cin >> spending[i]) || spending[i] < 0){
        std::cout << "Некоректні дані, повторіть ввід: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    do{
        menu_start:
        std::cout << "------Меню------\n";
        std::cout << "Пункт\t" << "Операція\n";
        std::cout << "1\t" << "Показати витрати по днях\n";
        std::cout << "2\t" << "Статистика витрат\n";
        std::cout << "3\t" << "Дні з перевищенням денного ліміту\n";
        std::cout << "4\t" << "Три найдорожчі дні\n";
        std::cout << "0\t" << "Вийти\n\n";

        std::cout << "Виберіть дію: ";
        if(!(std::cin >> option) || option != 1 && option != 2 && option !=  3 && option != 4 && option != 0){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto menu_start;
        } 

        if(option == 1){
            spendings(N, spending);
        } else if(option == 2){
            statistics(N, spending, budget);
        } else if (option == 3){
            day_limit(N, spending);
        } else if (option == 4){
            top_spendings(N, spending);
        }

    }while(option != 0);

    return 0;

}