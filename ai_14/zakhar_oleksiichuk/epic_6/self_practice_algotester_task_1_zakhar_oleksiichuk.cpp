#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct BracketPair {
    int openPos;
    int closePos;   
    bool isSquare;
    
    bool operator<(const BracketPair& other) const {
        return openPos < other.openPos;
    }
};

bool isInside(const BracketPair& inner, const BracketPair& outer) {
    return outer.openPos <= inner.openPos && inner.closePos <= outer.closePos;
}

bool isReady(int idx, const vector<BracketPair>& pairs, const vector<bool>& printed) {
    for (int k = 0; k < pairs.size(); k++) {
        if (k != idx && isInside(pairs[k], pairs[idx]) && !printed[k]) {
            return false;
        }
    }
    return true;
}

int findFirst(int target, bool needSquare, const vector<BracketPair>& pairs, const vector<bool>& printed) {
    for (int j = 0; j < pairs.size(); j++) {
        if (!printed[j] && isInside(pairs[j], pairs[target]) && isReady(j, pairs, printed) && pairs[j].isSquare == needSquare) {
            return j;
        }
    }
    return -1;
}

int main() {
    string str;
    getline(cin, str);

    stack<pair<char, int>> st;
    vector<BracketPair> pairs;

    for (int i = 0; i < str.size(); i++) {
        char ch = str[i];
        int pos = i + 1;

        if (ch == '(' || ch == '[') {
            st.push({ch, pos});
        } else if (ch == ')' || ch == ']') {
            char expectedOpen = (ch == ')') ? '(' : '[';
            if (st.empty() || st.top().first != expectedOpen) {
                cout << "NO";
                return 0;
            }
            bool isSquare = (ch == ']');
            pairs.push_back({st.top().second, pos, isSquare});
            st.pop();
        }
    }

    if (!st.empty()) {
        cout << "NO";
        return 0;
    }

    cout << "YES\n";

    sort(pairs.begin(), pairs.end());
    
    int n = pairs.size();
    int printedCount = 0;
    vector<bool> printed(n, false);
    
    while (printedCount < n) {
        int target = -1;
        
        for (int i = 0; i < n; i++) {
            if (!printed[i] && pairs[i].isSquare) {
                target = i;
                break;
            }
        }
        
        if (target == -1) {
            for (int i = 0; i < n; i++) {
                if (!printed[i]) {
                    target = i;
                    break;
                }
            }
        }
        
        while(!printed[target]) {
            int firstFoundInd = findFirst(target, true, pairs, printed);
            if (firstFoundInd == -1) {
                firstFoundInd = findFirst(target, false, pairs, printed);
            }
            
            cout << pairs[firstFoundInd].openPos << " " << pairs[firstFoundInd].closePos << "\n";
            printed[firstFoundInd] = true;
            printedCount++;
        }
    }

    return 0;
}