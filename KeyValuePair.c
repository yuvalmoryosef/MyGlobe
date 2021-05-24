//
// Created by Yuval and Adi on 12/2/18.
//

#include "KeyValuePair.h"

struct keyValuePair_s {
    Element key;
    Element value;
    copyFunction copyKey;
    copyFunction copyVal;
    freeFunction freeKey;
    freeFunction freeVal;
    printFunction printKey;
    printFunction printVal;
    equalFunction equalKey;
};
//1.
keyValuePair createKeyValuePair(Element key, Element value,
                                copyFunction copyKey, copyFunction copyVal,
                                freeFunction freeKey, freeFunction freeVal,
                                printFunction printKey, printFunction printVal,
                                equalFunction equalKey)
{

    keyValuePair pair = (keyValuePair) malloc(sizeof(struct keyValuePair_s));//allocation for pair
    if (pair == NULL)
        return NULL;
    pair->copyKey = copyKey;
    pair->copyVal = copyVal;
    pair->key = pair->copyKey(key);
    pair->value = pair->copyVal(value);
    pair->freeKey = freeKey;
    pair->freeVal = freeVal;
    pair->printKey = printKey;
    pair->printVal = printVal;
    pair->equalKey = equalKey;

    return pair;
}

//2.
status destroyKeyValuePair(keyValuePair pair) {
    //free all the elements in the pair
    if (pair != NULL) {
        pair->freeKey(pair->key);
        pair->freeVal(pair->value);
        free(pair);
        pair = NULL;
        return success;
    }
    return null;
}

//3.
status displayValue(keyValuePair pair) {

    if(pair!=NULL){
        pair->printVal(pair->value);
        return success;
    }
    return null;
}
//4.
status displayKey(keyValuePair pair) {

    if(pair!=NULL){
        pair->printKey(pair->key);
        return success;
    }
    return null;
}
//5.
Element getValue(keyValuePair pair) {

	if(pair == NULL)
		return NULL;
    return pair->value;
}
//6.
Element getKey(keyValuePair pair) {

    return pair->key;
}
//7.
bool isEqualKey(keyValuePair pair1, keyValuePair pair2)
{

    if (pair1->equalKey == pair2->equalKey) {//check if the pairs are from the same type
        return pair1->equalKey(pair1->key, pair2->key);
    }
    return false;
}

Element copyPair(Element epair)
{
    keyValuePair pair=(keyValuePair)epair;//transform epair to keyValuePair

    //copy the pair
    keyValuePair copyPair=createKeyValuePair(pair->key,pair->value,
                                             pair->copyKey,pair->copyVal,pair->freeKey,pair->freeVal
            ,pair->printKey, pair->printVal,pair->equalKey);

    return (Element)copyPair;

}

status freePair(Element epair)
{

	if(epair==NULL)
		return null;

	return destroyKeyValuePair((keyValuePair)epair);
}

status printPair(Element epair)
{
    if(epair!=NULL)
    {
    	return  displayValue((keyValuePair)epair);
    }
    return null;
}

bool equalPair(Element epair1,Element epair2)
{
	if(epair1==NULL || epair2==NULL)
		return false;

        return isEqualKey((keyValuePair)epair1,(keyValuePair)epair2);

}
