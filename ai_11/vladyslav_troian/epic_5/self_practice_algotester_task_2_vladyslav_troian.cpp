#include <iostream>
#include <cstring>
using namespace std;

int lower(int min, int c)
{
    if (min > c){
        return c;
    } else return min;
}

int main()
{
    const int n = 100001;
    char first[n] = {0};
    char second[n] = {0};
    scanf("%s", first);
    scanf("%s", second);
    
    int k = -1;
    int firlen = strlen(first);
    int seclen = strlen(second);
    int min = firlen;

    for (int i = 0; i < seclen; i++){
        for (int j = k+1; j < firlen; j++){
            if (first[j] < second[i]){
                min = lower(min, j-i);
                break;
            }
        }
        k++;
        while (k < firlen && (first[k] != second[i])){
            k++;
        }
        if (k == firlen){
            break;
        }
        if (i+1 < seclen){
            min = lower(min, firlen - (i+1));
        }
    }
    cout << min << endl;
    return 0;
}