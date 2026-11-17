/*
Редактор текстового повідомлення
Мадяр Андрій Вікторович
ШІ-13
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
using namespace std;
const int textSize = 256;//розміри +1 для '\0'
const int wordSize = 32;
//були для перевірок всередині інших функцій
bool clearLine();
bool readLine(char buffer[], int size);
bool isValidText(const char* text);
bool readWord(char word[], int size);
//ф-ції для дії з динамічними масивами
char **splitWords(const char *text, int &count);
void freeWords(char **&words, int &count);
//ф-ції для пунктів меню
void countChars(const char *text, int &letter, int &digit, int &space);
void showStat(const char *text, int count);
void wordTable(char **words, int count);
void wordAnalysis(char **words, int count);
void showWords(char **words, int count);
void replaceWord(char text[]);
void compareWords();
void showCharacter(const char *text);
void readSentence(char text[]);
int main(){
    char text[textSize];
    int choice, count = 0;
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if(!readLine(text, textSize) || !isValidText(text)){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0;
    }
    char **words = splitWords(text, count);
    do{
        printf("Показати текст і статистику(1)\n");
        printf("Таблиця слів(2)\n");
        printf("Замінити слово(3)\n");
        printf("Порівняти два слова(4)\n");
        printf("Інформація про символ(5)\n");
        printf("Ввести нове речення(6)\n");
        printf("Вийти(0)\nВибір за вами: ");
        int scans = scanf("%9d", &choice);//дивимся чи не написали багато сиволів, 9 щоб не сталося оверфлову
        if(scans == EOF)break;
        bool trash = clearLine();
        if(scans != 1 || trash){//перевірки на ввід та відповідні дії
            printf("Помилка: введіть номер пункту меню.\n");
            choice = -1;
            continue;
        }
        if(choice < 0 || choice > 6){//очевидно для яких випадків
            printf("Помилка: пункту %d немає в меню.\n", choice);
            choice = -1;
            continue;
        }
        printf("\n");
        switch(choice){
            case 1:showStat(text, count);
            break;
            case 2:showWords(words, count);
            break;
            case 3:replaceWord(text);
            break;
            case 4:compareWords();
            break;
            case 5:showCharacter(text);
            break;
            case 6:readSentence(text);
            break;
            case 0:break;
        }
        if(choice == 3 || choice == 6){
            freeWords(words, count);//ми перезаписали текст треба перевиділити слова
            words = splitWords(text, count);//+запобігання витокам
        }
    }while(choice != 0);
    freeWords(words, count);
    return 0;
}
bool clearLine(){//для того шоб у випадку переповнення забрати мусор
    bool overflow = false;
    while(true){
        int chr = getchar();//приймаємо символ
        if(chr == EOF || chr == '\n')break;//закриваєм якщо доходимо до кінця або ентер
        if(chr != ' '&& chr != '\t')overflow = true;//чотири пробіли реагує як табуляцію 
    }
    return overflow;
}
bool readLine(char buffer[], int size){//чиста перевірка і заміна \n
    if(fgets(buffer, size, stdin) == nullptr)return false;//воно дає нулптр якщо пусто
    char *enter = strchr(buffer, '\n');//шукаєм ентер
    if(enter != nullptr){//нам надо перевірити чи знайдений в межах
        *enter = '\0';
        return true;
    }
    int nextChr = getchar();//перевіряєм можливо текст на крайній межі то ентер наступний у буфері
    if(nextChr == EOF || nextChr == '\n')return true;
    clearLine();
    return false;
}
bool isValidText(const char *text){//перевірка умов коректності
    int length = static_cast<int>(strlen(text));//бо strlen видає тип size_t
    if(length < 2 || length > 255 || text[length-1] != '.')return false;
    bool hasWord = false;
    for(int i = 0; i<length-1; i++){
        unsigned char a = static_cast<unsigned char>(text[i]);//захищаємось від переповнення бла бла
        bool latin = false;
        if((a>='a' && a<='z')||(a>='A' && a<='Z'))latin = true;
        if(latin || isdigit(a)){
            hasWord = true;
        }else if(a!=' ')return false;
    }
    return hasWord;
}
bool readWord(char word[], int size){
    if(!readLine(word, size) || strlen(word) == 0){
        printf("Помилка: введіть одне слово довжиною від 1 до %d символів.\n", size - 1);
        return false;
    }
    for(int i = 0; word[i]!='\0'; i++){
        unsigned char a = static_cast<unsigned char>(word[i]);//захищаємось від переповнення бла бла
        bool latin = false;
        if((a>='a' && a<='z')||(a>='A' && a<='Z'))latin = true;
        if(!latin && !isdigit(a)){
            printf("Помилка: у слові дозволені лише латинські літери та цифри.\n");
            return false;
        }
    }
    return true;
}
char **splitWords(const char *text, int &count){//для розділення тексту на слова
    count = 0;
    for(int i = 0; text[i]!='.' && text[i]!='\0'; i++){
        if(text[i]!=' ' && (i == 0||text[i-1] == ' '))count++;//обраховуєм кількість слів(якщо перша буква не пробіл а символ до неї-пробіл(або його нема))
    }
    char buffer[textSize];
    strcpy(buffer, text);//створюєм копію бо strtok змінює рядок
    buffer[strlen(buffer)-1] = '\0';
    char **words = new char*[count];
    char *token = strtok(buffer, " ");
    for(int i = 0; i<count; i++){
        if(token == nullptr)break;//випадок якщо слова закінчилися
        words[i] = new char[strlen(token)+1];//+1 для '\0'
        strcpy(words[i], token);
        token = strtok(nullptr, " ");
    }
    return words;
}
void freeWords(char **&words, int &count){
    if(words == nullptr){//якийсь тесткейс не проходив
        count = 0;
        return;
    }
    for(int i = 0; i<count; i++){
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    count = 0;
    return;
}
void countChars(const char *text, int &letter, int &digit, int &space){
    letter = 0;
    digit = 0;
    space = 0;
    const char *p = text;
    while(*p != '\0'){
        unsigned char a = static_cast<unsigned char>(*p);
        if(isalpha(a)){
            letter++;
        }else if(isdigit(a)){
            digit++;
        }else if(a == ' ')space++;
        p++;
    }
}
void showStat(const char *text, int count){
    int letter = 0, digit = 0, space = 0;
    countChars(text, letter, digit, space);
    int length = static_cast<int>(strlen(text));
    printf("Текст\t\"%s\"\n", text);
    printf("Символів: %5d\n", length);
    printf("Слів:     %5d\n", count);
    printf("Літер:    %5d (%5.1f%%)\n", letter, 100.0*letter / length);
    printf("Цифр:     %5d (%5.1f%%)\n", digit, 100.0*digit / length);
    printf("Пробілів: %5d (%5.1f%%)\n", space, 100.0*space / length);
}
void wordTable(char **words, int count){
    int wordWidth = 15, countWidth = 2;//відповідна ширина
    for(int i = 0; i<count; i++){
        int len = static_cast<int>(strlen(words[i]));
        if(len > wordWidth)wordWidth = len;
    }
    if(count >= 100)countWidth++;
    string border = "+" + string(countWidth + 2, '-') + "+" + string(wordWidth + 2, '-') + "+-------+";
    printf("%s\n", border.c_str());
    printf("| %-*s | Слово%*s | Довж. |\n", countWidth, "N", wordWidth - 5, "");//чутливе до більшої ширини
    printf("%s\n", border.c_str());
    for (int i = 0; i < count; i++) {
        printf("| %*d | %-*s | %5zu |\n", countWidth, i + 1, wordWidth, words[i], strlen(words[i]));
    }
    printf("%s\n", border.c_str());
}
void wordAnalysis(char **words, int count){
    int minIndex = 0, maxIndex = 0, highestIndex = 0, mostCount = 0;
    double sum = 0;
    for(int i = 0; i<count; i++){
        int len = static_cast<int>(strlen(words[i]));
        sum += len;
        if (len < static_cast<int>(strlen(words[minIndex])))minIndex = i;//просто шукаємо те в якого відповідна довжина
        if (len > static_cast<int>(strlen(words[maxIndex])))maxIndex = i;
    }
    printf("Найдовше слово: %s (%zu)\n", words[maxIndex], strlen(words[maxIndex]));
    printf("Найкоротше слово: %s (%zu)\n", words[minIndex], strlen(words[minIndex]));
    printf("Середня довжина: %.2f\n", sum / count);
    char** sorted = new char*[count];
    for(int i = 0; i<count; i++){
        sorted[i] = words[i];
    }
    for(int i = 0; i<count-1; i++){
        for(int j = 0; j<count-i-1; j++){
            if(strcmp(sorted[j], sorted[j + 1]) > 0){//видає >0 якщо буква більша по аскіі
                char *temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    printf("За абеткою:");
    for(int i = 0; i<count; i++){
        printf(" %s", sorted[i]);
    }
    printf("\n");
    for(int i = 0; i<count; i++){
        int currentCount = 0;
        for(int j = 0; j<count; j++){
            if(strcmp(sorted[i], sorted[j]) == 0){
                currentCount++;
            }
        }if(currentCount > mostCount){
            mostCount = currentCount;
            highestIndex = i;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", sorted[highestIndex], mostCount);
    delete[] sorted;
}
void showWords(char **words, int count){//розділив бо ну дуже крупна
    wordTable(words, count);
    wordAnalysis(words, count);
}
void replaceWord(char text[]){//для заміни слів
    char fromchr[wordSize], tochr[wordSize];
    printf("Замінити слово: ");
    if(!readWord(fromchr, wordSize))return;
    printf("На слово: ");
    if(!readWord(tochr, wordSize))return;
    string result = text, from = fromchr, to = tochr;//створюєм стрінг-відповіднки
    int changes = 0;
    size_t pos = result.find(from, 0);
    while(pos != string::npos){
        size_t end = pos + from.length();
        bool starts = false, ends = false;
        if(pos == 0 || result[pos-1] == ' ')starts = true;//якщо до знайденого пробіл або нічого
        if(result[end] == ' '||result[end] == '.') ends = true;//після знайденого пробіл або .(кінець)
        if(starts&&ends){
            result.replace(pos, from.length(), to);
            changes++;
            pos += to.length();
        }else pos++;
        pos = result.find(from, pos);
    }
    if(result.length() > 255){
        printf("Помилка: після заміни текст перевищить 255 символів.\n");
        return;
    }
    printf("Замін виконано: %d\n", changes);
    printf("Було:  \"%s\"\n", text);
    printf("Стало: \"%s\"\n", result.c_str());
    printf("Нова довжина: %zu\n", result.length());
    strcpy(text, result.c_str());
}
void compareWords(){
    char one[wordSize], two[wordSize];
    printf("Перше слово: ");
    if(!readWord(one, wordSize))return;
    printf("Друге слово: ");
    if(!readWord(two, wordSize))return;
    int cmp = strcmp(one, two);
    if(cmp<0){
        printf("strcmp: -1 -> перше слово менше\n");
    }else if(cmp>0){
        printf("strcmp: 1 -> перше слово більше\n");
    }else printf("strcmp: 0 слова одинакові\n");
    string a = one, b = two, together = a + " & " + b;//зразу є змінна для виводу конкатенації
    printf("Рівні (==): %s\n", (a==b) ? ("так") : ("ні"));
    for(size_t i = 0; i<a.length(); i++){
        a[i] = static_cast<char>(tolower(static_cast<unsigned char>(a[i])));
    }//переписуємо всі на маленькі буквищоб порівняти
    for(int i = 0; i<b.length(); i++){
        b[i] = static_cast<char>(tolower(static_cast<unsigned char>(b[i])));
    }
    printf("Рівні без урахування регістру: %s\n", (a==b) ? ("так") : ("ні"));
    printf("Довжини: %zu і %zu\n", a.length(), b.length());
    printf("Конкатенація: \"%s\" (%zu)\n", together.c_str(), together.length());
}
void showCharacter(const char *text){
    char chr[3];
    printf("Введіть символ: ");
    if(!readLine(chr, 3) || strlen(chr) != 1){//з цими ф-ціями не треба забирати пробіл
        printf("Помилка: потрібно ввести рівно один символ.\n");
        return;
    }
    unsigned char a = static_cast<unsigned char>(chr[0]);
    unsigned int base = a;
    printf("Символ: '%c'\n", a);
    printf("Код: %u (hex 0x%x, oct 0%o, bin ", base, base, base);
    for(int i = 7; i>=0; i--)printf("%u",(base >> i) & 1u);//імітація переведення в двійкову, постійно побітовий зсув та побітове І у крайньому біті 
    printf(")\n");
    if(isupper(a)){
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(a));
    }else if(islower(a)){
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(a));
    }else if(isdigit(a)){
        printf("Тип: цифра\n");
    }else if(isspace(a)){
        printf("Тип: пробільний символ\n");
    }else printf("Тип: інший символ\n");
    if(base < 255) {
        char nextChar = static_cast<char>(base + 1);
        printf("Наступний символ: '%c'\n", nextChar);
    }
    int count = 0;
    const char *ptr = text;
    while(*ptr != '\0'){
        if(static_cast<unsigned char>(*ptr) == a){
            count++;
        }
        ptr++;
    }
    const char *firstPtr = strchr(text, a);
    if(firstPtr == nullptr){
        printf("Символ у тексті не зустрічається.\n");
    }else{
        int pos = static_cast<int>(firstPtr-text) + 1;
        printf("Входжень у тексті: %d, перше на позиції %d\n", count, pos);
    }
}
void readSentence(char text[]){
    string sentence, word;
    int wordCount = 0;
    bool finish = false, endDot = false;
    printf("Введіть речення (крапка після останнього слова):\n");
    while(cin >> word){//ввід з перевірками виконання умов
        wordCount++;
        if(sentence.length() <= 255){
            if(wordCount > 1)sentence += ' ';
            sentence += word;
        }
        if(word[word.length() - 1] == '.'){
            finish = true;
            break;
        }
    }
    if(finish)endDot = clearLine();
    if(!finish || endDot || !isValidText(sentence.c_str())){
        printf("Помилка: некоректне речення або перевищено 255 символів.\n");
        return;
    }
    strcpy(text, sentence.c_str());
    printf("Прочитано слів: %d\n", wordCount);
    printf("Новий текст: \"%s\"\n", text);
    printf("Довжина: %zu\n", sentence.length());
}