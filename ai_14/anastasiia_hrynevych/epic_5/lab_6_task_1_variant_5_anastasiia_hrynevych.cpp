#include <iostream>
#include <cstring> 
#include <cctype>
#include <cstdio> 

using namespace std;

int main() {

    char s[256];
    char letters[256] = ""; 
    char digits[256] = "";  
    char result[515] = "";  

    printf("Введіть рядок (зі словами та пробілами), який закінчується крапкою:\n");
    fgets(s, sizeof(s), stdin); 

    int l_idx = 0;
    int d_idx = 0;

    
    for (int i = 0; s[i] != '\0' && s[i] != '.'; i++) {
        if (isdigit((unsigned char)s[i])) {
            digits[d_idx++] = s[i];
        } 
        else if (!(isspace((unsigned char)s[i]))) {
            letters[l_idx++] = s[i];
        }
    }

    
    letters[l_idx] = '\0';
    digits[d_idx] = '\0';

    
    strcpy(result, letters);  
    strcat(result, digits);  
    strcat(result, ".");  

    printf("Перетворений рядок:\n%s\n", result);

    return 0;
}