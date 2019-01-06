#include <vector>
#include <iostream>

using namespace std;

/**
 * Definition for a binary tree node.*/
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution962 {
public:
    bool isUnivalTree(TreeNode* root) {
        int rootValue = root->val;
        vector<TreeNode*> BFS;
        BFS.push_back(root);

        while (!BFS.empty()) {
            TreeNode* current = BFS.back();
            BFS.pop_back();
            if (current->left != NULL) {
                if (current->left->val == rootValue) BFS.push_back(current->left);
                else return false;
            }
            if (current->right != NULL) {
                if (current->right->val == rootValue) BFS.push_back(current->right);
                else return false;
            }
        }
        return true;
    }
};

int main() {
    TreeNode t0{2};
    TreeNode t1{2};
    TreeNode t2{2};
    TreeNode t3{5};
    TreeNode t4{2};
    TreeNode t5{1};
    t0.left = &t1;
    t0.right = &t2;
    t1.left = &t3;
    t1.right = &t4;
    //t2.right = &t5;

    Solution962 s;
    bool b = s.isUnivalTree(&t0);
    cout << b << endl;
    return 0;
}