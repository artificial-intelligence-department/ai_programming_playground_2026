#include <iostream>

using namespace std;

int main() {

    int m = 0;
    int n = 0;
    cout<<"enter m&n:"<<endl;
    cin>>m>>n;

    int m_tmp = m;
    int n_tmp = n;
    int step_1 = n_tmp++ + m_tmp; //n+m; n = n+1
    cout << "m: " << m_tmp << ", n: " << n_tmp << ", res: " << step_1 << endl;

    m_tmp = m;
    n_tmp = n;
    bool step_2 = m_tmp-- > n_tmp; // same to step 1
    cout << "m: " << m_tmp << ", n: " << n_tmp << ", res: " << boolalpha << step_2 << endl;

    m_tmp = m;
    n_tmp = n;
    bool step_3 = n_tmp-- > m_tmp; // same to step 1
    cout << "m: " << m_tmp << ", n: " << n_tmp << ", res: " << boolalpha << step_3 << endl << endl;

    return 0;
}