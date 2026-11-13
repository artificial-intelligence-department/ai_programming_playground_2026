#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>

std::string toLowerString(const std::string& s) {
    std::string res = s;
    for (char& c : res) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    if (!(std::cin >> n >> k)) return 0;

    std::vector<std::string> words(n);
    std::map<std::string, int> freq;

    for (int i = 0; i < n; ++i) {
        std::cin >> words[i];
        std::string lowerW = toLowerString(words[i]);
        freq[lowerW]++;
    }

    std::set<char> validLetters;

    for (const auto& pair : freq) {
        if (pair.second >= k) {
            for (char c : pair.first) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    validLetters.insert(c);
                }
            }
        }
    }

    if (validLetters.empty()) {
        std::cout << "Empty!\n";
    }
    else {
        std::vector<char> result(validLetters.begin(), validLetters.end());
        std::sort(result.rbegin(), result.rend()); // Від 'z' до 'a'

        std::cout << result.size() << "\n";
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i] << (i + 1 == result.size() ? "" : " ");
        }
        std::cout << "\n";
    }

    return 0;
}