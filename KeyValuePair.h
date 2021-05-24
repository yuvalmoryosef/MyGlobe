//
// Created by yuval on 12/2/18.
//

#ifndef ATLASSSS_KEYVALUEPAIR_H
#define ATLASSSS_KEYVALUEPAIR_H


#include "Defs.h"

//struct:
typedef struct keyValuePair_s *keyValuePair;

//functions:
keyValuePair createKeyValuePair (Element, Element, copyFunction, copyFunction ,
                                 freeFunction, freeFunction, printFunction, printFunction, equalFunction );

status destroyKeyValuePair(keyValuePair);

status displayValue(keyValuePair);

status displayKey(keyValuePair);

Element getValue(keyValuePair);

Element getKey(keyValuePair);

bool isEqualKey(keyValuePair, keyValuePair);

Element copyPair(Element);

status freePair(Element);

status printPair(Element);

bool equalPair(Element, Element);

#endif //ATLASSSS_KEYVALUEPAIR_H
