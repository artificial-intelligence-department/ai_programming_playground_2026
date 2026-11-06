#include <iostream>
#include <string>

using namespace std;

int main(){
    //введення стрічки
    string s;
    cin >> s;
    //цикл з виведенням кожної унікальної букви і цифри після неї
    for(int i = 0; i < s.length(); i++){
        int n = 1;
        //вивід букви
        cout << s[i];
        //підрахунок букв що повторюються
        while (s[i] == s[i+1]){
            i++;
            n++;
        }
        //не виводимо 1
        if(n != 1){
            cout << n;
        }    
    }
}