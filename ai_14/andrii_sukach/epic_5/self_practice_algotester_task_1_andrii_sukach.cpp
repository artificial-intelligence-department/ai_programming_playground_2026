/* Задача: снігурочка(Алготестер)
Виконавець: Андрій Сукач*/
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(){
   string word;
   int words;
   string space;
int count = 0;
while (cin >> word) {
    if (!space.empty()) {//пробіл перед словом, якщо newText ще не порожній:
    space += " ";
    }
    space += word;
   if (word != ".") {
    words++;
}

for (int i = 0; i < (int)word.length(); i++) {
    word[i] = tolower((unsigned char)word[i]);
}


bool isPalin = true;
int left = 0;
int right = word.length() - 1;

while(left < right) {
    if (word[left] != word[right]) {
        isPalin = false; 
        break;
    }
    left++; right--;
}
if (isPalin) count++;
}
cout << count;

return 0;
}