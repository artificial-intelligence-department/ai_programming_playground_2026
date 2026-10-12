// Депутатські гроші

#include <iostream>

int main()
{

    const int HRYVNIA = 1;
    const int DVI_HRYVNI = 2;
    const int PIAT_HRYVEN = 5;
    const int DESIAT_HRYVEN = 10;
    const int DVADCIAT_HRYVEN = 20;
    const int PIATDESIAT_HRYVEN = 50;
    const int STO_HRYVEN = 100;
    const int DVISTI_HRYVEN = 200;
    const int PIATSOT_HRYVEN = 500;

    int kypiury[9] = {HRYVNIA, DVI_HRYVNI, PIAT_HRYVEN, DESIAT_HRYVEN, DVADCIAT_HRYVEN, PIATDESIAT_HRYVEN, STO_HRYVEN, DVISTI_HRYVEN, PIATSOT_HRYVEN};
    int the_most_valuable = 8;

    int count = 0;
    int n;

    std::cin >> n;
    
    while (n != 0)
    {
        if (n < kypiury[the_most_valuable])
            the_most_valuable--;
        else
        {
            count += n / kypiury[the_most_valuable];
            n = n % kypiury[the_most_valuable];
        }
    }

    std::cout << count << std::endl;

    return 0;
}