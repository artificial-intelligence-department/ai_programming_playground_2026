//Задача №0281 "Поле чудес"
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    cin>>s;
    string abetka="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //Задаємо змінні для циклів for
    int i, j;
    //Лічильник унікальних літер
    int k=0;
    for (i=0; i<26; i++) {
        //Змінна, яка рахує повтори однакових літер
        int povtor=0;
           for (j=0; j<s.length(); j++) {
               //Перевірка на співпадіння літер з абетки та слова
               if (abetka[i]==s[j]) {
                   if(povtor==0) {
                       k++; 
                       povtor=1;
                        }
                    }
              }
       }
    cout<<k<<endl;
    return 0;
}