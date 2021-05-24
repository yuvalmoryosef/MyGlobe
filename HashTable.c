//
// Created by Yuval and Adi on 12/2/18.
//


#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"


struct hashTable_s {
	List* arrList;
	copyFunction copyKey;
	freeFunction freeKey;
	printFunction printKey;
	copyFunction copyValue;
	freeFunction freeValue;
	printFunction printValue;
	equalFunction equalKey;
	transformIntoNumberFunction transformKeyIntoNumber;
	int hashNumber;
};

//1.
hashTable createHashTable(copyFunction copyKey, freeFunction freeKey, printFunction printKey,
		copyFunction copyValue,freeFunction freeValue, printFunction printValue,
		equalFunction equalKey,transformIntoNumberFunction transformKeyIntoNumber, int hashNumber)
{

	hashTable hash=(hashTable)malloc(sizeof(struct hashTable_s));//allocation of hash table
	if(hash==NULL)
		return NULL;

	hash->arrList=(List*)calloc(sizeof(List),hashNumber);//allocation of the arrList

	if(hash->arrList==NULL)
		return NULL;
	hash->copyKey=copyKey;
	hash->freeKey=freeKey;
	hash->printKey=printKey;
	hash->copyValue=copyValue;
	hash->freeValue=freeValue;
	hash->printValue=printValue;
	hash->equalKey=equalKey;
	hash->transformKeyIntoNumber=transformKeyIntoNumber;
	hash->hashNumber=hashNumber;

	return hash;
}

//2.
status destroyHashTable(hashTable hash)
{
	int i;
	if(hash!=NULL)
	{
		for(i=0;i<hash->hashNumber;i++)
		{
			if(hash->arrList[i]!=NULL)
			{
				destroyList(hash->arrList[i]);
				hash->arrList[i] = NULL;
			}
		}
		free(hash->arrList);
		hash->arrList=NULL;
		free(hash);
		hash = NULL;
		return success;
	}
	return failure;
}





//3.
status addToHashTable(hashTable hash, Element key,Element value)
{
	if(hash!=NULL)
	{
		//find the place of the key in the hash:
		int place=(int)hash->transformKeyIntoNumber(key)%(hash->hashNumber);//in the main--> int place=(int)(hashFunction(key))%(hash->hashNumber);

		keyValuePair pair = createKeyValuePair(key,value,hash->copyKey,hash->copyValue,
				hash->freeKey,hash->freeValue,hash->printKey,hash->printValue, hash->equalKey);

		//if there is no list in this place:
		if(hash->arrList[place] == NULL)
		{
			//createLinkedList and init the function that the list get
			hash->arrList[place] = (Element)createLinkedList(copyPair,freePair,printPair,equalPair);
		}

		appendNode(hash->arrList[place],pair);//add the new pair to list in the place we got
		destroyKeyValuePair(pair);

		return success;
	}
	return null;
}



//4.
//problem with the compare between the pair and the key
Element lookupInHashTable(hashTable hash, Element key)
{
	if(hash==NULL || key==NULL)
	{
		return NULL;
	}

	keyValuePair pair = createKeyValuePair(key,NULL,hash->copyKey,hash->copyValue,
			hash->freeKey,hash->freeValue,hash->printKey,hash->printValue, hash->equalKey);
	//find the place of the key in the hash:
	int place=(int)hash->transformKeyIntoNumber(key)%(hash->hashNumber);

	//compare between the pair that hold the key and the pair in the list

	Element find= getValue((keyValuePair) searchInList(hash->arrList[place],(keyValuePair )pair));

	destroyKeyValuePair(pair);

	return find;
}



//5.
status removeFromHashTable(hashTable hash, Element key)
{

	if(hash==NULL || key==NULL)
	{
		return null;
	}

	keyValuePair pair = createKeyValuePair(key,NULL,hash->copyKey,hash->copyValue,
			hash->freeKey,hash->freeValue,hash->printKey,hash->printValue, hash->equalKey);

	//find the place of the key in the hash:
	int place=(int)hash->transformKeyIntoNumber(key)%(hash->hashNumber);

	//compare between the pair that hold the key and the pair in the list and delete
	status stat = deleteNode(hash->arrList[place],pair);

	destroyKeyValuePair(pair);

	return stat;

}


//6.
status displayHashElements(hashTable hash)
{
	if(hash!=NULL)
	{
		int i;
		for(i=0;i<hash->hashNumber;i++){
			if(hash->arrList[i]!=NULL)
			{
				displayList(hash->arrList[i]);
			}
		}
		return success;
	}
	return null;

}


