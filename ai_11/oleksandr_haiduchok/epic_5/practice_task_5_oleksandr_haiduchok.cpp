#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;
// функція перевірки за допомогою команд біблшотеки
bool Perevirka(char *text){
    int i = 0;
    if((int)strlen(text) == 0 || text[(int)strlen(text) -1] != '.'){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return 0;
    }
    while(text[i] != '\0'){
        //використовую для коректної перевірки символів
        unsigned char let = (unsigned char)text[i];
        bool check = false;
        if(isalpha(let) || isdigit(let) || isspace(let) || let == '.'){
        check = true;
        }
        if(check == false){
            printf("%s", "Ви ввели некоректний текст\n");
            return 0;
        }
    i++;
}
return 1;
}
//розділяю слова, тут же роблю динамічний масив, зважаю на межі
char**splitWords(const char *text, int &count){
    char textcopy[256];
    count = 0;
    for(int k = 0; k < strlen(text); k++){
        textcopy[k] = text[k];
    }
    textcopy[strlen(text)] = '\0';
    char **words = new char*[128];
    int n = 0;
    char *h = strtok(textcopy, " ");
    while(h != NULL){
        if(strlen(h) > 0 && h[strlen(h) - 1] == '.'){
            h[strlen(h) - 1] = '\0';
        }
        words[n] = new char[strlen(h) + 1];
        strcpy(words[n], h);
        n++;
        h = strtok(NULL, " ");
        count++;
    }
    return words;
}
//підрахунок символів за допомогою вказівників
void countChars(const char *text, int &letters, int &digits, int &spaces){
    const char *point = text;
    while(*point != '\0'){
        if(isalpha(*point)){
            letters++;
        }
        if(isdigit(*point)){
            digits++;
        }   
        if(isspace(*point)){
            spaces++;
        }    
        point++;
    }
}
//вивід інформації з точністю у десяті
void Punkt1(char *text, int count, int letters, int digits, int spaces){
    countChars(text, letters, digits, spaces);
    float pers1 = (letters * 100.0f)/(strlen(text));
    float pers2 = (digits * 100.0f)/(strlen(text));
    float pers3 = (spaces * 100.0f)/(strlen(text));
    printf("Текст:\t\t\"%s\"" "\n", text);
    printf("Символів:\t%d" "\n", ((int)strlen(text)));
    printf("Слів:\t\t%d" "\n", count);
    printf("Літер:\t\t%d (%3.1f%%)" "\n", letters, pers1);
    printf("Цифр:\t\t%d (%3.1f%%)" "\n", digits, pers2);
    printf("Пробілів:\t%d (%3.1f%%)" "\n", spaces, pers3);


}
//інформація про кожне слово, сортую слова бульбашкою та зважаю на умови завдання
void Punkt2(char**words, int count){
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    int longest = strlen(words[0]);
    int shortnes = strlen(words[0]);
    double seredne = 0;
    int check1 = 0;
    int check2 = 0;
    
    for(int i = 0; i < count; i++){
        int d = i + 1;
        printf("| %-2d | %-15s | %5d |\n", d, words[i], (int)strlen(words[i]));
        if(longest < strlen(words[i])){
            longest = strlen(words[i]);
            check1 = i;
        }
        if(shortnes > strlen(words[i])){
            shortnes = strlen(words[i]);
            check2 = i;
        }
        seredne+=strlen(words[i]);
    }
    printf("+----+-----------------+-------+\n");
    seredne = seredne/count;
    int maxpovt = 0;
    int maxindex = 0;
    char **sortwords = new char*[count];
    for(int k = 0; k < count; k++){
        sortwords[k] = words[k];
    }
    for(int f = 0; f < count - 1; f++){
        for(int s = 0; s < count - f - 1; s++){
            if(strcmp(sortwords[s], sortwords[s + 1]) > 0){ 
            char *temp = sortwords[s];
            sortwords[s] = sortwords[s + 1];
            sortwords[s + 1] = temp;
            }
        }
    }
    for(int g = 0; g < count; g++){
        int maxnow = 0;
        for(int h = 0; h < count; h++){
            if(strcmp(sortwords[g], sortwords[h]) == 0){
                maxnow++;
            }
        }
        if(maxnow > maxpovt){
            maxpovt = maxnow;
            maxindex = g;
         }
    }
    printf("Найдовше слово: %s (%d)\n", words[check1], longest);
    printf("Найкоротше слово: %s (%d)\n", words[check2], shortnes);
    printf("Середня довжина: %.2f\n", seredne);
    printf("За абеткою: ");
    for(int x = 0; x < count; x++){
        printf("%s ", sortwords[x]);
        if(x == count - 1){
            printf("\n");
        }
    }
    printf("Найчастіше слово: %s (%d)\n", sortwords[maxindex], maxpovt);
    delete[] sortwords; // обовʼязково звільняю масив
}
// заміна слова командами, заодно валідація, використав перетворення масиву чарів в рядок і навпаки
void Punkt3(char text[], char **words, int &count){
    string origin(text);
    string textnow(text);
    char temp1[32];
    char temp2[32];
    printf("Замінити слово: ");
    scanf("%31s", temp1);
    while (getchar() != '\n');
    for(int h = 0; temp1[h] != '\0'; h++){
        if(!isalnum((unsigned char)temp1[h])){
        printf("Помилка: слово має складатися з латинських літер, цифр\n");
        return;
        }
    }
    printf("На слово: ");
    scanf("%31s", temp2);
    while (getchar() != '\n');
    for(int k = 0; temp2[k] != '\0'; k++){
        if(!isalnum((unsigned char)temp2[k])){
            printf("Помилка: слово має складатися з латинських літер, цифр\n");
            return;
        }
    }
    string from(temp1);
    string to(temp2);
    int pos = textnow.find(from);
    if(pos < 0){
        printf("Слово %s не знайдене\n", temp1);
        return;
    }
    int rah = 0;
    while(pos >= 0){
        textnow.replace(pos, from.length(), to);
        rah++;
        pos = textnow.find(from, pos + to.length());
    }
    if(textnow.length() >= 256){
        printf("Помилка, новий текст містить більше 255 символів\n");
        return;
    }
    printf("Замін виконано: %d\n", rah);
    printf("Було:  \"%s\"\n", origin.c_str());
    printf("Стало: \"%s\"\n", textnow.c_str());
    printf("Нова довжина: %d\n", (int)textnow.length());
    strcpy(text, textnow.c_str());
}
// порівняння слів, порівняння двома способами та конкатенація
void Punkt4(char text[], char **words, int &count){
    char word1[32];
    char word2[32];
    printf("Перше слово: ");
    scanf("%31s", word1);
    while (getchar() != '\n');
    for(int h = 0; word1[h] != '\0'; h++){
        if(!isalnum(word1[h])){
        printf("Помилка: слово має складатися з латинських літер, цифр\n");
        return;
        }
    }
    printf("Друге слово: ");
    scanf("%31s", word2);
    while (getchar() != '\n');
    for(int g = 0; word2[g] != '\0'; g++){
        if(!isalnum(word2[g])){
        printf("Помилка: слово має складатися з латинських літер, цифр\n");
        return;
        }
    }
    int res = 0;
    res = strcmp(word1, word2);
    if(res < 0){
    printf("strcmp: -1 -> перше слово менше\n");
    }
    if(res == 0){
    printf("strcmp: 0 -> слова однакові\n");
    }
    if(res > 0){
    printf("strcmp: 1 -> перше слово більше\n");
    }
    string slovo1(word1);
    string slovo2(word2);
    if(slovo1 == slovo2){
        printf("Рівні (==): так\n");
    }
    if(slovo1 != slovo2){
        printf("Рівні (==): ні\n");
    }
    string mensheA = slovo1;
    string mensheB = slovo2;
    for(int i = 0; i < mensheA.length(); i++){
        mensheA[i] = tolower(mensheA[i]);
    }
    for(int i = 0; i < mensheB.length(); i++){
        mensheB[i] = tolower(mensheB[i]);
    }
    if(mensheA == mensheB){
        printf("Рівні без урахування регістру: так\n");
    }
    else{
        printf("Рівні без урахування регістру: ні\n");
    }
    printf("Довжини: %d і %d\n", (int)mensheA.length(), (int)mensheB.length());
    string concat = slovo1 + " & " + slovo2;
    printf("Конкатенація: \"%s\" (%d)\n", concat.c_str(), (int)concat.length());
    }
    //вивід інформації про символ, його код в різних системах числення
void Punkt5(char text[], char **words, int &count){
    printf("Введіть символ: ");
    char symbol;
    scanf("%c", &symbol);
    if(symbol != '\n'){
    while(getchar() != '\n');
    }
    int num = (unsigned char)symbol;
    printf("Символ: '%c'\n", symbol);
    char binary[9];
    binary[8] = '\0';
    int temp = num;
    for(int i = 7; i >= 0; i--){
        binary[i] = (temp & 1) + '0';
        temp = temp >> 1;
    }
    printf("Код: %d (hex 0x%x, oct 0%o, bin %s)\n", num, num, num, binary);
    if(isupper(num)){
        printf("Тип: велика літера\n");
        printf("Інший регістр: '%c'\n", tolower(num));
    }
    else if(islower(num)){
        printf("Тип: мала літера\n");
        printf("Інший регістр: '%c'\n", toupper(num));
    }
    else if(isdigit(num)){
        printf("Тип: цифра\n");
    }
    else if(isspace(num)){
        printf("Тип: пробіл\n");
    }
    else{
        printf("Тип: інший тип\n");
    }
    char nextsymbol = symbol + 1;
    printf("Наступний символ: '%c'\n", nextsymbol);
    int countsym = 0;
    int index = 0;
    char *found = strchr(text, symbol);
    if(found != nullptr){
        index = found - text;
        char *point = found;
        while(point != nullptr){
            countsym++;
            point = strchr(point+1,symbol);
        }
    }
    if(countsym > 0){
        printf("Входжень у тексті: %d, перше на позиції %d\n", countsym, index + 1);
    }
    else{
        printf("у тексті не зустрічається\n");
    }
}
//введення нового речення, валідація та мінімальна інформація
void Punkt6(char text[], char **words, int &count){
    char newtext[256] = "";
    printf("Введіть речення (крапка після останнього слова):");
    int countword = 0;
    string temp;
    while(cin >> temp){
        int len = (int)temp.length() + (int)strlen(newtext) + (countword > 0 ? 1 : 0);
        if(len >= 256){
            printf("Помилка, текст містить більше 255 символів\n");
            while(getchar() != '\n');
            return;
        }
        if(countword > 0){
            strcat(newtext, " ");
        }
        strcat(newtext, temp.c_str());
        countword++;
        if(temp[temp.length() - 1] == '.'){
            break;
        }
    }
    while(getchar() != '\n');
    if(!Perevirka(newtext)){
        return;
    }
    printf("Прочитано слів: %d\n", countword);
    printf("Новий текст: \"%s\"\n", newtext);
    printf("Довжина: %d\n", (int)strlen(newtext));
    strcpy(text, newtext);
}
// видалення динамічного масиву
void Delete(char **&words, int &count){
    for(int g = 0; g < count; g++){
        delete[] words[g];
    }
    delete[] words;
    words = nullptr;
}


int main(){
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці):");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    if(!Perevirka(text)){
        return 0;
    }
    int letters = 0;
    int digits = 0;
    int spaces = 0;
    int count = 0;
    int choice = 0;
    char **words = splitWords(text, count);
    // цикл ду вайл з поверненням меню у разі поганого вводу
    do{
        printf("1\t\tПоказати текст і статистику\n");
        printf("2\t\tТаблиця слів\n");
        printf("3\t\tЗамінити слово\n");
        printf("4\t\tПорівняти два слова\n");
        printf("5\t\tІнформація про символ\n");
        printf("6\t\tВвести нове речення\n");
        printf("0\t\tВийти\n");
        printf("Ваш вибір: ");
    
    char res = scanf("%d", &choice);
    if(res != 1){
        printf("Помилка: введіть номер пункту меню.\n");
        while(getchar() != '\n');
        choice = -1;
        continue;
    }
    if(choice < 0 || choice > 6){
        printf("Помилка: пункту %d немає в меню.\n", choice);
        while(getchar() != '\n');
        choice = -1;
        continue;
    }
    while(getchar() != '\n');

    switch(choice){
    case -1: printf("Помилка, ви не вибрали пункт меню\n"); break;
    case 0: Delete(words, count); return 0;
    case 1: Punkt1(text, count, letters, digits, spaces); break;
    case 2: Punkt2(words, count); break;
    case 3: Punkt3(text, words, count);
    Delete(words, count);
    words = splitWords(text, count);
    break;
    case 4: Punkt4(text, words, count); break;
    case 5: Punkt5(text, words, count); break;
    case 6: Punkt6(text, words, count);
    Delete(words, count);
    words = splitWords(text, count);
    break;
    }
    }
    while(choice != 0);
    Delete(words, count);
    return 0;
    }
