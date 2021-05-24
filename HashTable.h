//
// Created by yuval on 12/2/18.
//

#ifndef ATLASSSS_HASHTABLE_H
#define ATLASSSS_HASHTABLE_H



#include "Defs.h"

typedef struct hashTable_s *hashTable;


hashTable createHashTable(copyFunction copyKey, freeFunction freeKey, printFunction printKey, copyFunction copyValue,
                          freeFunction freeValue, printFunction printValue, equalFunction equalKey,
                          transformIntoNumberFunction transformKeyIntoNumber, int hashNumber);

status destroyHashTable(hashTable);

status addToHashTable(hashTable, Element key,Element value);

Element lookupInHashTable(hashTable, Element key);

status removeFromHashTable(hashTable, Element key);

status displayHashElements(hashTable);

#endif //ATLASSSS_HASHTABLE_H
