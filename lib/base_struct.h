#ifndef BASESTRUCT
#define BASESTRUCT

#include <malloc.h>
#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include <type_traits>

template <typename Type>
class Node{
public:
    Node();
    ~Node();
    Type value;
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
    bool is_empty();
    Type remove(int pos);
    void _print();
    void _immRemove();
    void _immInsertBeforePoint(Type value);
};

template <typename Type>
class Stack : public List<Type>{
public:
    bool push(Type value);
    Type pop();
};

template <typename Type>
bool List<Type>::is_empty(){
    return head->next == tail;
}

template <typename Type>
void List<Type>::_immRemove(){
        p->pre->next = p->next;
        p->next->pre = p->pre;
        delete p;
}

template <typename Type>
void List<Type>::_immInsertBeforePoint(Type value){
    Node<Type>* newnode = new Node<Type>();
    newnode->value = value;
    newnode->pre = p->pre;
    newnode->next = p;
    p->pre->next = newnode;
    p->pre = newnode;
}

template <typename Type>
List<Type>::List(){
    head = new Node<Type>();
    tail = new Node<Type>();
    head->next = tail;
    tail->pre = head;
    p = head;
}

template <typename Type>
List<Type>::~List(){
    p = head->next;
    while(p = p->next){
        delete head->next;
        head->next = p;
    }
    delete head;
    delete tail;
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
        while(pos && (p = p->pre))
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
        Node<Type>* newnode = new Node<Type>();
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
    // 此处会造成内存泄露
    if(p && p->next && p->pre){
        p->pre->next = p->next;
        p->next->pre = p->pre;
        // if(std::is_pointer<Type>()){

        // }
        Type reDate = p->value;
        delete p;
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
    return this->insert(-1, value);
}

template <typename Type>
Type Stack<Type>::pop(){
    return this->remove(-1);
}

template <typename Type>
Node<Type>::Node(){
    next = nullptr;
    pre = nullptr;
    value = NULL;
}

template <typename Type>
Node<Type>::~Node(){
    // try{
    //     delete value;
    // }
    // catch(const std::exception& e){
    //     return;
    // }
    // return;  
}

#endif