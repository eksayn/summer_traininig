#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


TreeNode* buildTreeFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Can't open file: " << filename << endl;
        return nullptr;
    }

    int num;
    file >> num; // Первое число - корень дерева
    TreeNode* root = new TreeNode(num);

    while (file >> num) {
        TreeNode* current = root;
        while (true) {
            if (num < current->val) {
                if (current->left == nullptr) {
                    current->left = new TreeNode(num);
                    break;
                } else {
                    current = current->left;
                }
            } else if (num > current->val) {
                if (current->right == nullptr) {
                    current->right = new TreeNode(num);
                    break;
                } else {
                    current = current->right;
                }
            }
        }
    }

    file.close();
    return root;
}


vector<int> findAncestorsWithStack(TreeNode* root, int target, int& operations) {
    vector<int> ancestors;
    if (root == nullptr) return ancestors;

    stack<pair<TreeNode*, vector<int>>> st;
    st.push({root, {}});
    operations = 0;

    while (!st.empty()) {
        operations++;
        auto [node, path] = st.top();
        st.pop();

        if (node->val == target) {
            ancestors = path;
            break;
        }

        if (node->right) {
            vector<int> newPath = path;
            newPath.push_back(node->val);
            st.push({node->right, newPath});
            operations++;
        }
        if (node->left) {
            vector<int> newPath = path;
            newPath.push_back(node->val);
            st.push({node->left, newPath});
            operations++;
        }
    }
    return ancestors;
}


bool findAncestorsRecursive(TreeNode* root, int target, vector<int>& ancestors, int& operations) {
    operations++;
    if (root == nullptr) return false;
    
    if (root->val == target) return true;
    
    if (findAncestorsRecursive(root->left, target, ancestors, operations) || 
        findAncestorsRecursive(root->right, target, ancestors, operations)) {
        ancestors.push_back(root->val);
        operations++;
        return true;
    }
    
    return false;
}

int main() {
    
    string filename;
    cout << "Input file name: ";
    cin >> filename;

    TreeNode* root = buildTreeFromFile(filename);
    if (root == nullptr) return 1;

    int target;
    cout << "Input target: ";
    cin >> target;

    
    int stackOperations = 0;
    vector<int> stackAncestors = findAncestorsWithStack(root, target, stackOperations);
    
    cout << "Ancestors(Stack): ";
    for (int ancestor : stackAncestors) {
        cout << ancestor << " ";
    }
    cout << "\nAmount of operations(Stack): " << stackOperations << endl;

    
    int recursiveOperations = 0;
    vector<int> recursiveAncestors;
    findAncestorsRecursive(root, target, recursiveAncestors, recursiveOperations);
    
    cout << "Ancestors (recursion): ";
    for (int ancestor : recursiveAncestors) {
        cout << ancestor << " ";
    }
    cout << "\nAmount of operations (recursion): " << recursiveOperations << endl;

    
    cout << "Comparison:\n";
    cout << "Stack: " << stackOperations << " operations\n";
    cout << "Recursion: " << recursiveOperations << " operations\n";

    return 0;
}