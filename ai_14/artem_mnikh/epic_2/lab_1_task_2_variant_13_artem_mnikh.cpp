/*
lab1 task 2 v-13
Artem Mnikh
AI_14
*/
#include <iostream>

using namespace std;

int main(){
    int m, n;
    cout << "Введіть число m: ";
    cin >> m;
    cout << endl <<  "Введіть число n: ";
    cin >> n;
    cout << endl << "Значення m і n: "<< m << "; " << n << endl;

    int temp_n = n;
    int temp_m = m;

    int res1 = temp_m- ++temp_n;
    cout << "m- ++n: " << res1 << endl;

    temp_m = m;
    temp_n = n;

    int res2 = ++temp_m > --temp_n;
    cout << "++m > --n: " << (res2 ? "True": "False") << endl;
    
    temp_m = m;
    temp_n = n;
    
    int res3 = --temp_n < ++temp_m;
    cout << "--n < ++m: " << (res3 ? "True": "False") << endl;

    return 0;

}