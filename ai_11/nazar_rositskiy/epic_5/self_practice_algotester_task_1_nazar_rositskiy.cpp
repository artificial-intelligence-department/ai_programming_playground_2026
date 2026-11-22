//снігурочка

#include <cstdio>
#include <cstring>
#include <cctype>

int main(){
    //створення масиву для слова
    char word[1025];

    //Створення рахунку для слів
    int count = 0;

    //Введення слів
    while(scanf("%1024s", word) == 1){
        //Вважаємо слово паліндромом
        bool pali = true;

        //Перевіряємо чи є паліндромом
        for(int i = 0; i < strlen(word)/2; i++){
            if(tolower(word[i]) != tolower(word[strlen(word)-i-1])){
                pali = false;
                break;
            }
        }

        //Якщо є паром то додаємо до ра
        if(pali){
            count++;
        }
    }

    //виводимо рахунок
    printf("%d", count);
}