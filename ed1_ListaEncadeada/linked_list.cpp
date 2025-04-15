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

bool LinkedList::push_back(int key) 
{
    Node* novo = new Node{key, nullptr};

    if (!this->head) {
        this->head = novo;
        return true;
    }

    Node* temp = this->head;
    while (temp->next) {
        temp = temp->next;
    }

    temp->next = novo;
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

int LinkedList::get(int pos) 
{
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

Node* find(int key) 
{   


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
    if(pos == 0) // se a posição for igual a 0
    {
        return this->push_front(key); // chama a função push front
    }

    Node* temp = this->head; // declaração da variavel auxiliar temp que recebe o endereço de head

    for(int i = 0; i < pos-1 && temp; i++) // enquanto i for menor que pos && temp for verdade (i vai parar uma posição antes de pos)
    {
        temp = temp->next; // incrementa temp com a proxima posição de temp

        if(!temp) // se temp não existir retorna false
        {
            return false;
        }
    }

    Node* novo = new Node{key, temp->next}; // cria um novo nó apontando para a proxima posição de temp
    temp->next = novo; // proxima posição de temp aponta para novo nó

    return true;
}

bool LinkedList::remove_pos(int pos) 
{
    Node* temp = this->head;

    if(pos == 0)
    {
        pop_front();

    }

    for(int i = 0; i < pos - 1 && temp; i++)
    {
        temp = temp->next;

        if(!temp) // se temp não existir retorna false
        {
            return false;
        }
    }

    Node* to_delete = temp->next;
    temp->next = to_delete->next;
    delete to_delete;

    return true;
}

bool LinkedList::remove_key(int key) {
    return true;
}

bool LinkedList::pop_back() 
{
    int pos = size();

    Node* temp = this->head;

    for(int i = 0; i < pos - 1 && temp; i++)
    {
        temp = temp->next;

        if(!temp) // se temp não existir retorna false
        {
            return false;
        }
    }

    Node* to_delete = temp->next;
    temp->next = to_delete->next;

    delete temp;


    return true;
}

bool LinkedList::empty() {
    return true;
}