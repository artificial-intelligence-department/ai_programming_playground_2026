#include <cstdio>
using namespace std;
int main(){
    char s[256];
    fgets(s, sizeof(s), stdin);//ввід з fgets
    char buffer[256];
    int wordLen = 0;
    for(int i = 0; i<sizeof(s); i++){
        if(s[i] == ' ' || s[i] == '.' || s[i] == '\n' || s[i] == '\0'){//шукаю пробіл або завершення(крапка)
            if(wordLen > 0){
                for (int j = wordLen - 1; j >= 0; j--)printf("%c", buffer[j]);//якщо слово вже є виводим наоборот і обнуляєм
                wordLen = 0;
            }
            if(s[i] == ' ' || s[i] == '.')printf("%c", s[i]);//для виводу пробілів і крапки
            if (s[i] == '.' || s[i] == '\n' || s[i] == '\0')break;
        }else{
            buffer[wordLen] = s[i];//додаємо символи в слово
            wordLen++;
        }
    }
    return 0;
}