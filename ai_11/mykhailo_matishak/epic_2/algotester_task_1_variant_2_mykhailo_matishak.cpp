/*Епік 2. Алготестер. Завдання 1. Варіант 2
Автор: Матішак Михайло
Група: ШІ-11*/

#include <iostream>

using namespace std;

int main(){
    unsigned long long h_1, h_2, h_3, h_4, d_1, d_2, d_3, d_4; 
    cin >> h_1 >> h_2 >> h_3 >> h_4;   // зчитування значень h_1, h_2, h_3, h_4
    cin >> d_1 >> d_2 >> d_3 >> d_4;   // зчитування значень d_1, d_2, d_3, d_4
    if (d_1 > h_1 || d_2 > h_2 || d_3 > h_3 || d_4 > h_4) { // перевірка чи d_i не перевищує h_i
        cout << "ERROR" << endl;
        return 0;
    }

    // зменшення значень h_i на відповідні d_i, перевірка чи кожне h_i після зменшення не менше половини від інших h_
    h_1 = h_1 - d_1; 
    if (h_1 * 2 <= h_2 || h_1 * 2 <= h_3 || h_1 * 2 <= h_4) {   
        cout << "NO" << endl;
        return 0;
    }
    h_2 = h_2 - d_2;
    if (h_2 * 2 <= h_1 || h_2 * 2 <= h_3 || h_2 * 2 <= h_4) {
        cout << "NO" << endl;
        return 0;
    }
    h_3 = h_3 - d_3;
    if (h_3 * 2 <= h_1 || h_3 * 2 <= h_2 || h_3 * 2 <= h_4) {
        cout << "NO" << endl;
        return 0;
    }
    h_4 = h_4 - d_4;
    if (h_4 * 2 <= h_1 || h_4 * 2 <= h_2 || h_4 * 2 <= h_3) {
        cout << "NO" << endl;
        return 0;
    }

    unsigned long long max_value = h_1; // знаходження максимального значення серед h_1, h_2, h_3, h_4
    if (h_2 > max_value) {
        max_value = h_2;}
    if (h_3 > max_value) {
        max_value = h_3;}
    if (h_4 > max_value) {
        max_value = h_4;}
    unsigned long long min_value = h_1; // знаходження мінімального значення серед h_1, h_2, h_3, h_4
    if (h_2 < min_value) {
        min_value = h_2;}
    if (h_3 < min_value) {
        min_value = h_3;}
    if (h_4 < min_value) {
        min_value = h_4;}
    min_value = min_value * 2;
    if (max_value >= min_value) { // перевірка чи максимальне значення не перевищує подвоєного мінімального значення
        cout << "NO" << endl;
        return 0;
    }
    if (h_1 == h_2 && h_2 == h_3 && h_3 == h_4 && h_1 > 0) { // перевірка чи всі h_i рівні і більше нуля
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
}