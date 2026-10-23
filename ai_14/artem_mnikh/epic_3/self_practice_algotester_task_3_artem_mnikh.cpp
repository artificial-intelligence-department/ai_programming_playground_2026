/*Школяр з Коломиї 1771*/

#include <iostream>

using namespace std;

int main()
{
    int n, dollars;
    cin >> n >> dollars;
    int subjects[12] = {0};
    for (int i = 0; i < n; ++i)
    {
        int score;
        cin >> score;
        subjects[score - 1]++;
    }
    int result = subjects[9] + subjects[10] + subjects[11];
    for (int x = 9; x > 0; --x)
    {
        int cost_of_score = 10 - x;
        if (dollars - cost_of_score * subjects[x - 1] >= 0)
        {
            dollars -= cost_of_score * subjects[x - 1];
            result += subjects[x - 1];
            continue;
        }
        else
        {
            result += dollars / cost_of_score;
            break;
        }
    }
    cout << result;
}
