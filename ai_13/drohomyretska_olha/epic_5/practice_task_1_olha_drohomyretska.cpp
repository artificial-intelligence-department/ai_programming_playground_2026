#include <iostream> 
#include <cstring>
#include <cctype>
#include <string>
#include <cstdio>
using namespace std;

bool isValidno(const char *text);
char **splitWords(const char *text, int &count);
void freeWords(char **&words, int &count);
void showMenu();
void countChars(const char *text, int &letters, int &digits, int &spaces);
void showStatistics(const char *text, int count);
void showWords(char **words, int count);
void quickSort(char **words, int left, int right);
bool finishLine();
bool readWord(const char *prompt, char *word);
void replaceWord(char *text, char **&words, int &count);
void compareWords();
void showCharInfo(const char *text);
void newSentence(char *text, char **&words, int &count);

int main () {
    //255 позицій для тексту та одна завершальна для нуля; спочатку масив порожній
   char text[256] = {};
   printf("Введіть текст (до 255 символів, крапка в кінці):\n");

   if (fgets(text, sizeof(text), stdin) == nullptr) {
    return 1;
   }
   //прибираємо новий рядок від Enter, щоб останнім символом тексту залишалася крапка
   text[strcspn(text, "\n")] = '\0';

   if (strlen(text) == 255) {
    char extra;
    if (scanf("%c", &extra) == 1 && extra != '\n') {
        printf("Помилка: техт перевищує 255 символів.\n");
        return 1;
    }
   }
   if (!isValidno(text)) {
    printf("Помилка: текст має складатися з латинських літер, цифр\n" 
        "і пробілів та завершуватися крапкою.\n");
    return 1;
   }

   int count = 0;
   //words зберігає адреси окремих слів, а count - кількість цих адрес
   char **words = splitWords(text, count);

   int choice;
   while (true) {
    showMenu();
    //result - кільсть успішних перетворень, EOF ознчає завершення вводу
    int result = scanf("%9d", &choice);
    if (result == EOF) {
        break;
    }
    char extra; 
    bool hasExtra = false;
    //дочитуємо залишок рядка, щоб зайві символи не стали наступним вибором меню
    while (scanf("%c", &extra) == 1 && extra != '\n') {
        if (!isspace((unsigned char)extra)) {
            hasExtra = true;
        }
    }
    //відхиляємо як нечисловий ввід, так і сторонні символи після числа
    if (result != 1 || hasExtra) {
        printf("Помилка: введіть номер пункту меню.\n");
        continue;
    }
    if (choice == 0) {
        break;
    }
    if (choice < 0 || choice > 6) {
        printf("Помилка: пункту %d немає в меню.\n", choice);
        continue;
    }
    //кожен пункт меню викликає свою функцію
    switch (choice) {
        case 1:
        showStatistics(text, count);
        break;

        case 2:
        showWords(words, count);
        break;

        case 3:
        replaceWord(text, words, count);
        break;

        case 4:
        compareWords();
        break;

        case 5:
        showCharInfo(text);
        break;

        case 6:
        newSentence(text, words, count);
        break;
    }
   }
   //після виходу з меню повертаємо всю виділену для слів памʼять
   freeWords(words, count);
   return 0;
}
//перевіряє завершальну крапку, дозволені символи та наявність хоча б одного слова
bool isValidno(const char *text) {
    int length = strlen(text);
    //спочатку перевіряємо порожній рядок: це не дозволяє звернутися до індексу -1
    if (length == 0 || text[length - 1] != '.') {
        return false;
    }
    bool hasWord = false;
    
    //завершальну крапку вже перевірено; решта символів мають бути літерами, цифрами, або пробілами
    for (int i = 0; i < length - 1; i++) {
        unsigned char c = text[i];
        if (isalpha(c) || isdigit(c)) {
            hasWord = true;
        } else if (c != ' ') {
            return false;
        }
    }
    return hasWord;
}
//створюємо окремі динамічні копії слів, count повертає їх через посилання
char **splitWords(const char *text, int &count) {
    char copy[256];
    strcpy(copy, text);

    copy[strlen(copy) - 1] = '\0'; //прибираємо крапку лише з копії
    char **words = new char*[128];
    count = 0;
    char *word = strtok(copy, " ");

    while (word != NULL) {
        words[count] = new char[strlen(word) + 1]; //виділяємо окрему памʼять для символу слова
        strcpy(words[count], word);
        count++;

        word = strtok(NULL, " ");
    }
    return words;
}
//звільняємо слова й масив вказівників, посилання обнулюють words i count у виклику
void freeWords(char **&words, int &count) {
    for (int i = 0; i < count; i++) {
        delete[] words[i]; //звільняємо памʼять кожного слова
    }
    delete[] words; //звільняємо сам масив вказівників
    words = NULL;
    count = 0;
}
//показуємо доступні операції, після виконання пункту повертаємося до меню
void showMenu () {
    printf("\nПункт    Операція\n"
        "1     Показати текст і статистику\n"
        "2     Tаблиця слів\n"
        "3     Замінити слово\n"
        "4     Порівняти два слова\n"
        "5     Інформація про символ\n"
        "6     Ввести нове речення\n"
        "0     Вийти\n"
        "Ваш вибір: ");
}
//обходить текст вказівником, три лічильники передаються через посилання для повернення результатів
void countChars (const char *text, int &letters, int &digits, int &spaces) {
   letters = 0;
   digits = 0;
   spaces = 0;
   //p переходить до наступного символу, *p читає поточний; завершальний нуль зупиняє обхід
   for (const char *p = text; *p != '\0'; p++) {
    unsigned char c = *p;
    if (isalpha(c)) {
        letters++;
    } else if (isdigit(c)) {
        digits++;
    } else if (c == ' ') {
        spaces++;
    }
  }
}
//обчислює кількість символів кожного типу та їхню частку в загальній довжині тексту
void showStatistics(const char *text, int count) {
    int letters, digits, spaces;
    countChars(text, letters, digits, spaces);
    //у загальну довжину входить крапка, тому сума відсотків літер, цифр і пробілів менша за 100%
    int length = strlen(text);
    printf("Текст:\t\"%s\"\n", text);
    printf("Символів: %6d\n", length);
    printf("Слів:     %6d\n", count);
    printf("Літер:    %6d (%6.1f%%)\n", letters, 100.0 * letters / length);
    printf("Цифр:     %6d (%6.1f%%)\n", digits, 100.0 *digits/length);
    printf("Пробілів: %6d (%6.1f%%)\n", spaces, 100.0 * spaces / length);
}
//показує слово в початковому порядку, їхні довжини та результати аналізу
void showWords(char **words, int count) {
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");

    for (int i = 0; i < count; i++) {
        printf("| %2d | %-15s | %5zu |\n",
               i + 1, words[i], strlen(words[i]));
    }
    //зберігаємо індекси слів, а не їхні копії; за однакової довжини залишається перше знайдене
    int longest = 0;
    int shortest = 0;
    int totalLength = 0;

    for (int i = 0; i < count; i++) {
        int length = strlen(words[i]);
        totalLength += length;

        if (length > strlen(words[longest])) {
            longest = i;
        }
        if (length < strlen(words[shortest])) {
            shortest = i;
        }
    }
    printf("+----+-----------------+-------+\n");
    printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", 1.0 * totalLength / count);
    //копіюємо лише адреси: сортування не змінить порядок у words
    char **sorted = new char*[count];
    for (int i = 0; i < count; i++) {
        sorted[i] = words[i];
    }
    quickSort(sorted, 0, count - 1);
    printf("За абеткою:");
    for (int i = 0; i < count; i++) {
        printf(" %s", sorted[i]);
    }
    printf("\n");

    int best = 0; //де стоїть найчастіше слово
    int bestCount = 0; //скільки разів зустрічається
    for(int i = 0; i < count; ){
        int j = i + 1;
        while (j < count && strcmp(sorted[i], sorted[j]) == 0) {
           j++;
        }
        //j - i - розмір групи; за однакової частоти залишається перше за порадком strcmp слово
        if (j - i > bestCount) {
            best = i;
            bestCount = j - i;
        }
        //переходимо одразу до першого слова наступної групи, не перераховуючи вже знайдені повтори
        i = j;
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[best], bestCount);
    //звільняємо копію масиву адрес
    delete[] sorted;
}
void quickSort(char **words, int left, int right) { //функція розставляє слова за абеткою
    int i = left;
    int j = right;
    char *pivot = words[(left + right) / 2]; //вибираємо опорне слово 
    
    while (i <= j) {
        //два цикли while пропускають слова, які вже з правильного боку
        while (strcmp(words[i], pivot) < 0) {
            i++;
        }
        while (strcmp(words[j], pivot) > 0) {
            j--;
        }
        if (i <= j) {
            char *temp = words[i];
            words[i] = words[j];
            words[j] = temp;

            i++;
            j--;
        }
    }
    //сортуємо ті частини, що лишилися після роботи циклу
    if (left < j) {
        quickSort(words, left, j);
    }
    if (i < right) {
        quickSort(words, i, right);
    }
}
//дочитуємо поточний рядок; false означає, що після введення залишилося непробільні символи
bool finishLine() {
    char extra;
    bool clean = true;

    while (scanf("%c", &extra) == 1 && extra != '\n') {
        if (!isspace((unsigned char)extra)) {
            clean = false;
        }
    }

    return clean;
}
//зчитує одне слово й повертає true лише після успішного введення та перевірки символів
bool readWord(const char *prompt, char *word) {
    printf("%s", prompt);
    //залишаємо місце для завершального нуля в буфері з 32 символів; %s читає до пробілу.
    int result = scanf("%31s", word);
    // Друге слово або хвіст надто довгого слова роблять clean хибним.
    bool clean = finishLine();

    if(result != 1 || !clean) {
        printf("Помилка: введіть одне слово до 31 символу.\n");
        return false;
    }
    for (int i = 0; word[i] != '\0'; i++){
        unsigned char c = word[i];
        if (!isalpha(c) && !isdigit(c)) {
            printf("Помилка: слово має містити лише латинські літери й цифри.\n");
            return false;
        }
    }
    return true;
}
// Замінює лише цілі слова; оновлює текст і заново формує динамічний масив слів.
void replaceWord(char *text, char **&words, int &count) {
    char from[32];
    char to[32];
    if (!readWord("Замінити слово: ", from)) {
        return;
    }
    if (!readWord("На слово: ", to)) {
        return;
    }
    string before = text;
    string after = before;
    
    string oldWord = from;
    string newWord = to;

    size_t position = 0;
    int replacements = 0;
    // find повертає позицію наступного входження; npos означає, що більше входжень немає.
    while ((position = after.find(oldWord, position)) != string::npos) {
    size_t end = position + oldWord.length();
    // Межі слова не дозволяють замінити cat усередині слова catalog; || захищає індекс position - 1.
    bool leftBoundary = position == 0 || after[position - 1] == ' ';
    bool rightBoundary = end == after.length() || after[end] == ' '|| after[end] == '.';

    if(leftBoundary && rightBoundary) {
        after.replace(position, oldWord.length(), newWord);
        // Продовжуємо після вставленого слова, щоб не обробляти повторно щойно зроблену заміну.
        position += newWord.length();
        replacements++;
    } else {
        position += oldWord.length();
    }
    }
    if (after.length() > 255) {
        printf("Помилка: після заміни текст перевищує 255 символів.\n");
        return;
    }
    strcpy(text, after.c_str());
     // Старі слова більше не відповідають зміненому тексту: видаляємо їх і створюємо нові.
    freeWords(words, count);
    words = splitWords(text, count);
    printf("Замін виконано: %d\n", replacements);
    printf("Було: \"%s\"\n", before.c_str());
    printf("Стало: \"%s\"\n", text);
    printf("Нова довжина: %zu\n", after.length());
}
// Порівнює два слова з урахуванням регістру та без нього, показує довжини й конкатенацію.
void compareWords() {
    char a[32];
    char b[32];
    if (!readWord("Перше слово: ", a)) {
        return;
    }
    if (!readWord("Друге слово: ", b)){
        return;
    }
    int result = strcmp(a, b);
    // strcmp гарантує знак результату, а не саме -1 чи 1; приводимо значення до потрібного формату.
    if (result < 0) {
        result = -1;
    } else if (result > 0) {
        result = 1;
    }
    if (result == -1) {
        printf("srtcmp: -1 -> перше слово менше\n");
    } else if (result == 1) {
        printf("strcmp: 1 -> перше слово більше\n");
    } else {
        printf("strcmp: 0 -> слова однакові\n");
    }
    string first = a;
    string second = b;
    if (first == second) {
        printf("Рівні (==): так\n");
    } else {
        printf("Рівні (==): ні\n");
    }
    // Змінюємо регістр лише в копіях, щоб зберегти початковий вигляд введених слів.
    string lowerFirst = first;
    string lowerSecond = second;
    for (size_t i = 0; i < lowerFirst.length(); i++) {
        lowerFirst[i] = tolower((unsigned char)lowerFirst[i]);
    }

    for (size_t i = 0; i < lowerSecond.length(); i++) {
        lowerSecond[i] = tolower((unsigned char)lowerSecond[i]);
    }

    if (lowerFirst == lowerSecond) {
        printf("Рівні без урахування регістру: так\n");
    } else {
        printf("Рівні без урахування регістру: ні\n");
    }
    printf("Довжини: %zu i %zu\n", first.length(), second.length());
    string combined = first + " & " + second;
    printf("Конкатенація: \"%s\" (%zu)\n", combined.c_str(), combined.length());
}
// Визначає код і тип символу, його регістр та входження в поточний текст.
void showCharInfo(const char *text) {
    char input;
    printf("Введіть символ: ");
    if (scanf("%c", &input) != 1) {
        return;
    }
    // %c читає навіть пробіл; залишок рядка дочитуємо, якщо сам Enter ще не був прочитаний.
    if (input != '\n') {
        finishLine();
    }
    unsigned char c = input;
    unsigned int code = c;

    printf("Символ: '%c'\n", c);
    printf("Код: %u (hex 0x%x, oct 0%o, bin ", code, code, code);
    // Виводимо 8 бітів від старшого до молодшого; зсув і маска 1 виділяють один біт.
    for (int bit = 7; bit >= 0; bit--) {
        printf("%u", (code >> bit) & 1u);
    }
    printf(")\n");

    const char *type = "інший символ";
    if (isupper(c)) {
        type = "велика літера";
    } else if (islower(c)) {
        type = "мала літера";
    } else if (isdigit(c)) {
        type = "цифра";
    } else if (isspace(c)) {
        type = "пробільний символ";
    }
    printf("Тип: %s\n", type);
    // Інший регістр має сенс тільки для літери; тернарний оператор вибирає lower або upper.
    if (isalpha(c)) {
        printf("Інший регістр: '%c'\n",
               isupper(c) ? tolower(c) : toupper(c));
    }
    printf("Наступний символ: '%c'\n", (int)c + 1);
    // strchr повертає адресу першого входження символу або NULL, якщо його немає.
    const char *first = strchr(text, input);
    int occurrences = 0;
    for (const char *p = text; *p != '\0'; p++) {
        if (*p == input) {
            occurrences++;
        }
    }
    // Різниця first - text дає індекс від нуля; у виводі додаємо 1 для позиції від одиниці.
    if (first == NULL) {
        printf("У тексті не зустрічається.\n");
    } else {
        printf("Входжень у тексті: %d, перше на позиції %d\n",
               occurrences, (int)(first - text) + 1);
    }
}
// Читає слова до завершальної крапки; приймає новий текст лише після всіх перевірок.
void newSentence(char *text, char **&words, int &count) {
    printf("Введіть речення (крапка після останнього слова):\n");
    string sentence;
    string word;

    int readCount = 0;
    bool ended = false;
    bool tooLong = false;
    // Читаємо по слову; під час складання речення замінюємо будь-які проміжки одним пробілом.
    while (cin >> word) {
        readCount++;
        // Після перевищення довжини припиняємо нарощувати рядок, але продовжуємо читати до крапки.
        if (!tooLong) {
         if (!sentence.empty()) {
                sentence += " ";
            }
            sentence += word;
            tooLong = sentence.length() > 255;
        }
        if (word[word.length() - 1] == '.') {
            ended = true;
            break;
        }
    }
    if (ended) {
        finishLine();
    }
    // Невдалий ввід не змінює поточний текст; нове речення приймаємо лише після всіх перевірок.
    if (!ended || tooLong || !isValidno(sentence.c_str())) {
        printf("Помилка: некоректне речення або довжина перевищує 255 символів.\n");
        return;
    }
    strcpy(text, sentence.c_str());
    freeWords(words, count);
    // Після прийняття нового тексту оновлюємо також слова та їхню кількість.
    words = splitWords(text, count);
    printf("Прочитано слів: %d\n", readCount);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", sentence.length());
}