#include <iostream>
#include <cmath>
using namespace std;

// 1. показати витрати по днях
void dailyExp(int N, const double spending[]){
    cout << "День\tВитрати, грн\n";
    for(int i = 0; i < N; i++){
        cout << (i + 1) << "\t" << spending[i] << "\n";
    }
}

// 2. статистика витрат

//пошук мінімальних і максимальних витрат за день
void minMaxExp(int N, const double spending[], double &minVal, double &maxVal){
    if(N <= 0) return;
    minVal = spending[0];
    maxVal = spending[0];
    for(int i = 1; i < N; i++){
        if(spending[i] < minVal) minVal = spending[i];
        if(spending[i] > maxVal) maxVal = spending[i];
    }
}
//рекурсивна функція для сумарних витрат
double sumExp(const double spending[], int N){
    if(N <= 0) return 0;
    return spending[N - 1] + sumExp(spending, N - 1);
}
// 2.
void expStat(int N, const double spending[], double budget){
    double minVal, maxVal;
    minMaxExp(N, spending, minVal, maxVal);
    double total = sumExp(spending, N);
    double remaining = budget - total;

    //cередні витрати за дні з покупками
    int daysWithPurchases = 0;
    double sumPurchases = 0;
    for(int i = 0; i < N; i++){
        if(spending[i] == 0) continue;
        daysWithPurchases++;
        sumPurchases += spending[i];
    }
    //вивід 2.
    cout << "Мінімальні витрати за день:\t" << minVal << " грн\n";
    cout << "Максимальні витрати за день:\t" << maxVal << " грн\n";
    cout << "Сумарні витрати:           \t" << total << " грн\n";

    if (remaining < 0) {
        cout << "Перевитрата понад бюджет:\t" << abs(remaining) << " грн\n";
    } else {
        cout << "Залишок бюджету:        \t" << remaining << " грн\n";
    }

    cout << "Днів з покупками:         \t" << daysWithPurchases << "\n";
    cout << "Середні витрати за такий день:\t" << sumPurchases/daysWithPurchases << " грн\n";
    //день, коли бюджет вичерпано (пошук цього дня)
    double accumulated = 0;
    int idx = 0;

    while (idx < N) {
        accumulated += spending[idx];
        if (accumulated > budget) {
            cout << "Бюджет вичерпано на дні " << (idx + 1) << ", накопичено " << accumulated << " грн\n";
            break; 
        }
        idx++;
    }   

        // якщо цикл дійшов до кінця і бюджет не перевищено
        if (accumulated <= budget) {
            cout << "Бюджету вистачило на всі дні. Залишок: " << remaining << " грн\n";
        }
}

// 3. дні з перевищенням денного ліміту
void daysExcLimit(int N, const double spending[], double dayLimit = 1000.0){
    cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    double inputLimit;
    cin >> inputLimit;
    if(inputLimit > 0){
        dayLimit = inputLimit;
    }
    cout << "Ліміт: " << dayLimit << " грн\n";

    int daysCount = 0;
    for(int i = 0; i < N; i++){
        if(spending[i] > dayLimit){
            cout << "\tдень " << (i + 1) << ":\t" << spending[i] << " грн\n";
            daysCount++;
        }
    }
    cout << "Разом днів з перевищенням: " << daysCount << "\n";
}

// 4. три найдорожчі дні
void mostExpDays(int N, const double spending[]){

    //копіюємо масив, щоб початковий масив не змінився
    double copySpending[31];
    for (int i = 0; i < N; i++) {
        copySpending[i] = spending[i];
    }

    //сортування бульбашкою вкладеними циклами (за спаданням)
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (copySpending[j] < copySpending[j + 1]) {
                double temp = copySpending[j];
                copySpending[j] = copySpending[j + 1];
                copySpending[j + 1] = temp;
            }
        }
    }

    //визначаємо, скільки елементів виводити (3 або N, якщо N < 3)
    int countToShow = (N < 3) ? N : 3;

    cout << "\nТоп-" << countToShow << " витрат:\t";
    
    //виводимо трійку найбільших елементів (у порядку зростання)
    for (int i = countToShow - 1; i >= 0; i--) {
        cout << copySpending[i] << " грн";
        if (i > 0) cout << ", ";
    }
    cout << "\n";

}

int main(){
    double budget;
    cout << "Бюджет на місяць, грн:\t";
    if(!(cin >> budget)) return 0;

    int N;
    cout << "Кількість днів обліку:\t";
    if(!(cin >> N) || N < 1) return 0;

    if(N > 31){
        cout << "N не повинно перевищувати 30" << endl;
        return 0;
    }

    double spending[31] = {};
    cout << "Витрати по днях, грн:\t";
    for(int i = 0; i < N; i++){
        if(!(cin >> spending[i])) return 0;
    }

    int num;
    
    do {
        menu:
        cout << "\nПункт\t Операція\n";
        cout << "1\t Показати витрати по днях\n";
        cout << "2\t Статистика витрат\n";
        cout << "3\t Дні з перевищенням денного ліміту\n";
        cout << "4\t Три найдорожчі дні\n";
        cout << "0\t Вийти\n";

        cout << "Виберіть дію\n" << ">";
        if(!(cin >> num) || (num != 1 && num != 2 && num != 3 && num != 4 && num != 0)) {
            cin.clear();
            cin.ignore(1000, '\n');
            goto menu;
        }

            switch(num){
                case 1:
                    dailyExp(N, spending);
                    break;
                case 2:
                    expStat(N, spending, budget);
                    break;
                case 3:
                    daysExcLimit(N, spending);
                    break;
                case 4:
                    mostExpDays(N, spending);
                    break;
                case 0: 
                    return 0;
                default:
                    goto menu; 
        }
 
    } while(num != 0);
    return 0;
}