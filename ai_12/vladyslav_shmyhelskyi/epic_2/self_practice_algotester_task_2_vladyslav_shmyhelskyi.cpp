#include <iostream>
using namespace std;
int main()
{

    int n;
    cin >> n;
   
    char c;
    int scoreV = 0;
    int scoreK = 0;
    int gamesV = 0;
    int gamesK = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> c;

        if (!(c == 'V' || c == 'K'))
        {
            return 0;
        }
        else if (c == 'V')
        {
            scoreV++;
        }
        else if (c == 'K')
        {
            scoreK++;
        }
        if ((scoreV == 11 && scoreK <= 9) || (scoreV > 11 && (scoreV - scoreK) >=2))
        {
            gamesV++;
            scoreV = 0;
            scoreK = 0;
        }
        if ((scoreK == 11 && scoreV <= 9) || (scoreK > 11 && (scoreK - scoreV) >=2))
        {

            gamesK++;
            scoreV = 0;
            scoreK = 0;
        }
    }

    cout << gamesK << ":" << gamesV << endl;
    if (scoreK > 0 || scoreV > 0)
    {
        cout << scoreK << ":" << scoreV << endl;
    }

}