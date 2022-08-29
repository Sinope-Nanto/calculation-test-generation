#ifndef BASESTRUCT
#define BASESTRUCT

#include <malloc.h>
#include <stdexcept>
#include <stdio.h>
#include <iostream>

template <typename Type>
class Node{
public:
    Node(double value);
    ~Node();
    Type value = 0;
    Node* next = nullptr;
    Node* pre = nullptr;
};

template <typename Type>
class List{
public:
    Node<Type>* head;
    Node<Type>* tail;
    Node<Type>* p;
    List();
    ~List();
    Type getValue(int pos);
    bool insert(int pos, Type value);
    Type remove(int pos);
    void _print();
};

template <typename Type>
class Stack : public List<Type>{
public:
    bool push(Type value);
    Type pop();
};

class Tree{
    public:
    Tree();
    ~Tree();
    Tree* left_child = nullptr;
    Tree* right_child = nullptr;
    int value = 0;
};

template <typename Type>
List<Type>::List(){
    head = (Node<Type>*)malloc(sizeof(Node<Type>));
    tail = (Node<Type>*)malloc(sizeof(Node<Type>));
    head->next = tail;
    tail->pre = head;
    p = head;
}

template <typename Type>
List<Type>::~List(){
    p = head->next;
    while(p = p->next){
        free(head->next);
        head->next = p;
    }
    free(head);
    free(tail);
}

template <typename Type>
Type List<Type>::getValue(int pos){
    if(pos >= 0){
        p = head;
        while((p = p->next) && pos)
            pos--;
    }
    else{
        pos = -pos;
        p = tail;
        while((p = p->pre) && pos)
            pos--;
    }
    if(p && p->next && p->pre)
        return p->value;
    else
        throw std::logic_error("Index out range");
}

template <typename Type>
bool List<Type>::insert(int pos, Type value){
    if(pos >= 0){
        p = head;
        while(p && pos){
            p = p->next;
            pos--;
        }
    }
    else{
        pos = -pos;
        p = tail;
        while(p && pos){
            p = p->pre;
            pos--;
        }
    }
    if(p){
        Node<Type>* newnode = (Node<Type>*)malloc(sizeof(Node<Type>));
        newnode->value = value;
        newnode->pre = p;
        newnode->next = p->next;
        p->next->pre = newnode;
        p->next = newnode;
        return true;
    }
    else return false;
}

template <typename Type>
Type List<Type>::remove(int pos){
    if(pos >= 0){
        p = head;
        while((p = p->next) && pos)
            pos--;
    }
    else{
        p = tail;
        pos = - pos - 1;
        while((p = p->pre) && pos)
            pos--;
    }
    if(p && p->next && p->pre){
        p->pre->next = p->next;
        p->next->pre = p->pre;
        double reDate = p->value;
        free(p);
        return reDate;
    }
    else
        throw std::logic_error("Index out range");  
}

template <typename Type>
void List<Type>::_print(){
    p = head;
    while((p = p->next) && p != tail)
        std::cout<<p->value<<' ';
    printf("\n");
}

template <typename Type>
bool Stack<Type>::push(Type value){
    return insert(-1, value);
}

template <typename Type>
Type Stack<Type>::pop(){
    return remove(-1);
}
#endif