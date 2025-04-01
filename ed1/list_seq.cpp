#include <iostream>
#include <algorithm>
#include "list_seq.hpp"

using namespace std;

// construtor que cria a instância da lista
ListSeq::ListSeq(int _capacity) {
  data = new int[_capacity];
  capacity = _capacity;
}

// Libera a memória alocada para o vetor
void ListSeq::destroy() 
{
    /*
    ----diferença entre free e delete----

    free apaga variaveis escalares que estejam na PILHA ou seja: objetos de dados de tamanho fixo individuais, tais como inteiros e ponteiros

    delete usado para elementos vetoriais, ou seja, apaga todos os ponteiros relacionados que estejam na HEAP. neste caso todos os ponteiros relacionados a data
    os dados não são apagados, somente os ponteiros.

    delete[] data;
    
    */
    delete[] data;
}

// realoca vetor 
bool ListSeq::resize()
{
    int* _data = new int(++capacity);

    for(int i = 0; i < size; i++)
    {
        _data[i] = data[i];
    }

    destroy();
    data = _data;
    return true;
}

// imprime conteúdo da lista
void ListSeq::print() {
  for (int i=0; i<size; i++)
    cout << data[i] << " ";
  cout << endl;
}

// retorna posição do elemento ou -1
int ListSeq::find(int elem) {
  return 1;
}

// obtém o elemento na posição argumentada
int ListSeq::get(int pos) {
  return 1;
}

// lista vazia?
bool ListSeq::isEmpty() {
  if (size == 0)
    return true;
  else
    return false;
}

// lista cheia?
bool ListSeq::isFull() {
  if (size == capacity)
    return true;
  else
    return false;
}

// insere elemento no final
bool ListSeq::add(int elem) {
  if (size < capacity) {
    data[size++] = elem;
    return true;
  } else
    return false;
}

// remove elemento do final
void ListSeq::remove() 
{
    if(!isEmpty())
    {
        size--;
    }
}

// insere elemento na posição especificada
void ListSeq::insert(int elem, int pos) {}

// remove elemento na posição especificada
void ListSeq::removeAt(int pos) 
{
    if(pos < (size-1))
    {
        for(int i = pos; i < size-1; i++)
        {
            data[i] = size[i+1];
        }

        size--;
    }


}

// insere elemento em ordem crescente
bool ListSeq::addSorted(int elem) {
  return true;
}