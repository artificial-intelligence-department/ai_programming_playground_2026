#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* prev;
    Node* next;
    bool alive;
};

bool canRemove(const Node* node) {
    if (node == nullptr || !node->alive) {
        return false;
    }

    int needed = node->value + 1;
    return (node->prev != nullptr && node->prev->value == needed) ||
           (node->next != nullptr && node->next->value == needed);
}

int main() {
    int n;
    cin >> n;

    vector<Node*> nodes;
    nodes.reserve(n);

    Node* tail = nullptr;
    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;

        Node* node = new Node{value, tail, nullptr, true};
        if (tail != nullptr) {
            tail->next = node;
        }
        nodes.push_back(node);
        tail = node;
    }

    vector<Node*> sorted = nodes;
    sort(sorted.begin(), sorted.end(), [](const Node* a, const Node* b) {
        return a->value < b->value;
    });

    vector<Node*> ready;
    int remaining = n;
    bool possible = true;

    for (size_t first = 0; first < sorted.size() && remaining > 1;) {
        size_t end = first;
        int value = sorted[first]->value;
        while (end < sorted.size() && sorted[end]->value == value) {
            ++end;
        }
        ready.clear();
        for (size_t i = first; i < end; ++i) {
            if (canRemove(sorted[i])) {
                ready.push_back(sorted[i]);
            }
        }

        for (size_t i = 0; i < ready.size(); ++i) {
            Node* node = ready[i];
            if (!canRemove(node)) {
                continue;
            }
            Node* left = node->prev;
            Node* right = node->next;
            if (left != nullptr) {
                left->next = right;
            }
            if (right != nullptr) {
                right->prev = left;
            }
            node->alive = false;
            --remaining;

            if (left != nullptr && left->value == value && canRemove(left)) {
                ready.push_back(left);
            }
            if (right != nullptr && right->value == value && canRemove(right)) {
                ready.push_back(right);
            }
        }
        if (remaining == 1) {
            break;
        }

        for (size_t i = first; i < end; ++i) {
            if (sorted[i]->alive) {
                possible = false;
                break;
            }
        }
        if (!possible) {
            break;
        }
        first = end;
    }

    cout << (possible && remaining == 1 ? "TAK" : "NI") << '\n';

    for (Node* node : nodes) {
        delete node;
    }
    return 0;
}