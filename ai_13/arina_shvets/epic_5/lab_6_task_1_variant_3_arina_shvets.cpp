#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

int main(){
    char text[258];

    if (fgets(text, sizeof(text), stdin) == nullptr){
        return 0;
    }

    char word[256];
    int wordLength = 0;
    int digits = 0;

    for (int i = 0; ; ++i){
        char c = text[i];
        bool endOfWord = (c == ' ' || c == '.' || c == '\n' || c == '\0');

        if (endOfWord){
            if (wordLength > 0){
                word[wordLength] = '\0';
                if (digits == 1){
                    printf("%s\n", word);
                }
            }
            wordLength = 0;
            digits = 0;

            if (c == '.' || c == '\n' || c == '\0'){
                break;
            }
        } else{
            word[wordLength++] = c;
            if (isdigit(static_cast<unsigned char>(c))){
                ++digits;
            }
        }
    }

    return 0;
}