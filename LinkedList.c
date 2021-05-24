//
// Created by Yuval and Adi on 12/2/18.
//

#include "LinkedList.h"



struct Node_s {
	Element data;
	Node next;
};

struct List_s {
	Node head;
	Node tail;

	freeFunction freeData;
	copyFunction copyData;
	equalFunction equalData;
	printFunction printData;

};


//‫‪1. createLinkedList‬‬
List createLinkedList(copyFunction copyData, freeFunction freeData,
		printFunction printData, equalFunction equalFunction ){

	List list = (List)malloc(sizeof(struct List_s));
	if(list == NULL){
		return NULL;
	}
	list->copyData = copyData;

	list->freeData = freeData;
	list->head = NULL;
	list->tail = NULL;
	list->printData=printData;
	list->equalData = equalFunction;
	return list;
}

//2. destroyList
void destroyList(List list){
	while (list->head!=NULL){
		deleteNode(list,list->head->data);
	}

	free(list);
}//destroyList

//3. appendNode
void appendNode(List list,Element element){

	//create new node
	Node node = (Node)malloc(sizeof(struct Node_s));

	Node temp = NULL;

	//init next as tail
	node->next=NULL;

	//if empty list
	if(list->head == NULL) {
		list->head = node;
		list->tail = node;
	} else {
		temp = list->head;
		while(temp->next!=NULL){
			temp = temp->next;
		}
		temp->next = node;
		list->tail = node;
	}
	//copy data
	list->tail->data=list->copyData(element);
}

//4. deleteNode
status deleteNode(List list, Element element){
	if (list!=NULL)
	{
		Node node = list->head;
		Node temp = NULL;

		int ifFound=0;

		//head?
		if(list->equalData(list->head->data,element) == true)
		{

			temp = list->head->next;
			//free head
			list->freeData(list->head->data);
			free(list->head);
			list->head = NULL;
			//init next
			list->head = temp;
			return success;

		}

		//else

		while(node->next != NULL){
			if(list->equalData(node->next->data,element) == true)
			{
				ifFound=1;
				break;
			}else{
				node = node->next;
			}
		}
		if(ifFound ==1) {
			temp = node->next;
			node->next = node->next->next;
			list->freeData(temp->data);
			free(temp);
			return success;
		}
	}
	return failure;

}
//deleteNode

//5. displayList
void displayList(List list)
{
	if(list!=NULL)
	{
		if(list->head!=NULL){
			Node node = list->head;
			while(node->next != NULL)
			{
				list->printData(node->data);
				node = node->next;
			}
			list->printData(node->data);//print last node in list
		}
	}
}//displayList


//6. searchInList
Element searchInList(List list, Element element)
{
	if(list!=NULL)
	{
		Node node = list->head;
		while (node != NULL)
		{
			if (list->equalData(node->data, element) == true)
			{
				return node->data;
			}
			node = node->next;
		}
	}

	return NULL;
}

