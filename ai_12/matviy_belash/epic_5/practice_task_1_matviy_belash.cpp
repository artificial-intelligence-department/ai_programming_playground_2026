#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <string>   

bool word_valid(const char *word){

    if(*word == '\0') return false;
    for(const char *p = word; *p != '\0'; p++){
        if(!isalnum((unsigned char)*p)) return false;
    }
    return true;

}

void och_line(){        

    int c;
    while((c = getchar()) != '\n' && c != EOF){}  

}

bool read_p(char *mirror){        

    if(scanf("%32s", mirror) != 1) return false;
    och_line();
    if(strlen(mirror) > 31){
        printf("Помилка: слово довше за 31 символ.\n");
        return false;
    }
    if(!word_valid(mirror)){
        printf("Помилка: слово має складатися лише з латинських літер і цифр.\n");
        return false;
    }
    return true;

}

bool letter_valid(const char *s){

    int l_t = strlen(s);
    if(l_t < 2 || s[l_t- 1] != '.') return false;   

    bool may_letter = false;
    for(int i = 0; i < l_t - 1; i++){             
        unsigned char c = (unsigned char)s[i];
        if(isalnum(c)) may_letter = true;              
        else if(c != ' ') return false;             
    }
    return may_letter;

}

void valid_text(char *text, bool &FAIL){

    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if(fgets(text, 256, stdin) == NULL){
        printf("Помилка.\n");
        FAIL = true;
        return;
    }

    char* p = strchr(text, '\n');
    if(p != NULL){
        *p = '\0';
    }else{
        int next = getchar();                  
        if(next != '\n' && next != EOF){
            printf("Помилка: текст довший за 255 символів.\n");
            och_line();
            FAIL = true;
            return;
        }
    }

    if(!letter_valid(text)){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        FAIL = true;
        return;
    }
}

void vib_choice(int &choice){
    bool success = false;
    while(!success){
        printf("Ваш вибір: ");
        int normal = scanf("%d", &choice); 
        if(normal == EOF){                      
            choice = 0;
            return;
        }
        och_line();
        if(normal != 1){
            printf("Помилка: введіть номер пункту меню.\n");
        }else if(choice < 0 || choice > 6){
            printf("Помилка: пункту %d немає в меню.\n", choice);
        }else{
            success = true;
        }
    }
}

void printMenu(){

    printf("\n%-13s%s\n", "Пункт", "Операція");   
    printf("%-8d%s\n", 1, "Показати текст і статистику");
    printf("%-8d%s\n", 2, "Таблиця слів");
    printf("%-8d%s\n", 3, "Замінити слово");
    printf("%-8d%s\n", 4, "Порівняти два слова");
    printf("%-8d%s\n", 5, "Інформація про символ");
    printf("%-8d%s\n", 6, "Ввести нове речення");
    printf("%-8d%s\n", 0, "Вийти");

}

void countChars(const char *text, int &letters, int &digits, int &spaces){

    letters = 0; digits = 0; spaces = 0;
    for(const char* p = text; *p != '\0'; p++){
        unsigned char c = (unsigned char)*p;
        if(isalpha(c)) letters++;
        else if(isdigit(c)) digits++;
        else if(c == ' ') spaces++; 
    }
     
}

void statistic(const char text[], int &word_numb){

    printf("\n%s\t\"%s\"\n", "Текст:", text); 
    printf("Символів: %5zu\n", strlen(text));
    printf("Слів:     %5d\n", word_numb);

    int letters = 0, digits = 0, spaces = 0;
    countChars(text, letters, digits, spaces);
    printf("Літер:    %5d (%5.1f%%)\n", letters, letters * 100.0 / strlen(text));
    printf("Цифр:     %5d (%5.1f%%)\n", digits, digits * 100.0 / strlen(text));
    printf("Пробілів: %5d (%5.1f%%)\n", spaces, spaces * 100.0 / strlen(text));

}

char **splitWords(const char *text, int &word_numb){

    word_numb = 0;

    char text_copy[256];
    strcpy(text_copy, text);

    char *w = strtok(text_copy, " .\n");
    while(w != NULL){
        word_numb++;
        w = strtok(NULL, " .\n");
    }

    char **words = new char*[word_numb];

    strcpy(text_copy, text);           
    int i = 0;
    w = strtok(text_copy, " .\n");
    while(w != NULL){
        words[i] = new char[strlen(w) + 1];
        strcpy(words[i], w);
        i++;
        w = strtok(NULL, " .\n");
    }
    return words;

}

void freeWords(char **&words, int &word_numb){

    for(int i = 0; i < word_numb; i++){
        delete[] words[i];
    }
    delete[] words;
    words = nullptr;
    word_numb = 0;

}

void words_table(char **words, int word_numb){

    printf("\n+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for(int i = 0; i < word_numb; i++){
        printf("| %2d | %-15s | %5zu |\n", i + 1, words[i], strlen(words[i]));
    }
    printf("+----+-----------------+-------+\n");

    int longest = 0, shortest = 0; 
    float sum = 0;
    for(int i = 0; i < word_numb; i++){
        size_t len = strlen(words[i]);
        sum += len;
        if(len > strlen(words[longest])) longest = i;     
        if(len < strlen(words[shortest])) shortest = i;   
    }
    printf("Найдовше слово: %s (%zu)\n", words[longest], strlen(words[longest]));
    printf("Найкоротше слово: %s (%zu)\n", words[shortest], strlen(words[shortest]));
    printf("Середня довжина: %.2f\n", sum / word_numb);

    char **words_sort = new char*[word_numb];
    for(int i = 0; i < word_numb; i++){
        words_sort[i] = words[i];
    }

    for(int i = 0; i < word_numb - 1; i++){
        int min = i;                             
        for(int j = i + 1; j < word_numb; j++){
            if(strcmp(words_sort[j], words_sort[min]) < 0){
                min = j;                          
            }
        }
        char *tit = words_sort[i];                     
        words_sort[i] = words_sort[min];
        words_sort[min] = tit;
    }

    printf("За абеткою: ");
    for(int i = 0; i < word_numb; i++){
        printf("%s ", words_sort[i]);
    }
    printf("\n");


    int lucky = 1, lucky_k = 0;
    int lucky_i = 1;
    for(int i = 1; i < word_numb; i++){
        if(strcmp(words_sort[i], words_sort[i - 1]) == 0) lucky_i++;
        else lucky_i = 1;
        if(lucky_i > lucky){        
            lucky = lucky_i;
            lucky_k = i;
        }
    }
    printf("Найчастіше слово: %s (%d)\n", words_sort[lucky_k], lucky);

    delete[] words_sort;   

}

void mirror_words(char *text, char **&words, int &word_numb){

    char mirror_word[33], d_word[33];
    printf("\nЗамінити слово: ");
    if(!read_p(mirror_word)) return; 
    printf("На слово: ");
    if(!read_p(d_word)) return; 

    std::string was = text;      
    std::string work = " " + was;  
    work[work.length() - 1] = ' ';   
    std::string old_m_w = mirror_word;    
    std::string mirror_word_s = " " + old_m_w + " ";
    std::string old_d_w = d_word;  
    std::string d_word_s = " " + old_d_w + " ";

    int n_z = 0;
    size_t pos = work.find(mirror_word_s); 
    while(pos != std::string::npos){                          
        work.replace(pos, mirror_word_s.length(), d_word_s);       
        n_z++;
        pos = work.find(mirror_word_s, pos + d_word_s.length() - 1);  
    }

    work[work.length() - 1] = '.';
    work.erase(0, 1);
    if(work.length() > 255){
        printf("Помилка: результат перевищує 255 символів, текст не змінено.\n");
        return;
    }

    strcpy(text, work.c_str());
    freeWords(words, word_numb);
    words = splitWords(text, word_numb);

    printf("Замін виконано: %d\n", n_z);
    printf("Було:  \"%s\"\n", was.c_str());
    printf("Стало: \"%s\"\n", work.c_str());
    printf("Нова довжина: %zu\n", work.length());

}

void different_words(){

    char word_one[33], word_two[33];
    printf("\nПерше слово: ");
    if(!read_p(word_one)) return;
    printf("Друге слово: ");
    if(!read_p(word_two)) return;

    std::string a = word_one, b = word_two;
    int tt = 0;
    const char *m_x;
    if(strcmp(word_one, word_two) > 0){
        tt = 1;
        m_x = "перше слово більше";
    }else if(strcmp(word_one, word_two) < 0){
        tt = -1;  
        m_x = "перше слово менше";
    }else{
        tt = 0;
        m_x = "слова однакові";
    }     

    bool riv = (a.length() == b.length());   
    if(riv){
        for(size_t i = 0; i < a.length(); i++){
            if(tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])){
                riv = false;     
                break;              
            }
        }
    }

    std::string a_plus_b = a + " & " + b;  
    
    printf("%s %d -> %s\n","strcmp:", tt, m_x);
    printf("%s %s\n", "Рівні (==):", a == b ? "так" : "ні");
    printf("%s %s\n", "Рівні без урахування регістру:", riv ? "так" : "ні");
    printf("%s %zu і %zu\n", "Довжини:", a.length(), b.length());
    printf("%s \"%s\" (%zu)\n", "Конкатенація:", a_plus_b.c_str(), a_plus_b.length());

}

void symbol_information(const char *text){

    char sym;
    printf("\nВведіть символ: ");
    if(scanf("%c", &sym) != 1) return;
    if(sym == '\n'){                     
        printf("Помилка: символ не введено.\n");
        return;
    }
    och_line();

    unsigned char sym_copy = (unsigned char)sym;
    if(sym_copy > 127){
        printf("Помилка: введіть символ.\n");
        return;
    }

    printf("%s '%c'\n", "Символ:", sym);
    printf("Код: %d (hex 0x%x, oct 0%o, bin ", sym_copy, sym_copy, sym_copy);
    for(int i = 0; i < 8; i++){
        printf("%d", (sym_copy >> (7 - i)) & 1);
    }
    printf(")");

    printf("\nТип: ");
    if(isupper(sym_copy)){
        printf("велика літера\n");
    }else if(islower(sym_copy)){
        printf("мала літера\n");
    }else if(isdigit(sym_copy)){
        printf("цифра\n");
    }else if(isspace(sym_copy)){
        printf("пробільний символ\n");
    }else{
        printf("інший символ\n");
    }

    if(isalpha(sym_copy)){                         
        if(isupper(sym_copy)) printf("Інший регістр: '%c'\n", sym + 32);
        else printf("Інший регістр: '%c'\n", sym - 32);
        printf("Наступний символ: '%c'\n", sym + 1);
    }

    int n_v = 0, pos = 0;
    for(int i = 0; text[i] != '\0'; i++){
        if(text[i] == sym){
            n_v++;
            if(n_v == 1) pos = i + 1;
        }
    }
    if(n_v == 0) printf("У тексті цей символ не зустрічається.\n");
    else printf("%s %d, %s %d\n", "Входжень у тексті:", n_v, "перше на позиції", pos);

}

void new_text(char *text, int &word_numb, char **&words){

    printf("\nВведіть речення (крапка після останнього слова):\n");
    std::string te, wo;
    while(std::cin >> wo){
        if(!te.empty()) te += " ";  
        te += wo;
        if(wo[wo.length() - 1] == '.') break; 
    }
    std::cin.ignore(10000, '\n');

    if(te.length() > 255){
        printf("Помилка: речення довше за 255 символів, текст не змінено.\n");
        return;
    }
    if(!letter_valid(te.c_str())){
        printf("Помилка: текст має складатися з латинських літер, цифр і пробілів та завершуватися крапкою.\n");
        return;
    }

    strcpy(text, te.c_str());
    freeWords(words, word_numb);
    words = splitWords(text, word_numb);

    printf("%s %d\n%s \"%s\"\n", "Прочитано слів:", word_numb, "Новий текст:", text);
    printf("%s %zu\n", "Довжина:", strlen(text));

}

int main(){

    char text[256];
    int word_numb = 0;

    bool FAIL = false;
    valid_text(text, FAIL);
    if(FAIL) return 0;

    char **words = splitWords(text, word_numb);

    int choice = 0;
    do{

        printMenu();
        vib_choice(choice);

        switch(choice){

            case 1: statistic(text, word_numb); break;

            case 2: words_table(words, word_numb); break;

            case 3: mirror_words(text, words, word_numb); break;

            case 4: different_words(); break;

            case 5: symbol_information(text); break;

            case 6: new_text(text, word_numb, words); break;

            default: freeWords(words, word_numb); return 0;

        }

    }while(choice != 0);

    freeWords(words, word_numb);

    return 0;
}