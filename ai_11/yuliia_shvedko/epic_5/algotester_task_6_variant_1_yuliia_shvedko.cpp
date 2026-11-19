#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdio>
using namespace std;

void quickSort(char **a, int l, int h)
{
    while(l < h)
    {
        char *pivot = a[l + (h - l) / 2];
        int i = l;
        int j = h;
        while(i <= j)
        {
            while(strcmp(a[i], pivot) < 0)
            i++;
            while(strcmp(a[j], pivot) > 0)
            j--;
            if(i <= j)
            {
                char *t = a[i];
                a[i] = a[j];
                a[j] = t;
                i++;
                j--;
            }
        }
        if(j - l < h - i)
        {
            quickSort(a, l, j);
            l = i;
        }
        else
        {
            quickSort(a, i, h);
            h = j;
        }
    }
}

int main()
{
    int n;
    int k;
    cin >> n >> k;
    char **words = new char*[n];
    for(int i = 0; i < n; i++)
    {
        words[i] = new char[15];
        scanf("%14s", words[i]);
        for(size_t j = 0; j < strlen(words[i]); j++)
        words[i][j] = tolower(words[i][j]);
    }
    quickSort(words, 0, n - 1);
    bool a[26] = {false};
    int count = 1;
    for(int i = 0; i < n; i++)
    {
        if(i + 1 < n && strcmp(words[i], words[i + 1]) == 0)
        count++;
        else 
        {
            if(count >= k)
            {
                for(size_t j = 0; j < strlen(words[i]); j++)
                a[words[i][j] - 'a'] = true;
            }
            count = 1;
        }
    }
    int c = 0;
    for(int i = 0; i < 26; i++)
    {
        if(a[i])
        c++;
    }
    if(c > 0)
    {
        cout << c << endl;
        for(int i = 25; i >=0; i--)
        {
            if(a[i])
            cout << static_cast<char>('a' + i) << " ";
        }
    }
    else
    cout << "Empty!" << endl;
    for(int i = 0; i < n; i++)
    delete[] words[i];
    delete[] words;
    return 0;
}