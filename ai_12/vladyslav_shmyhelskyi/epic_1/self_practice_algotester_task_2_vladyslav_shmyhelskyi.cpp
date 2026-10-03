#include <iostream>
int main()
{
    long long presentcost;
    std::cin >> presentcost;
    if (presentcost < 1 || presentcost > 1000000000)
    {
        return 0;
    }

    int banknotes = 0;
    if (presentcost >= 500)
    {
        banknotes += presentcost / 500;
        presentcost %= 500;
    }
    if (presentcost >= 200)
    {
        banknotes += presentcost / 200;
        presentcost %= 200;
    }
    if (presentcost >= 100)
    {
        banknotes += presentcost / 100;
        presentcost %= 100;
    }
    if (presentcost >= 50)
    {
        banknotes += presentcost / 50;
        presentcost %= 50;
    }
    if (presentcost >= 20)
    {
        banknotes += presentcost / 20;
        presentcost %= 20;
    }
    if (presentcost >= 10)
    {
        banknotes += presentcost / 10;
        presentcost %= 10;
    }
    if (presentcost >= 5)
    {
        banknotes += presentcost / 5;
        presentcost %= 5;
    }
    if (presentcost >= 2)
    {
        banknotes += presentcost / 2;
        presentcost %= 2;
    }
    if (presentcost >= 1)
    {
        banknotes += presentcost / 1;
        presentcost %= 1;
    }
    std::cout << banknotes << std::endl;
}
