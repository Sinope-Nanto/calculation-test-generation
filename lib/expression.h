#ifndef EXPRESSION
#define EXPRESSION
#include "base_struct.h"
#include <cstring>
#include <malloc.h>
#include "operator.h"
#include <stdexcept>
#include <stdlib.h>
#include "tree.h"
List<char*>* _notation2List(const char* notation);
TreeNode* load2Tree(List<char*>* expression);
List<char*>* _negative_number_process(List<char*>* expression);
char* _resume_negative_number(char* expression);
char* removeParentheses(char* expression);

List<char*>* _notation2List(const char* notation){
    int left = 0;
    int right = 0;
    List<char*>* symbol = new List<char*>();
    symbol->is_empty();
    while(notation[right] != '\0'){
        if(in(notation[right], operator_list)){
            if(left == right){
                if(notation[right] != ' '){
                    char* operators = new char[2];
                    operators[0] = notation[right];
                    operators[1] = '\0';
                    symbol->insert(-1, operators);
                }
                left++;
                right++;
                continue;
            }
            char* number = new char[right - left + 1];
            memcpy(number, notation + left, right - left);
            number[right - left] = '\0';
            symbol->insert(-1, number);
            if(notation[right] != ' '){
                char* operators = new char[2];
                operators[0] = notation[right];
                operators[1] = '\0';
                symbol->insert(-1, operators);
            }
            left = (++right);
        }
        else right++;
    }
    if(left < strlen(notation)){
        char* number = new char[right - left + 1];
        memcpy(number, notation + left, right - left);
        number[right - left] = '\0';
        symbol->insert(-1, number);
    }
    return symbol;
}

List<char*>* _negative_number_process(List<char*>* expression){
    if(expression->getValue(0)[0] == '-'){
        expression->remove(0);
        char* zero = new char[2];
        zero[0] = '0';
        zero[1] = '\0';
        char* N = new char[2];
        N[0] = 'N';
        N[1] = '\0';
        expression->insert(0, N);
        expression->insert(0, zero);
    }
    Node<char*>* point = expression->head;
    expression->p = expression->head->next;
    char* checkList = new char[6];
    checkList[0] = '(';
    checkList[1] = '+';
    checkList[2] = '-';
    checkList[3] = '*';
    checkList[4] = '/';
    checkList[5] = '\0';
    while(expression->p->next){
        if(expression->p->value[0] == ' '){
            expression->_immRemove();
            expression->p = point->next;
        }
        if(point->value && in(point->value[0], checkList) && expression->p->value[0] == '-'){
            expression->p->value[0] = 'N';
            char* zero = new char[2];
            zero[0] = '0';
            zero[1] = '\0';
            expression->_immInsertBeforePoint(zero);
            point = point->next;
        }
        point = point->next;
        expression->p = expression->p->next;
    }
    delete[] checkList;
    return expression;
}

TreeNode* load2Tree(List<char*>* expression){
    Stack<TreeNode*>* numStack = new Stack<TreeNode*>();
    Stack<TreeNode*>* operatorStack = new Stack<TreeNode*>();
    while(!expression->is_empty()){
        char* value = expression->remove(0);
        if(in(value[0], operator_list)){
            if(value[0] == ')'){
                while(true){
                    TreeNode* t = operatorStack->pop();
                    if(t->value[0] == '(') break;
                    TreeNode* right = numStack->pop();
                    mergeTree(numStack->pop(), right, t);
                    numStack->push(t);
                }         
            }
            else if(value[0] == '('){
                TreeNode* newnode = new TreeNode(value);
                operatorStack->push(newnode);
            }
            else{
                
                while(!operatorStack->is_empty() && operator_rank(value[0]) <= operator_rank(operatorStack->getValue(-1)->value[0])){
                    TreeNode* t = operatorStack->pop();
                    TreeNode* right = numStack->pop();
                    mergeTree(numStack->pop(), right, t);
                    numStack->push(t);
                }
                TreeNode* newnode = new TreeNode(value);
                operatorStack->push(newnode);
            }
        }
        else{
            TreeNode* newnode = new TreeNode(value);
            numStack->push(newnode);
        }
        delete[] value;
    }
    while(!operatorStack->is_empty()){
        TreeNode* t = operatorStack->pop();
        TreeNode* right = numStack->pop();
        mergeTree(numStack->pop(), right, t);
        numStack->push(t);        
    }
    TreeNode* re = numStack->pop();
    delete numStack;
    delete operatorStack;
    return re;
}

char* _resume_negative_number(char* expression){
    int length = strlen(expression);
    int i = 0;
    int j = 1;
    for(; j < length; ++i,++j)
        if(expression[i] == '0' && expression[j] == '-')
            memcpy(expression + i, expression + j, length + 1 - i);
    return expression;
}

char* removeParentheses(char* expression){
    return _resume_negative_number(load2Tree(_negative_number_process(_notation2List(expression)))->removeN()->get_str());
}
#endif