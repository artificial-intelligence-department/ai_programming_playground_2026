/*Epic 5 - Буквозабирання
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <string>

using namespace std;

bool check(const string &a, const string &b, int i) {
    return a.compare(i, b.size(), b) == 0;
}

int main() {
    int n;
    cin >> n;
    while (n-- > 0){
        string a, b;
        cin >> a >> b;
        int m = b.size();
        int k = (int)a.size() - m; // Кількість літер які необхідно видалити
        
        bool sergei;
        if (k <= 0) { // Цільовий рядок довший або рівний за початковий - Сергій виграє тільки якщо вони однакові
            sergei = (a == b);
        } else if (k % 2 == 1){ // Якщо потрібно видалити непарну кількість літер
            sergei = check(a, b, (k - 1) / 2) && check(a, b, (k + 1) / 2); // Сергій виграє якщо цільовий рядок є строго по центру
                                                                           // початкового і з невеликим зміщенням вліво - вправо
        } else {
            sergei = check(a, b, (k / 2)) || (check(a, b, (k / 2 - 1)) && check(a, b, (k / 2 + 1))); // Сергій виграє якщо рядок є
                                                                                                     // точно по центру або по краях центру початкового
        }
        cout << (sergei ? "Sergei" : "Larry") << "\n";
    }
    return 0;
}