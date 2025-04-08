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

bool LinkedList::pop_front() 
{
    if(this->head) // se head apontar para um elemento válido
    {
        Node* temp = this->head;
        this->head = temp->next;
        delete temp;
        return true;
    }else
    {
        return false;
    }    
}

bool LinkedList::push_back(int key) {
    return true;
}

bool LinkedList::equals(LinkedList* other) 
{
// other e head aponta para o começo da lista

    Node* temp1 = this->head; // variavel temporaria que aponta para o começo
    Node* temp2 = other->head; // variavel temporaria que aponta para o começo

    while(temp1 && temp2)
    {
        if(temp1->key == temp2->key)
        {
            temp1 = temp1->next;
            temp2 = temp2->next;

        }else
        {
            return false;
        }
    }

    return true;

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

int LinkedList::size() 
{
    int count = 0; // variavel que vai receber o tamanho da lista
    Node* temp = this->head; // função auxiliar que recebe a head

    while(temp) // enquanto temp for verdadeiro (não nulo)
    {
        temp = temp->next;
        count++;
    }

    return count;
}

Node* find(int key) {
    return nullptr;
}

void LinkedList::insert_after(int key, Node* pos) 
{
    Node* novo = new Node{key, pos->next}; // cria um novo nó com a key e apontando para a proxima posição do nó
    pos->next = novo; // pos->next aponta para novo

    // head -> [3|*]->[4|*]  [novo|*]->[7|*] (cria novo nó apontando para o proximo, mas ninguem aponta para ele)
    // head -> [3|*]->[4|*]->[novo|*]->[7|*] (agora o elemento anterior de novo aponta para novo)

}

bool remove_after(Node* pos) {
    return true;
}

bool LinkedList::insert(int pos, int key) 
{

    if(pos <= this->size()) // se a posição for menor que o tamanho da lista
    {
        Node* temp = this->head; // variavel que recebe head (posição 0 da lista)

        for(int i = 0; i <= pos; i++) // enquanto i for menor ou igual a pos
        {
            temp = temp->next; // temp recebe a proxima posição de temp (proxima posição da lista)
        }

        Node* novo = new Node{key, temp->next}; // cria um novo nó apontando para a proxima posição da lista
        temp->next = novo; // elemento anterior ao novo nó aponta para o novo nó

        return true;
    }

    return false;

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