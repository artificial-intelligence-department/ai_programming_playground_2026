#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
using namespace std;

bool isValidText(char* text) {
    // перевірка чи закінчується крапкою
    int len = strlen(text);
    if (len==0 || text[len-1] !='.') {
        return false;
    }
    // перевірка чи тільки пробіли, букви та цифри і чи містить слово
    bool hasWord = false;
    for (int i =0; i<len-1; i++) {
        char c = text[i];
        if (isalnum(c)) {
            hasWord=true;
        } else if (c!=' ') {
            return false;
        }
    }
    return hasWord;
}

void freeWords(char **&splittedWords, int &count) {
    if(splittedWords!=nullptr) {
        for (int i =0; i<count; i++) {
            delete[] splittedWords[i];
        }
        delete[] splittedWords;
        splittedWords=nullptr;
    }
    count=0;
    
} 

char **splitWords(const char *text, int &count) {
    count=0;
    char* copy = new char[strlen(text)+1];
    strcpy(copy, text);

    char* token = strtok(copy, " .,\n\t");

    while (token != NULL) {
        count++;
        token = strtok(NULL, " .,\n\t");
    }
    strcpy(copy, text);

    char** splitted =new char*[count];
    token = strtok(copy, " .,\n\t");
    
    for(int i=0; i<count; i++) {
        splitted[i]=new char[strlen(token) + 1];
        strcpy(splitted[i], token);
        token = strtok(NULL, " .,\n\t");
    }
    delete[] copy;
    return splitted;

}

void countChars(const char *text, int &letters, int &digits, int &spaces) {
    letters=0;
    digits=0;
    spaces=0;
    for(int i=0; i<strlen(text); i++) {
        if (isalpha(*(text+i))) {
            letters++;
        } else if (isdigit(*(text+i))) {
            digits++;
        } else if (*(text+i)==' '){
            spaces++;
        }
    }
}

void showStats(const char* text, int count) {
    int symbols=strlen(text);
    int letters=0, digits=0, spaces=0;
    countChars(text, letters, digits, spaces);

    double letterspercentage=((double)letters/symbols * 100.0);
    double digitspercentage=((double)digits/symbols * 100.0);
    double spacespercentage=((double)spaces/symbols * 100.0);

    printf("Текст:\t\"%s\"\n", text);
    printf("Символів:\t%d\n", symbols);
    printf("Слів:\t\t%d\n", count);
    printf("Літер:\t\t%d (%5.1f%%)\n", letters, letterspercentage);
    printf("Цифр:\t\t%d (%5.1f%%)\n", digits, digitspercentage);
    printf("Пробілів:\t%d (%5.1f%%)\n", spaces, spacespercentage);

}

char** sortWords(char** splittedWords, int count) {
    char **sorted = new char*[count];
    for(int i =0; i<count; i++) {
        sorted[i]=splittedWords[i];
    }
    for (int i = 0; i<count-1; i++) {
        for (int j =1; j<count-i; j++) {
            if(strcmp(sorted[j-1], sorted[j])>0) {
                char* temp=sorted[j];
                sorted[j]=sorted[j-1];
                sorted[j-1]=temp;
            }
        }

    }
    return sorted;
}

void wordsTable(char** splittedWords, int count) {
    float sum=0.0;
    char *min_s=splittedWords[0];
    char *max_s=splittedWords[0];
    int min_length=256;
    int max_length=0;
    char **sortedWords = sortWords(splittedWords, count);
    printf("+----+-----------------+-------+\n");
    printf("| N  | Слово           | Довж. |\n");
    printf("+----+-----------------+-------+\n");
    for(int i=0; i<count; i++) {
        int length=strlen(splittedWords[i]);
        if(length<min_length) {
            min_length=length;
            min_s=splittedWords[i];
        }
        if(length>max_length) {
            max_length=length;
            max_s=splittedWords[i];
        }
        printf("| %2d | %-15s | %5d |\n", i+1, splittedWords[i], int(length));
        sum+=length;
    }
    printf("+----+-----------------+-------+\n");
    char* most_frequent=splittedWords[0];
    int most_frequent_counter=0;
    for(int i=0; i<count; i++) {
        int counter=0;
        for(int j=0; j<count; j++) {
            if(strcmp(sortedWords[i], sortedWords[j])==0) {
                counter++;
            }
        }
        if(counter>most_frequent_counter) {
            most_frequent_counter=counter;
            most_frequent=sortedWords[i];
        }
    }
    printf("Найдовше слово: %s (%d)\n", max_s, max_length);
    printf("Найкоротше слово: %s (%d)\n", min_s, min_length);
    printf("Cередня довжина слова %.2f\n", sum/count);
    printf("За абеткою: ");
    for(int i =0; i<count; i++) {
        printf("%s ", sortedWords[i]);
    }
    printf("\n");
    printf("Найчастіше слово: %s (%d)\n", most_frequent, most_frequent_counter);
    delete[] sortedWords;
    



}

bool isValidWord(const string &a) {
    if(a.empty() or a.length()>31) {
        return false;
    }
    for (unsigned char c : a) {
        if(!isalnum(c)) {
            return false;
        }
    }
    return true;
}

bool replaceWordsCount(char* text, string &copytext, size_t pos, string &a, string &b) {
    int replaces=0;
    while((pos=copytext.find(a, pos))!= string :: npos) {
        bool left = (pos==0) or !isalnum(copytext[pos-1]);
        bool right = (pos+a.length() == copytext.length()) or !isalnum(copytext[pos+a.length()]);
        if (left and right) {
            copytext.replace(pos, a.length(), b);
            pos+=b.length();
            replaces++;
        } else {
            pos +=a.length();
        }
        

    }
    int length=copytext.size();
    if (replaces == 0) {
        printf ("Такого слова немає в початковому реченні.\n");
        return false;

    } else if (length > 255) {
        printf("Довжина зміненого тексту перевищує 255 символів.\n");
        return false;
    } else {
        printf ("Замін виконано: %d \n", replaces);
        printf ("Було: \"%s\"\n", text);
        printf ("Стало: \"%s\"\n", copytext.c_str());
        printf ("Нова довжина: %d\n", length);
        return true;
    }
   
}

void compareTwoWords(char bufA[], char bufB[], string &a, string&b) {
    int comparison = strcmp(bufA, bufB);
    string result;
    if (comparison<0) {
        result="перше слово менше";
    } else if (comparison>0) {
        result="друге слово менше";
    } else {
        result="слова рівні";
    }
    printf("strcmp: %d -> %s\n", comparison, result.c_str());
    bool equal = (a==b);
    if (!equal) {
        printf("Рівні (==): ні\n");
    } else {
        printf("Рівні (==): так\n");
    }
    bool case_equal = (strcasecmp(bufA, bufB)==0);
    if (!case_equal) {
        printf("Рівні без урахування регістру: ні\n");
    } else {
        printf("Рівні без урахування регістру: так\n");
    }
    int a_sz = a.size();
    int b_sz = b.size();
    
    printf("Довжини: %d %d\n", a_sz, b_sz);
    string con = a + " & " + b;
    int con_sz  =con.size();
    printf("Конкатенація: \"%s\" (%d)\n", con.c_str(), con_sz);
}

int countChar (const char* text, char target) {
    int count =0;
    for (int i=0; text[i]!='\0'; i++) {
        if (text[i]==target) {
            count++;
        }
    }
    return count;
}

void charInfo(char c, char* text) {
    printf("Символ: %c\n", c);
    unsigned char ch = (unsigned char) c;
    string str_bin = "";
    for (int i =7; i>=0; i--) {
        str_bin+=(char)(((ch>>i)&1)+'0');
    }
    printf ("Код: %d (hex %#X, oct %#o, bin %s)\n", ch, ch, ch, str_bin.c_str());
    if (isalpha(c)) {
        if (c>='A' and c<='Z') {
            printf ("Тип: велика літера\n");
            printf ("Інший регістр: \'%c\'\n", c-'A'+'a');
            printf ("Наступний символ: \'%c\'\n", c+1);
        } else {
            printf ("Тип: мала літера\n");
            printf ("Інший регістр: \'%c\'\n", c-'a'+'A');
            printf ("Наступний символ: \'%c\'\n", c+1);
        }

    } else if (isdigit(c)) {
        printf ("Тип: цифра\n");
    } else if (c==' ') {
        printf ("Тип: пробіл\n");
    } else {
        printf ("Тип: інший символ\n");
    }
    int occurence = countChar(text, c);
    string copy=text;
    int pos = copy.find(c)+1;
    if (occurence>0) {
        printf ("Входжень у тексті: %d, перше на позиції %d\n", occurence, pos);
    } else {
        printf ("Такого елемента немає в тексті.\n");
    }
}

int main(){
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці):\n");
    if (fgets(text, sizeof(text), stdin)==NULL) {
        printf("Помилка зчитування тексту.\n");
        return 1;
        
    }
    char *n=strchr(text, '\n');
    if (n) {
        *n = '\0';
    }
    if (!isValidText(text)) {
        printf("Помилка: текст має складатися із латинських літер, цифр і пробілів та завершуватись крапкою.\n");
        return 1;
    }
    int count = 0;
    char **splittedWords = splitWords(text, count);
    int choice;
    do {
        printf ("========================================\nЛаскаво просимо до РЕДАКТОРА ТЕКСТОВОГО ПОВІДОМЛЕННЯ\n========================================\nМЕНЮ\n========================================\n1 - Показати текст і статистику\n2 - Таблиця слів\n3 - Замінити слово\n4 - Порівняти два слова\n5 - Інформація про символ\n6 - Ввести нове речення\n0 - Вийти\n========================================\nВаш вибір: ");
        if(scanf("%d", &choice) !=1) {
            printf("Зробіть свій вибір!\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choice)
        {
        case 1: {
            showStats(text, count);
            break;
        }
        case 2: {
            wordsTable(splittedWords, count);
            break;
        }
        case 3: {
            char bufA[32], bufB[32];
            printf("Замінити слово: ");
            if(scanf("%31s", bufA) !=1) {
                printf("Слово повинне містити латинські букви та цифри та бути довжиною до 31 символу\n");
                break;
            }
            printf("На слово: ");
            if(scanf("%31s", bufB) !=1) {
                printf("Слово повинне містити латинські букви та цифри та бути довжиною до 31 символу\n");
                break;
            }
            string a=bufA;
            string b=bufB;
            if(!(isValidWord(a) && isValidWord(b))) {
                printf("Слово повинне містити латинські букви та цифри та бути довжиною до 31 символу\n");
                break;
            } else {
                string copytext = text;
                size_t pos=0;
                if (replaceWordsCount(text, copytext, pos, a, b)) {
                    strcpy(text, copytext.c_str());
                    freeWords(splittedWords, count);
                    splittedWords=splitWords(text, count);
                
                }
                
                
            }
            break;
        }
        case 4: {
            char bufA[32], bufB[32];
            printf("Перше слово: ");
            if(scanf("%31s", bufA) !=1) {
                printf("Слово повинне містити латинські букви та цифри та бути довжиною до 31 символу\n");
                break;
            }
            printf("Друге слово: ");
            if(scanf("%31s", bufB) !=1) {
                printf("Слово повинне містити латинські букви та цифри та бути довжиною до 31 символу\n");
                break;
            }
            string a=bufA;
            string b=bufB;
            if(!(isValidWord(a) && isValidWord(b))) {
                printf("Слово повинне містити латинські букви та цифри та бути довжиною до 31 символу\n");
                break;
            } else {
                compareTwoWords(bufA, bufB, a, b);
            }

            break;
        }
        case 5: {
            char c;
            printf ("Введіть символ: ");
            if (scanf(" %c", &c)!=1) {
                printf("Непрвильний ввід символу\n");
                break;
            };
            charInfo(c, text);
            break;
        }
        case 6: {
            printf("Введіть речення (крапка після останнього слова):\n");
            string sentence="";
            string word;
            while(cin >> word) {
                sentence+=word+" ";
                if (!word.empty() && word.back()=='.') {
                    break;
                }
            }
            sentence.pop_back();
            if (sentence.size()<=255) {
                char new_sentence[256];
                snprintf(new_sentence, sizeof(new_sentence), "%s", sentence.c_str());
                if (isValidText(new_sentence)) {
                    strcpy(text, new_sentence);
                    freeWords(splittedWords, count);
                    splittedWords = splitWords(text, count);
                    printf("Прочитано слів: %d\n", count);
                    printf("Новий текст: \"%s\"\n", text);
                    int length=strlen(text);
                    printf("Довжина: %d\n", length);

                } else {
                    printf("Помилка: текст має складатися із латинських літер, цифр і пробілів та завершуватись крапкою.\n");
                    break;
                }

            }
            break;
            
        }
        default:
            printf ("Такого пункту немає в меню.\n");
            break;
        }
    } while(choice!=0);
    freeWords(splittedWords, count);
    splittedWords=0;
    printf("Дякуємо за використання нашого редактору текстового повідомлення! До нових зустрічей!\n");
    return 0;
    

}