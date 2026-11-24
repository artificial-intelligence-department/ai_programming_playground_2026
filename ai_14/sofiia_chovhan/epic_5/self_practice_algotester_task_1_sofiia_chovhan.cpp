/*Algotester self practice 
Sofiia Chovhan */
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

int main() {
    char word[1025];
    int count = 0;

    while (scanf("%1024s", word) == 1) {
        int left = 0;
        int right = strlen(word) - 1;
        bool palindrome = true;

        while (left < right) {
            if (tolower(word[left]) != tolower(word[right])) {
                palindrome = false;
                break;
            }
            left++;
            right--;
        }

        if (palindrome) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}