#include <stdio.h>
#include <string.h>

bool is_Palindrome(char* word){
    int size = strlen(word);
    int k = size/2;
    bool palindrome = 1;
    if (size<2) return 0;
    for (int i =0; i<k; i++){
        if (word[i]!=word[size - 1 -i]) {
            palindrome=0;
            break;
        }
    }
    return palindrome;
}

int main(){
    printf("Введіть рядок (до 255 символів)\n");
    char sentence [256];
    fgets(sentence, sizeof(sentence), stdin);
    
    char* token = strtok(sentence, " .\n");
    int count = 0;
    
    while (token!=NULL){
        
        if (is_Palindrome(token)){
            count++;
            printf("%s ", token);
        }
        token=strtok(NULL, " .\n");
    }
    if (count==0){
       printf("Жодного паліндрому у рядку\n"); 
    }
    
    return 0;
}