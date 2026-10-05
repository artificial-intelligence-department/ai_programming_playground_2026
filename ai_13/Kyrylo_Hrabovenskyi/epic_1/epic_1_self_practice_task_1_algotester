#include <iostream>

    using namespace std;

    int main() 
    {
        int n;
        if (!(cin >> n)) return 0;

        int k_games = 0, v_games = 0;
        int curr_k = 0, curr_v = 0;

        char c;
        for (int i = 0; i < n; i++) 
        {
            cin >> c;
            if (c == 'K') {
                curr_k++;
            }
            else if (c == 'V') 
            {

                curr_v++;

            }

            if (curr_k >= 11 && (curr_k - curr_v) >= 2) 
            {

                k_games++;
                curr_k = 0;
                curr_v = 0;

            }
            else if (curr_v >= 11 && (curr_v - curr_k) >= 2) 
            {

                v_games++;
                curr_k = 0;
                curr_v = 0;

            }
        }

        cout << k_games << ":" << v_games << "\n";

        if (curr_k > 0 || curr_v > 0) 
        {

            cout << curr_k << ":" << curr_v << "\n";

        }

        return 0;
    }