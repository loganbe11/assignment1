/**
 * @file Queue.h
 * @author Michael Ellis (modified for queues by Logan Bell)
 * @date January 2017 (May 2018)
 * @brief File containing the function definitions of a Queue list.
 */

#ifndef _LIST_API_
#define _LIST_API_

#include <stdio.h>
#include <stdlib.h>
typedef struct dataNode{
  char travelDirection;  //Travel direction is the direction the car is coming from going into the intersection. example: west
  char turnDirection;
  float timeOfArrival;
}Data;
/**
*Node of a linked list. This list is doubly linked, meaning that it has points to both the node immediately in front
of it, as well as the node immediately behind it.
**/
typedef struct listNode{
    struct Data *data;
    struct listNode *previous;
    struct listNode *next;
} Node;

/**
 *Dummy head of the list. Contains no actual data on it beyond a pointer to the front and end of the list.
 **/
typedef struct listHead{
    Node *head;
    Node *tail;
    void (*deleteData)(void *toBeDeleted);
    int (*compare)(void *first,void *second);
    int (*compareNode) (void *first, void *second);
    void (*printData)(void *toBePrinted);
} List;

/**Function to point the list head to the appropriate functions. Allocates memory to the struct.
*@return pointer to the list head
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/
List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareNodeFunction)(void *first,void *second),int (*compareFunction)(void *primary,void *secondary));

/**Function for creating a node for a linked list. This node contains generic data and may be connected to
other notes in a list.
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a linked list
*@return On success returns a node that can be added to a linked list. On failure, returns NULL.
*@param data - is a generic pointer to any data type.
**/
Node *initializeNode(void * data);

/**Inserts a Node to the back of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertBack(List *list, void *data);

/** Deletes the entire linked list head to tail, starting with the nodes, followed by the list itself.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List-type dummy node
**/
void deleteList(List *list);

/** Uses the comparison function in the List struct to place the element in the appropriate position in the list.
*this is intended to be used from the beginning in order to keep the list completely sorted.
*@pre List exists and has memory allocated to it. Node to be added is valid.
*@post The node to be added will be placed immediately before or after the first occurrence of a related node
*@param list a pointer to the dummy head of the list containing function pointers for delete and compare, as well
as a pointer to the first and last element of the list.
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertSorted(List *list, void *data);

/**Function to return the data at the front of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the head of the list
 *@return pointer to the data located at the head of the list
 **/
void *getFromFront(List *list);

/**Function to remove a node from the list and alter the pointers accordingly to not disrupt the order of the
 *data structure.
 *@pre List must exist and have memory allocated to it
 *@post toBeDeleted will have its memory freed if it exists in the list.
 *@param list pointer to the dummy head of the list containing deleteFunction function pointer
 *@param toBeDeleted pointer to data that is to be removed from the list
 *@return returns EXIT_SUCCESS on success, and EXIT_FAILURE when empty. Returns -1 when the node cannot be found.
 **/
int deleteDataFromList(List *list, void *toBeDeleted);

//comment needed!!!
void *deleteFromFront(List *list);

/**Function to print list from head to tail. This will utilize the list's printData function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printForward(List *list);

/**Function to print list from tail to head. This will utilize the list's printData function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printBackwards(List *list);

/**Function to calculate varying times of cars entering intersection, This will go through the list and stdout all the times of cars.
this has a big O notation of 2N as the elements of the list must be gone through completely twice.
*@pre List must exist, but does not have to have elements.
*@param list pointer to linked list dummy head
**/
float calculateTime(List *list);

/**function to calculate the time required to turn in the intersection.
*@pre firstData must exist and have a direction
*@param data for car turning
**/
float turnTime(Data *firstData);

/**function to find the next car for the respective direction.
this has a big O notation of n.
*@pre list must exist
*@param list pointer to linked list dummy head, direction, data of previous first
**/
Data* findNewFirst(List *list,Data *firstData, char direction);







#endif
