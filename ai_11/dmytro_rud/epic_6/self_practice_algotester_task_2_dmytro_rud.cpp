#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int value;
    Node* parent;
    Node* left;
    Node* right;
};

int main() {
    int n, p;
    cin >> n >> p;

    vector<Node*> tree;
    tree.push_back(new Node{p, nullptr, nullptr, nullptr});

    for (int i = 0; i < n; i++) {
        char s;
        cin >> s;

        if (s == '+') {
            int x;
            cin >> x;

            int index = tree.size();
            int parentIndex = (index - 1) / 2;
            Node* parent = tree[parentIndex];
            Node* node = new Node{x, parent, nullptr, nullptr};

            if (parent->left == nullptr) {
                parent->left = node;
            } else {
                parent->right = node;
            }
            tree.push_back(node);

            int changes = 0;
            Node* change = node;

            while (change->parent != nullptr &&
                   change->parent->value < change->value) {
                int z = change->parent->value;
                change->parent->value = change->value;
                change->value = z;

                change = change->parent;
                changes++;
            }
            cout << changes << ' ' << tree[0]->value << '\n';
        } else if (s == '-') {
            Node* head = tree[0];
            Node* last = tree.back();

            if (last->parent->left == last) {
                last->parent->left = nullptr;
            } else {
                last->parent->right = nullptr;
            }

            head->value = last->value;
            tree.pop_back();
            delete last;
            int changes = 0;
            Node* node = head;
            while ((node->left != nullptr &&
                    node->left->value > node->value) ||
                   (node->right != nullptr &&
                    node->right->value > node->value)) {
                int x1 = (node->left != nullptr) ? node->left->value : 0;
                int x2 = (node->right != nullptr) ? node->right->value : 0;

                if (x1 >= x2) {
                    node->left->value = node->value;
                    node->value = x1;
                    node = node->left;
                } else {
                    node->right->value = node->value;
                    node->value = x2;
                    node = node->right;
                }
                changes++;
            }
            cout << changes << ' ' << head->value << '\n';
        }
    }
    for (Node* node : tree) {
        delete node;
    }

    return 0;
}