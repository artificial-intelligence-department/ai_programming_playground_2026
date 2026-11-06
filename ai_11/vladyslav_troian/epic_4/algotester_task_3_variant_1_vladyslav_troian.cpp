#include <iostream>
using namespace std;

int main()
{
    int N;
    cin >> N;
    cin.ignore();
    int count = 0;
    char words[10000] = {'\0'};
    for (int j = 0; j < N; j++){
        cin.getline(words, 10000);
        for (int i = 0; i < 10000; i++){
            if (i+1 < 10000 && words[i] == '#' && words[i+1] != '#'){
                count++;
            } else if (words[i] == '\0'){
                break;
            }
        }
    }
    cout << count << endl;
    return 0;
}