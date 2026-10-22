/*
Алготестер задача 2 Коля, Вася і Теніс
Станіслав Коваль
ШІ-12
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int kWins = 0, vWins = 0;
    int kScore = 0, vScore = 0;

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;

        if (c == 'K'){
            kScore++;
        } 
        else{
            vScore++;
        }

        if ((kScore >= 11 || vScore >= 11) && abs(kScore - vScore) >= 2) {
            if (kScore > vScore){
                kWins++;
            }
            else{
                vWins++;
            }
            kScore = 0;
            vScore = 0;
        }
    }

    cout << kWins << ":" << vWins << endl;

    if (kScore + vScore > 0) {
        cout << kScore << ":" << vScore << endl;
    }

    return 0;
}