#include "linked_list.h"
#include <stdio.h>
#include <iostream>

using namespace std;

LinkedList::LinkedList() 
{
    this->head = nullptr;
}

LinkedList::~LinkedList() {}  

bool LinkedList::push_front(int key) // método que cria um novo nó no inicio e o insere
{
    Node* no = new Node{key, nullptr}; //no = Nó. cria um novo nó

    if(!no) // se o nó não foi criado retorna false
    {
        return false;
    }
    no->next = this->head; // Nó.next aponta para a head(começo)
    this->head = no; // head agora aponta para o Nó
    
    return true;
}

bool LinkedList::pop_front() {
    return true;
}

bool LinkedList::push_back(int key) {
    return true;
}

bool LinkedList::equals(LinkedList* other) {
    return false;
}

int LinkedList::get(int pos) {
    return 0;
}

void LinkedList::print() 
{
    Node* no = this->head;

    while(no)
    {
        std::cout << "->" << no->key;
        no = no->next;
    }
}

int LinkedList::size() {
    return 0;
}

Node* find(int key) {
    return nullptr;
}

bool insert_after(int key, Node* pos) {
    return true;
}

bool remove_after(Node* pos) {
    return true;
}

bool insert(int pos) {
    return true;
}

bool remove(int pos) {
    return true;
}

bool remove(int key) {
    return true;
}

bool pop_back() {
    return true;
}

bool empty() {
    return true;
}