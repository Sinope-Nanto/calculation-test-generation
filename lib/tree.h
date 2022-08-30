#ifndef TREE
#define TREE

class TreeNode{
public:
    TreeNode();
    TreeNode(char* value);
    ~TreeNode();
    TreeNode* leftChild = nullptr;
    TreeNode* rightChild = nullptr;
    char* value;
    char* get_str(); 
    int slen;
};

TreeNode* mergeTree(TreeNode* treeL, TreeNode* treeR, TreeNode* root);

#endif