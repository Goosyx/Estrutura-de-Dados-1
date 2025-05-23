#pragma once

// Definicao do TAD Lista Encadeada

class Node {
public:
    int key;
    Node* next;
};


class LinkedList {
private:
    Node* head;

public:
    LinkedList(); // método construtor
    ~LinkedList(); // método destrutor
    // ~  simbolo de negação utilizado para apagar TODO o nó. começando pelo inicio até o final do NÓ
    
    bool push_front(int key);
    bool pop_front();
    
    void print();
    int size();
    bool empty();
    
    bool push_back(int key);
    bool pop_back();
    
    int get(int pos);
    Node* find(int key);
    
    void insert_after(int key, Node* pos);
    bool remove_after(Node* pos);
    
    bool insert(int pos, int key);
    bool remove_pos(int pos);
    bool remove_key(int key);
    
    bool insert_sorted(int key);

    bool equals(LinkedList* other);
};