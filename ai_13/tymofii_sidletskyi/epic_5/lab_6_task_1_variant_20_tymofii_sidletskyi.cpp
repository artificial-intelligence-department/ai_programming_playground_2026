#include <cstdio>
using namespace::std;
/* Лаб 6 завдання 1 варіант 20
   Сідлецький Тимофій ШІ-13
*/
// Знайти довжину найдовшого слова
int main () {
    char text[255];
    char *p = text;
    int count = 0;
    int current = 0;

    printf("Введіть текст: ");
    fgets(text, 255, stdin);
    while (*p != '.') {
        if (*p != ' ') {
            count++;
        } else {
            if (count > current) {
                current = count;
            }
            count = 0;
        }
        p++;
    }
    if (count > current) {
        current = count;
    }
    printf("Довжина найдовшого слова - %d", current);
    return 0;
}