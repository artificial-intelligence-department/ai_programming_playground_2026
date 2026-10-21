/*Задача 0173 - Спостерігачі
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    const int TIME_MAX = 72000; //20 * 60 * 60
    const int TIME_MIN = 28800; //8 * 60 * 60

    const int H_TO_S = 3600;
    const int M_TO_S = 60;

    const int TIME = TIME_MAX - TIME_MIN;

    int h1, m1, s1;
    int h2, m2, s2;

    bool time_observed[TIME] = {0};
    for(int i = 0; i < n; i++)
    {
        cin >> h1 >> m1 >> s1 >> h2 >> m2 >> s2;
        int time1 = h1 * H_TO_S + m1 * M_TO_S + s1 - TIME_MIN;
        int time2 = h2 * H_TO_S + m2 * M_TO_S + s2 - TIME_MIN;
        for(int j = time1; j < time2; j++)
        {
            time_observed[j] = 1;
        }
    }

    int time = 0;
    for(int i = 0; i < TIME; i++)
    {
        if(time_observed[i] == 0) time++;
    }

    cout << time << endl;
    return 0;
}
