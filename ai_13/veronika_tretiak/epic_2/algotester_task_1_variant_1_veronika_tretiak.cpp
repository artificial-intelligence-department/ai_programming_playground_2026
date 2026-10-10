#include <iostream>
using namespace std;

int main(){
    //Введення змінних
    long long H, M;

    cin >> H >> M;

    //Перевірка на правильність введення значень H та M
    for (int i = 0; i < 3; i++) {
        long long  h, m;
        cin >> h >> m;

        if ( h > 0 && m > 0){
       cout << "NO";
         return 0;
        }
        H -= h;
        M -= m;
        
    }
    //Перевірка на правильність залишку H та M
    if (H > 0 && M > 0){
        cout << "YES";
    } else {
        cout << "NO";
    }
return 0;
}