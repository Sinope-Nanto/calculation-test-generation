#include <tree.h>
#include <operator.h>
#include <base_struct.h>
#include <string.h>

TreeNode::TreeNode(){
    leftChild = nullptr;
    rightChild = nullptr;
    value = nullptr;
    slen = 0;
}

TreeNode::TreeNode(char* value){
    int len = strlen(value);
    slen = len;
    this->value = new char[len + 1];
    memcpy(this->value, value, len + 1);
    leftChild = nullptr;
    rightChild = nullptr;
}

TreeNode::~TreeNode(){
    delete value;
    if(leftChild) leftChild->~TreeNode();
    if(rightChild) rightChild->~TreeNode();
}

char* TreeNode::get_str(){
    char* re;
    if(!(leftChild && rightChild)){
        re = new char[slen + 1];
        memcpy(re, value, slen +  1);
    }
    else{
        char* leftStr = leftChild->get_str();
        char* rightStr = rightChild->get_str();
        int leftL = strlen(leftStr);
        int rightL = strlen(rightStr);
        re = new char[leftL + rightL + 6];
        int point = 0;
        if(operator_rank(leftChild->value[0]) < operator_rank(value[0])){
            re[0] = '(';
            memcpy(re + 1, leftStr, leftL);
            re[leftL + 1] = ')';
            point = leftL + 2;
        }
        else{
            memcpy(re, leftStr, leftL);
            point = leftL;
        }
        re[point++] = value[0];
        if(operator_rank(rightChild->value[0]) <=  operator_rank(value[0])){
            re[point] = '(';
            memcpy(re + point + 1, rightStr, rightL);
            re[point + 1 + rightL] = ')';
            point += (rightL + 2);
        }
        else{
            memcpy(re + point, rightStr, rightL);
            point += rightL;
        }
        re[point] = '\0';
        delete leftStr;
        delete rightStr;
    }
    return re;
}

TreeNode* mergeTree(TreeNode* treeL, TreeNode* treeR, TreeNode* root){
    root->leftChild = treeL;
    root->rightChild = treeR;
    return root;
}