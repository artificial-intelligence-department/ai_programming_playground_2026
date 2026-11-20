/*Лабораторна 6 задача 1 варіант 12
Максімко Павло - СШІ-13*/

#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX = 256;

bool validText(const char *text);
bool isSymbol(char symb);
void merge(char *text, int left, int right, int mid);
void mergeSort(char *text, int left, int right);

int main()
{
    char text[MAX];
    if(fgets(text, sizeof(text), stdin) == nullptr) 
    {
        printf("Завершення програми! Кінець вводу. \n");
        return 0;
    }
    char *enter = strchr(text, '\n');
    if(enter != nullptr) *enter = '\0';
    else
    {
        int ch = getchar();
        if(ch != '\n' && ch != EOF)
        {
            printf("Помилка: Текст повинен не перевищувати %d символів!\n", MAX - 1);
            return 1;
        }
    }
    if(!validText(text))
    {
        printf("Помилка: Текст повинен складатися лише з латинських символів, цифр або пробілів і мати крапку в кінці!\n");
        return 1;
    }
    printf("Непосортований рядок: %s \n", text);
    int i = 0;
    bool word = false;
    int start = -1, end = -1;
    while(text[i] != '.')
    {
        if(isSymbol(text[i]) && !word)
        {
            start = i;
            word = true;
        }
        if(!isSymbol(text[i]) && word)
        {
            end = i - 1;
            word = false;
        }
        if(start != -1 && end != -1)
        {
            mergeSort(text, start, end);
            start = -1;
            end = -1;
        }
        i++;
    }
    if(word)
    {
        end = i - 1;
        mergeSort(text, start, end);
    }
    printf("Посортований рядок: %s \n", text);
    return 0;
}

bool validText(const char *text)
{
    bool alnum = false;
    int length = strlen(text);
    for(int i = 0; i < length; i++)
    {
        if(isalnum((unsigned char)text[i])) alnum = true;
        if(i != (length - 1) && (!isalnum((unsigned char)text[i]) && text[i] != ' ')) return false;
        else if(i == (length - 1) && text[i] != '.') return false; 
    }
    if(alnum) return true;
    else return false;
}

bool isSymbol(char symb)
{
    return (symb != ' ' && symb != '.');
}

void merge(char *text, int left, int right, int mid)
{
    char t[MAX];
    int i = left;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= right)
    {
        if(text[i] <= text[j])
        {
            t[k] = text[i];
            i++;
        }
        else 
        {
            t[k] = text[j];
            j++; 
        }
        k++;
    }

    while(i <= mid)
    {
        t[k] = text[i];
        k++;
        i++;
    }

    while(j <= right)
    {
        t[k] = text[j];
        k++;
        j++;
    }

    for(int l = 0; l < k; l++)
    {
        text[left + l] = t[l];
    }
}

void mergeSort(char *text, int left, int right)
{
    if(left >= right)
    {
        return;
    }
    
    int mid = left + (right - left) / 2;
    mergeSort(text, left, mid);
    mergeSort(text, mid + 1, right);
    merge(text, left, right, mid); 
}