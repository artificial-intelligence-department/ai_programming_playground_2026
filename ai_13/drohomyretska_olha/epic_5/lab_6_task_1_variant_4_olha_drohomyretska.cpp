/*
Задача: Лабораторна робота №6 
Варіант: 4
Автор: Ольга Дрогомирецька
Група: Ші-13
*/

#include <cstdio>
#include <cstring>
using namespace std;

int main() {
  char text[256];

  printf("Введіть текст (до 255 символів, крапка в кінці):\n");
  fgets(text, sizeof(text), stdin);

  //прибираю символи enter
  text[strcspn(text, "\n")] = '\0';
  //перевіряємо, чи закінчується текст крапкою
  int len = strlen(text);

  if (len == 0 || text[len - 1] != '.') {
    printf("Помилка: текст має завершуватися крапкою.\n");
    return 1;
  }
//Знаходимо перше слово
char* firstWord = strtok(text, " .");
if (firstWord == nullptr) {
    printf("Помилка: текст має містити слова.\n");
    return 1;
}
//починаємо пошук із другого слова
char* word = strtok(nullptr, " .");
int count = 0;

printf("Слова, які збігаються з першим:\n");

while (word != nullptr) {
    //якшо слова однакові - виводимо поточне слово
    if (strcmp(firstWord, word) == 0) {
        printf("%s ", word);
        count++;
    }
    //переходимо до наступного слова
    word = strtok(nullptr, " .");
}
if (count == 0) {
    printf("Збігів немає.");
}
printf("\n");
return 0;
}
