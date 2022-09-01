#include <tree.h>
#include <operator.h>
#include <string.h>
#include <stdlib.h>

char operator_list[] = "+-*/() N";
int operator_rank(char _operator){
    switch (_operator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case 'N':
        return 9;
    case '(':
        return 0;
    case ')':
        return 10;
    default:
        return 999;
    }
}
bool in(char c, char* str){
    for(int i = 0; str[i] != '\0'; i++)
        if(c == str[i])
            return true;
    return false;
}

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

double TreeNode::get_value(){
    if(leftChild && rightChild){
        switch (value[0])
        {
        case '+':
            return leftChild->get_value() + rightChild->get_value();
        case '-':
        case 'N':
            return leftChild->get_value() - rightChild->get_value();
        case '*':
            return leftChild->get_value() * rightChild->get_value(); 
        case '/':
            return leftChild->get_value() / rightChild->get_value();
        default:
            return 0;
        }
    }
    else return atof(value);
}

TreeNode* mergeTree(TreeNode* treeL, TreeNode* treeR, TreeNode* root){
    root->leftChild = treeL;
    root->rightChild = treeR;
    return root;
}

TreeNode* TreeNode::removeN(){
    if(!(leftChild && rightChild)) return this;
    if(value[0] == 'N') value[0] = '-';
    leftChild->removeN();
    rightChild->removeN();
    return this;
}