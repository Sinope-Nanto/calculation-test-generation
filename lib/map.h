#ifndef MAP
#define MAP

#include <cstring>

class MapNode{
public:
    MapNode();
    ~MapNode();
    bool keyCompare(char* key);
    void changeValue(char* newvalue);
    char* key;
    char* value;
    MapNode* next = nullptr;
};

class MapList{
public:
    MapList();
    ~MapList();
    void add(MapNode* newNode);
    void changeOrAdd(char* key, char* value);
    void remove(char* key);
    char* find(char* key);
    MapNode* head;
    MapNode* p;
};

class Map{
public:
    Map();
    ~Map();
    int size;
    int (*hashFunc)(char* data);
};

MapNode::MapNode(){
    key = nullptr;
    value = nullptr;
    next = nullptr;
}

MapNode::~MapNode(){
    delete[] key;
    delete[] value;
}

bool MapNode::keyCompare(char* key){
    return strcmp(this->key, key) ? true : false;
}

void MapNode::changeValue(char* newValue){
    int length = strlen(newValue);
    delete[] value;
    value = new char[length + 1];
    memcpy(value, newValue, length + 1);
}

MapList::MapList(){
    head = new MapNode();
}

MapList::~MapList(){
    while(p = head->next){
        head->next = p->next;
        delete p;
    }
    delete head;
}

void MapList::add(MapNode* newNode){
    p = head;
    while(p->next) p = p->next;
    p->next = newNode;
}

void MapList::remove(char* key){
    p = head;
    while(p->next){
        if(p->next->keyCompare(key)){
            MapNode* t = p->next;
            p->next = t->next;
            delete t;
            return;
        }
        p = p->next;
    }
}

#endif