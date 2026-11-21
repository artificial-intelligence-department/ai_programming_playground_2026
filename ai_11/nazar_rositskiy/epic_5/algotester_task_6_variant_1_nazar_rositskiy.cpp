#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// Функція порівняння потрібна лише для qsort, щоб розв'язати проблему "Ліміту часу" на великих тестах
int compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

int main(){
    int n, k;

    cin >> n >> k;

    char s[n][11];
    char letters[30];
    letters[0] = '\0';

    //від слів і змінення всіх букв на маленьке
    for(int i = 0; i < n; i++){
        cin >> s[i];
        for(int j = 0; j < strlen(s[i]); j++){
            if(isupper(s[i][j])){
                s[i][j] = s[i][j] + 32;
            }
        }
    }

    // Сортуємо слова
    qsort(s, n, sizeof(s[0]), compare);

    for(int i = 0; i < n; i++){
        int count = 1;
        
        // Рахуємо однакові слова
        while(i + count < n && strcmp(s[i], s[i + count]) == 0){
            count++;
        }
        
        // Якщо слово зустрічається >= k разів
        if(count >= k){
            //проходимо по кожній літери слово
            for(int j = 0; s[i][j] != '\0'; j++){
                char ch = s[i][j];
                
                //перевіряємо чи вона використовувалась
                bool used = false;
                for(int l = 0; letters[l] != '\0'; l++){
                    if(letters[l] == ch){
                        used = true;
                        break;
                    }
                }
                
                //Якщо не використовувалась то додаємо в масив
                if(!used){
                    int len = strlen(letters);
                    letters[len] = ch;
                    letters[len + 1] = '\0';
                }
            }
        }
        
        i = i + (count - 1);
    }
    
    // Сортування зібраних букв від 'z' до 'a'
    int m = strlen(letters);
    for(int i = 0; i < m - 1; i++){
        for(int j = i + 1; j < m; j++){
            if(letters[i] < letters[j]){
                char temp = letters[i];
                letters[i] = letters[j];
                letters[j] = temp;
            }
        }
    }


    
    if(m == 0){
        cout << "Empty!" << endl;
    } else {
        cout << m << endl;
        for(int i = 0; i < m; i++){
            cout << letters[i];
            if(i < m - 1) cout << " ";
        }
    }
}