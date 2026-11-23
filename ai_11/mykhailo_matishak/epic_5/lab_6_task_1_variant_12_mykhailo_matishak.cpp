/*Лабораторна 6, варіант 12. Задача: сортування букв у кожному слові рядка
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

void sortWord(char *s, int from, int to){
    char letters[256];
    int n = 0;
    for(int i = from; i < to; i++){
        if(isalpha((unsigned char)s[i])){
            letters[n] = s[i];
            n++;
        }
    }
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if(letters[j] > letters[j + 1]){
                char temp = letters[j];
                letters[j] = letters[j + 1];
                letters[j + 1] = temp;
            }
        }
    }
    n = 0;
    for(int i = from; i < to; i++){
        if(isalpha((unsigned char)s[i])){
            s[i] = letters[n];
            n++;
        }
    }
}

void sortAllWords(char *s){
    int len = strlen(s);
    int i = 0;
    while(i < len){
        if(s[i] == ' ' || s[i] == '.'){
            i++;
        }
        else{
            int start = i;
            while(i < len && s[i] != ' ' && s[i] != '.'){
                i++;
            }
            sortWord(s, start, i);
        }
    }
}

int main(){
    char s[256];
    cout << "Введіть текст (до 255 символів, крапка в кінці):" << endl;
    cin.getline(s, 256);
    sortAllWords(s);
    cout << "Результат: " << s << endl;

    return 0;
}