/* 
Задача: Algotester Self-Practice №2.
Автор: Дячок Маргарита.
Група: ШІ-14
*/#include <iostream>
using namespace std;

int main() {
    double s_d = 0;
    double s_u = 0;
    double v = 0;
    cin >> s_d >> s_u >> v;
    if (v == 0) {
        if (s_d == s_u) cout << "Never mind";
        else if (s_d < s_u) cout << "Down";
        else cout << "Up"; } 
    else {
        double t_down = s_d / (v * 2);
        double t_up = s_u / (v / 2);
        if (t_down == t_up) cout << "Never mind";
        else if (t_down < t_up) cout << "Down";
        else cout << "Up"; }

    return 0;
}