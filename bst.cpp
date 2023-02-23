#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

//  Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    int minDiffInBST(TreeNode* root) {
        return 0;
    }

    std::vector<int> preOrder(TreeNode* root) {
        std::stack<TreeNode*> s;
        // s.push(root);
        TreeNode *cur_node = root;
        std::vector<int> node_values;
        while (!s.empty() || cur_node != nullptr) {
            if (cur_node != nullptr) {
                node_values.push_back(cur_node->val);
                s.push(cur_node->right);
                s.push(cur_node->left);
                cur_node = nullptr;
            } else {
                cur_node = s.top();
                s.pop();
            }
        }
        return node_values;
    }
    std::vector<int> inOrder(TreeNode* root) {
        std::stack<TreeNode*> s;
        // s.push(root);
        TreeNode *cur_node = root;
        std::vector<int> node_values;
        while (!s.empty() || cur_node != nullptr) {
            if (cur_node != nullptr) {
                s.push(cur_node);
                cur_node = cur_node->left;
            } else {
                cur_node = s.top();
                s.pop();
                node_values.push_back(cur_node->val);
                cur_node = cur_node->right;
            }
        }
        return node_values;
    }
    std::vector<int> postOrder(TreeNode* root) {
        std::stack<TreeNode*> s;
        s.push(root);
        TreeNode *cur_node = nullptr;
        std::vector<int> node_values;
        while (!s.empty() || cur_node != nullptr) {
            if (cur_node != nullptr) {
                s.push(cur_node->left);
                s.push(cur_node->right);
                cur_node = nullptr;
            } else {
                cur_node = s.top();
                s.pop();
                if (cur_node == nullptr) {
                    continue;
                }
                node_values.push_back(cur_node->val);
            }
        }
        std::reverse(node_values.begin(), node_values.end());
        return node_values;
    }
};

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    Solution s;
    std::vector<int> node_values = s.postOrder(root);
    for (int v : node_values) {
        std::cout << v << std::endl;
    }
    return 0;
}