/*Задача 0445 - "Буквозабирання"
Максімко Павло - СШІ-13*/

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_LEN = 500005;

int main()
{
    int test;
    cin >> test;

    char start_text[MAX_LEN];
    char end_text[MAX_LEN];

    for(int i = 0; i < test; i++)
    {
        cin >> start_text >> end_text;

        int start_length = strlen(start_text);
        int end_length = strlen(end_text);
        int moves = start_length - end_length;

        int mid = moves / 2;
        bool sergei_wins = false;

        if(moves == 0)
        {
            sergei_wins = (strcmp(start_text, end_text) == 0);
        }
        else if(moves % 2 == 1)
        {
            sergei_wins = (strncmp(start_text + mid, end_text, end_length) == 0) && (strncmp(start_text + mid + 1, end_text, end_length) == 0);
        }
        else
        {
            sergei_wins = (strncmp(start_text + mid, end_text, end_length) == 0) || ((strncmp(start_text + mid - 1, end_text, end_length) == 0) && (strncmp(start_text + mid + 1, end_text, end_length) == 0));
        }

        if(sergei_wins)
        {
            cout << "Sergei" << endl;
        }
        else
        {
            cout << "Larry" << endl;
        }
    }
    return 0;
}