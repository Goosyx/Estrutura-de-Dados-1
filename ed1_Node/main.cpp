#include <stdio.h>
#include "linked_list.h"

int main() {
    LinkedList* list1 = new LinkedList();

    list1->push_front(3);
    list1->push_front(8);
    list1->push_front(2);
    list1->push_front(5);

    list1->print();

    list1->pop_front();

    delete list1;
}