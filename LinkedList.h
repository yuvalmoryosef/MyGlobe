//
// Created by yuval on 12/2/18.
//

#ifndef ATLASSSS_LINKEDLIST_H
#define ATLASSSS_LINKEDLIST_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Defs.h"


typedef struct List_s *List;
typedef struct Node_s *Node;

List createLinkedList(copyFunction,freeFunction,printFunction,  equalFunction);
void destroyList(List);
void appendNode(List,Element);
status deleteNode(List, Element);
void displayList(List);
Element searchInList(List,Element);

#endif //ATLASSSS_LINKEDLIST_H
