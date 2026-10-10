#include <iostream>

using namespace std;

int main()
{   
    const long long NUMBER_OF_TABLE_LEGS = 4;
    long long h[NUMBER_OF_TABLE_LEGS];

    for(int i = 0;i < NUMBER_OF_TABLE_LEGS;i++)
    {
        cin >> h[i];
    }

    long long d[NUMBER_OF_TABLE_LEGS];
    
    for(int i = 0;i < NUMBER_OF_TABLE_LEGS;i++)
    {
        cin >> d[i];
    }

    for(int i = 0;i < NUMBER_OF_TABLE_LEGS;i++)
    {
        if(d[i] > h[i])
        {
            cout << "ERROR";
            return 0;
        }
    }

    
    long long number = 2;

    for(int i = 0;i < NUMBER_OF_TABLE_LEGS;i++)
    {
        h[i] -= d[i];

        long long minLength = h[0];
        long long maxLength = h[0];
        

        for(int j = 0;j < NUMBER_OF_TABLE_LEGS;j++)
        {
            if(h[j] < minLength){
                minLength = h[j];
            }
            else if(h[j] > maxLength){
                maxLength = h[j];
            }
        }

       
         if (maxLength >= number * minLength)
        {
            cout << "NO";
            return 0;
        }

    }



    if (h[0] > 0 && h[0] == h[1] && h[0] == h[2] && h[0] == h[3])
    {
        cout << "YES";
    }

    else
    {
        cout << "NO";
    }
 

}