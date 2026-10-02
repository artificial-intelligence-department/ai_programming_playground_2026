/*Epic 2 - Коля, Вася і теніс
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    
    string s;
    cin >> s;
    
    int kolya_sets = 0;
    int vasya_sets = 0;
    
    int kolya_points = 0;
    int vasya_points = 0;
    
    for (int i = 0; i < n; i++) {
        if (s[i] == 'K') {
            kolya_points++;
        } else if (s[i] == 'V') {
            vasya_points++;
        }
        
        // Перевірка, чи виграв Коля поточний сет
        if (kolya_points >= 11 && (kolya_points - vasya_points) >= 2) {
            kolya_sets++;
            kolya_points = 0;
            vasya_points = 0;
        } 
        // Перевірка, чи виграв Вася поточний сет
        else if (vasya_points >= 11 && (vasya_points - kolya_points) >= 2) {
            vasya_sets++;
            kolya_points = 0;
            vasya_points = 0;
        }
    }
    
    // Виведення загального рахунку по сетах
    cout << kolya_sets << ":" << vasya_sets << "\n";
    
    // Якщо останній сет не завершився (хоча б один гравець має очки)
    if (kolya_points > 0 || vasya_points > 0) {
        cout << kolya_points << ":" << vasya_points << "\n";
    }
    
    return 0;
}
