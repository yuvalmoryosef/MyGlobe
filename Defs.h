//
// Created by yuval on 12/2/18.
//

#ifndef ATLASSSS_DEFS_H
#define ATLASSSS_DEFS_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum e_bool { false,true } bool;
typedef enum e_status { success, failure,null} status;

typedef void * Element;

typedef Element(*copyFunction) (Element);
typedef status(*freeFunction) (Element);
typedef status(*printFunction) (Element);
typedef int(*transformIntoNumberFunction) (Element);
typedef bool(*equalFunction) (Element, Element);

#endif //ATLASSSS_DEFS_H
