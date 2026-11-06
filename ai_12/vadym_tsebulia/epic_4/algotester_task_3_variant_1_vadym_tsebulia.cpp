/*
Algotester Лабораторна робота №3, Завдання №1, Варіант №1.
Цебуля Вадим
ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;

int main(){
        string word;
        int N;
        cin >> N;
        cin.ignore(); 
        int count = 0;

        for (int i = 0; i < N; i++){
                getline(cin, word);
                int len = word.length();    
                for (int j = 0; j < len; j++){
                        if (word[j] == '#' && (j == 0 || word[j - 1] != '#')) {        
                                count++;
                        }
                }
        }
        
        cout << count << endl;
        return 0;
}