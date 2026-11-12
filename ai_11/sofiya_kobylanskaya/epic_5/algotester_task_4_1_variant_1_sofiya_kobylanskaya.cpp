#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
    multiset<int> n;
    int N;
    cin >> N;
    if (N < 1 || N > 100)
    {
        return 0;
    }
    int number;
    for (int i = 0; i < N; i++)
    {
        cin >> number;
        n.insert(number);
    }
    multiset<int> m;
    int M;
    cin >> M;
    if (M < 1 || M > 100)
    {
        return 0;
    }
    int digit;
    for (int i = 0; i < M; i++)
    {
        cin >> digit;
        m.insert(digit);
    }

    multiset<int> differenceN;
    set_difference(n.begin(), n.end(), m.begin(), m.end(), inserter(differenceN, differenceN.begin()));
    cout << differenceN.size() << endl;
    for (int x : differenceN)
    {
        cout << x << " ";
    }
    cout << endl;

    multiset<int> differenceM;
    set_difference(m.begin(), m.end(), n.begin(), n.end(), inserter(differenceM, differenceM.begin()));
    cout << differenceM.size() << endl;
    for (int x : differenceM)
    {
        cout << x << " ";
    }
    cout << endl;

    multiset<int> intersection;
    set_intersection(n.begin(), n.end(), m.begin(), m.end(), inserter(intersection, intersection.begin()));
    cout << intersection.size() << endl;
    for (int x : intersection)
    {
        cout << x << " ";
    }
    cout << endl;

    multiset<int> unionNM;
    set_union(n.begin(), n.end(), m.begin(), m.end(), inserter(unionNM, unionNM.begin()));
    cout << unionNM.size() << endl;
    for (int x : unionNM)
    {
        cout << x << " ";
    }
    cout << endl;

    multiset<int> symmetric_difference;
    set_symmetric_difference(n.begin(), n.end(), m.begin(), m.end(), inserter(symmetric_difference, symmetric_difference.begin()));
    cout << symmetric_difference.size() << endl;
    for (int x : symmetric_difference)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}