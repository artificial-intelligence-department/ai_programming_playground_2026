/*
 * Задача: Стипендія (алготестер додатково)
 * Поліщук Вероніка
 * Група 14
 */

 #include <iostream>

 using namespace std;

 int main(){
    int n, a;
    cin >> n;
    int pidv=0, zvyc=0;
    for (int i=0; i < n; i++){
        cin >> a;
        if (a >= 90) pidv++;
        else if (a >= 51) zvyc++;
    }
    if (pidv == n) cout << "Pidvyshchena";
    else if (zvyc+pidv == n) cout << "Zvychaina";
    else cout << "Zabud pro stypendiiu";

    
    return 0;
 }