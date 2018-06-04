#include <stdio.h>
#include <stdlib.h>
#include "../include/Queue.h"

/**Function to point the list head to the appropriate functions. Allocates memory to the struct.
*@return pointer to the list head
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/
List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareNodeFunction)(void *first, void *second),int (*compareFunction)(void *first, void *second))
{
  //creating new list and allocating space for list
  List *newList = malloc(sizeof(List)*1);

  //initializing list elements
  newList->head = NULL;
  newList->tail = NULL;
  newList->printData = printFunction;
  newList->compare = compareFunction;
  newList->compareNode = compareNodeFunction;
  newList->deleteData = deleteFunction;

  //returning new list
  return newList;
}


/**Function for creating a node for a linked list. This node contains generic data and may be connected to
other notes in a list.
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a linked list
*@return On success returns a node that can be added to a linked list. On failure, returns NULL.
*@param data - is a generic pointer to any data type.
**/
Node *initializeNode(void * data)
{
  //creating new node and allocating space for node
  Node * newNode = malloc(sizeof(Node)*1);
  //initializing node elements

  newNode->data = data;
  newNode->next = NULL;
  newNode->previous = NULL;

  //returning new node
  return newNode;
}


/**Inserts a Node to the back of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertBack(List *list, void *data)
{
  //check if list list does not point to anything
  if(list == NULL)
  {
    return;
  }

  //creating node to be added
  Node *nodeToBeAdded = initializeNode(data);

  //checking if head is NULL(head can be checked because then if head exists, we know there is at least 1 node)
  if(list->head == NULL)
  {
    list->head = nodeToBeAdded;
    list->tail = nodeToBeAdded;
    return;
  }

  //adding node to end if head is not NULL
  list->tail->next = nodeToBeAdded;
  nodeToBeAdded->previous = list->tail;
  list->tail = nodeToBeAdded;
  return;
}
/**Function to remove a node from the list and alter the pointers accordingly to not disrupt the order of the
 *data structure.
 *@pre List must exist and have memory allocated to it
 *@post toBeDeleted will have its memory freed if it exists in the list.
 *@param list pointer to the dummy head of the list containing deleteFunction function pointer
 *@param toBeDeleted pointer to data that is to be removed from the list
 *@return returns EXIT_SUCCESS on success, and EXIT_FAILURE when empty. Returns -1 when the node cannot be found.
 **/
int deleteDataFromList(List *list, void *toBeDeleted)
{
  //check if list exists
  if(list == NULL)
  {
    return EXIT_FAILURE;
  }
  //creating node
  Node *nodeToBeCompared = list->head;

  //comparing nodes to see if one is the same as toBeDeleted
  if (nodeToBeCompared != NULL)
  {
    if((nodeToBeCompared==list->tail)&&(list->compareNode(nodeToBeCompared->data,toBeDeleted) == 0))
    {
      list->deleteData(nodeToBeCompared->data);
      free(nodeToBeCompared);
      list->head=NULL;
      list->tail=NULL;
      return EXIT_SUCCESS;
    }
    while(nodeToBeCompared->next != NULL)
    {
      if (list->compareNode(nodeToBeCompared->data,toBeDeleted) == 0)
      {
        //check if head
        if (nodeToBeCompared ==list->head)
        {
          list->head = nodeToBeCompared->next;
          list->deleteData(nodeToBeCompared->data);
          free(nodeToBeCompared);
          return EXIT_SUCCESS;
        }

        //check if tail
        else if(nodeToBeCompared==list->tail)
        {
          list->tail=nodeToBeCompared->previous;
          list->deleteData(nodeToBeCompared->data);
          free(nodeToBeCompared);
          return EXIT_SUCCESS;
        }

        //if not head or tail
        else
        {
          nodeToBeCompared->previous->next = nodeToBeCompared->next;
          nodeToBeCompared->next->previous = nodeToBeCompared->previous;
          list->deleteData(nodeToBeCompared->data);
          free(nodeToBeCompared);
          return EXIT_SUCCESS;
        }
      }

      //moving to next node to be checked
      nodeToBeCompared = nodeToBeCompared->next;
    }
    return -1;
  }

  return -1;
}
/** Deletes the entire linked list head to tail, starting with the nodes, followed by the list itself.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List-type dummy node
**/
void deleteList(List *list)
{
  //check if list exists
  if(list == NULL)
  {
    return;
  }

  //create placeholder for node.
  Node *nodeHolder;

  //free each node including data in note(data in node is cleared through deleteData)
  while(list->head!=NULL)
  {
    nodeHolder = list->head;
    list->head = list->head->next;
    list->deleteData(nodeHolder->data);//might need to add more for deleting many data types
    free(nodeHolder);
  }
  //free the list itself
  free(list);
  return;

}

/** Uses the comparison function in the List struct to place the element in the appropriate position in the list.
*this is intended to be used from the beginning in order to keep the list completely sorted.
*@pre List exists and has memory allocated to it. Node to be added is valid.
*@post The node to be added will be placed immediately before or after the first occurrence of a related node
*@param list a pointer to the dummy head of the list containing function pointers for delete and compare, as well
as a pointer to the first and last element of the list.
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertSorted(List *list, void *data)
{
  //check if list exists
  if(list == NULL)
  {
    return;
  }

  //creating nodes
  Node *nodeToBeAdded = initializeNode(data);
  Node *nodeToBeCompared = list->head;

  //check if head == null
  if (list->head == NULL)
  {
    list->head = nodeToBeAdded;
    list->tail = nodeToBeAdded;
    return;
  }
  while(nodeToBeCompared!=NULL)
  {
    if(list->compare(nodeToBeCompared->data,nodeToBeAdded->data) < 0)
    {
      if(nodeToBeCompared->next == NULL)
      {
        nodeToBeCompared->next = nodeToBeAdded;
        nodeToBeAdded->previous = nodeToBeCompared;
        list->tail = nodeToBeAdded;
        return;
      }
      nodeToBeCompared=nodeToBeCompared->next;
    }
    else
    {
      if (list->head == nodeToBeCompared)
      {
        list->head = nodeToBeAdded;
        nodeToBeCompared->previous = nodeToBeAdded;
        nodeToBeAdded->next = nodeToBeCompared;
        return;
      }
      nodeToBeCompared->previous->next = nodeToBeAdded;
      nodeToBeAdded->previous = nodeToBeCompared->previous;
      nodeToBeCompared->previous = nodeToBeAdded;
      nodeToBeAdded->next = nodeToBeCompared;
      return;

    }
  }

  return;
}
/**Function to return the data at the front of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the head of the list
 *@return pointer to the data located at the head of the list
 **/
void *getFromFront(List *list)
{
  //check if list exists
  if(list == NULL)
  {
    return NULL;
  }

  //returns pointer to data located at head of the list.
  return list->head->data;
}
/**Function to print list from head to tail. This will utilize the list's printData function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printForward(List *list)
{
  //check if list exists
  if(list == NULL)
  {
    return;
  }

  //creates node
  Node *nodeToBePrinted = list->head;

  //prints forward using printData
  while (nodeToBePrinted != list->tail)
  {
    list->printData(nodeToBePrinted->data);
    nodeToBePrinted = nodeToBePrinted->next;
  }
  list->printData(list->tail->data);

  //returns void
  return;
}

/**Function to print list from tail to head. This will utilize the list's printData function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printBackwards(List *list)
{
//check if list exists
  if(list == NULL)
  {
    return;
  }

  //creates node
  Node *nodeToBePrinted = list->tail;

  //prints backwards using printData
  while (nodeToBePrinted != list->head)
  {
    list->printData(nodeToBePrinted->data);
    nodeToBePrinted = nodeToBePrinted->previous;
  }
  list->printData(list->head->data);

  //returns void
  return;
}

float calculateTime(List *list)
{
  Data *firstDataN = NULL;
  Data *firstDataE = NULL;
  Data *firstDataS = NULL;
  Data *firstDataW = NULL;



  int west = 0;
  int east = 0;
  int north = 0;
  int south = 0;
  int amountNorth = 0;
  int amountEast = 0;
  int amountWest = 0;
  int amountSouth = 0;
  float averageNorth = 0.0;
  float averageEast = 0.0;
  float averageSouth = 0.0;
  float averageWest = 0.0;
  float maxWaitTime = 0.0;

  //char lastCarThroughIntersectionDirection = 'X';  //stores the last car through
  //float lastCarThoughIntersectionTime = 0.0;

  int northVSEast = -999;
  int southVsWest = -999;
  int NEVsSW      = -999;

  float timeCounter=0;

  Node *tempNode = list->head;
  Data *tempData = NULL;

//assigning the first of each direction to its respective firstData
  while(tempNode!=NULL)
  {
    tempData = (Data *)tempNode->data;
    if (tempData->travelDirection == 'N' && north==0)
    {
      firstDataN = tempData;
      north = 1;
    }
    if (tempData->travelDirection == 'E' && east==0)
    {
      firstDataE = tempData;
      east = 1;
    }
    if (tempData->travelDirection == 'S' && south==0)
    {
      firstDataS = tempData;
      south = 1;
    }
    if (tempData->travelDirection == 'W' && west==0)
    {
      firstDataW = tempData;
      west = 1;
    }
    tempNode=tempNode->next;
  }

//checking what car goes first
  while(north!=0 || south!=0 || west!=0 || east!=0)
  {
    //comparing north against east
    if(east == 0)
    {
      if(north == 1)
      {
        northVSEast = -1;
      }
      else
      {
        northVSEast = -999;
      }
    }
    else if(north == 0)
    {
      northVSEast = 1;
    }
    else
    {
      northVSEast = list->compare(firstDataN, firstDataE);
    }

    //comparing south against west
    if(west == 0)
    {
      if(south == 1)
      {
        southVsWest = -1;
      }
      else
      {
        (southVsWest = -999);
      }
    }
    else if(south == 0)
    {
      southVsWest = 1;
    }
    else
    {
      southVsWest = list->compare(firstDataS,firstDataW);
    }

    //comparing north + east vs south + west
    if (northVSEast == -999)
    {
      if(southVsWest == -999)
      {
        return timeCounter;
      }
      else
      {
        //if both north and east have no cars
        switch(southVsWest)
        {
          case 1: //west arrive first
            if(timeCounter < firstDataW->timeOfArrival)
            {
              timeCounter = firstDataW->timeOfArrival;
            }


            printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                   ,firstDataW->travelDirection
                   ,firstDataW->turnDirection
                   ,firstDataW->timeOfArrival
                   ,timeCounter);
            if(maxWaitTime<(timeCounter-firstDataW->timeOfArrival)){
              maxWaitTime = timeCounter-firstDataW->timeOfArrival;
            }
            averageWest = averageWest + (timeCounter - firstDataW->timeOfArrival);
            amountWest++;
            timeCounter = timeCounter+turnTime(firstDataW);
            printf("%6.2f\n",timeCounter);

            firstDataW = findNewFirst(list,firstDataW,'W');
            if (firstDataW == NULL)
            {
              west = 0;
            }
            break;

          case 0:   //west and south arrive at the same time (south has priority since on the right)
          case -1:  //south arrives before west
            if(timeCounter < firstDataS->timeOfArrival)
            {
              timeCounter = firstDataS->timeOfArrival;
            }
            printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                   ,firstDataS->travelDirection
                   ,firstDataS->turnDirection
                   ,firstDataS->timeOfArrival
                   ,timeCounter);
            averageSouth = averageSouth + (timeCounter - firstDataS->timeOfArrival);
            amountSouth++;
            timeCounter = timeCounter+turnTime(firstDataS);
            printf("%6.2f\n",timeCounter);

            firstDataS = findNewFirst(list,firstDataS,'S');
            if (firstDataS == NULL)
            {
              south = 0;
            }
            break;
        }
      }
    }
    else if (southVsWest == -999)
    {
      //if both south and west have no cards
      switch(northVSEast)
      {
        case 1://east arrives first
          if(timeCounter < firstDataE->timeOfArrival)
          {
            timeCounter = firstDataE->timeOfArrival;
          }
          printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                 ,firstDataE->travelDirection
                 ,firstDataE->turnDirection
                 ,firstDataE->timeOfArrival
                 ,timeCounter);
          averageEast = averageEast + (timeCounter - firstDataE->timeOfArrival);
          amountEast++;
          timeCounter = timeCounter+turnTime(firstDataE);
          printf("%6.2f\n",timeCounter);

          firstDataE = findNewFirst(list,firstDataE,'E');
          if (firstDataE == NULL)
          {
            east = 0;
          }
          break;
        case 0://north and east arrive at same time(north is on right so has priority)
        case -1:// north arrives first
          if(timeCounter < firstDataN->timeOfArrival)
          {
            timeCounter=firstDataN->timeOfArrival;
          }
          printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                 ,firstDataN->travelDirection
                 ,firstDataN->turnDirection
                 ,firstDataN->timeOfArrival
                 ,timeCounter);
          timeCounter = timeCounter+turnTime(firstDataN);
          printf("%6.2f\n",timeCounter);
          firstDataN = findNewFirst(list,firstDataN,'N');
          if (firstDataN == NULL)
          {
            north = 0;
          }
          break;
      }
    }
    //checking which cars are to be compared for north + east vs south + west, then comparing
    else if(northVSEast>=0)//east arrives first or north and east arrive at the same time
    {
      if(southVsWest>=0)//west arrives first or south and west arrive at the same time
      {
        NEVsSW = list->compare(firstDataE,firstDataW);
      }
      else //south arrives first between south and west
      {
        NEVsSW = list->compare(firstDataE,firstDataS);
      }
    }
    else //north arrives first between north and east
    {
      if(southVsWest >= 0)//west arrives first or south and west arrive at the same time
      {
        NEVsSW = list->compare(firstDataN,firstDataW);
      }
      else//south arrives first between south and west
      {
        NEVsSW = list->compare(firstDataN,firstDataS);
      }
    }

    //comparing cars to see which is first if there is at least one car in either north + east and at least one car in either south + west
    switch(NEVsSW)
    {
      case 1://if NEVsSW==1 southVsWest arrives before northVsEast
        switch(southVsWest)
        {
          case 1:
            if(timeCounter < firstDataW->timeOfArrival)
            {
              timeCounter = firstDataW->timeOfArrival;
            }
            printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                   ,firstDataW->travelDirection
                   ,firstDataW->turnDirection
                   ,firstDataW->timeOfArrival
                   ,timeCounter);
            if(maxWaitTime<(timeCounter-firstDataW->timeOfArrival)){
              maxWaitTime = timeCounter-firstDataW->timeOfArrival;
            }
            averageWest = averageWest + (timeCounter - firstDataW->timeOfArrival);
            amountWest++;
            timeCounter = timeCounter+turnTime(firstDataW);
            printf("%6.2f\n",timeCounter);
            firstDataW = findNewFirst(list,firstDataW,'W');
            if (firstDataW == NULL)
            {
              west = 0;
            }
            break;
          case 0:
            if(timeCounter < firstDataS->timeOfArrival)
            {
              timeCounter = firstDataS->timeOfArrival;
            }
            printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                   ,firstDataS->travelDirection
                   ,firstDataS->turnDirection
                   ,firstDataS->timeOfArrival
                   ,timeCounter);
            if(maxWaitTime<(timeCounter-firstDataS->timeOfArrival)){
              maxWaitTime = timeCounter-firstDataS->timeOfArrival;
            }
            averageSouth = averageSouth + (timeCounter - firstDataS->timeOfArrival);
            amountSouth++;
            timeCounter = timeCounter+turnTime(firstDataS);
            printf("%6.2f\n",timeCounter);

            firstDataS = findNewFirst(list,firstDataS,'S');
            if (firstDataS == NULL)
            {
              south = 0;
            }
            break;
          case -1:
            if(timeCounter < firstDataS->timeOfArrival)
            {
              timeCounter = firstDataS->timeOfArrival;
            }
            printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                   ,firstDataS->travelDirection
                   ,firstDataS->turnDirection
                   ,firstDataS->timeOfArrival
                   ,timeCounter);
            if(maxWaitTime<(timeCounter-firstDataS->timeOfArrival)){
              maxWaitTime = timeCounter-firstDataS->timeOfArrival;
            }
            averageSouth = averageSouth + (timeCounter - firstDataS->timeOfArrival);
            amountSouth++;
            timeCounter = timeCounter+turnTime(firstDataS);
            printf("%6.2f\n",timeCounter);
            firstDataS = findNewFirst(list,firstDataS,'S');
            if (firstDataS == NULL)
            {
              south = 0;
            }
            break;
        }
        break;
      //ifNSVsSW==-1
      case -1:
        switch(northVSEast)
        {
          case 1:
            if(timeCounter < firstDataE->timeOfArrival)
            {
              timeCounter = firstDataE->timeOfArrival;
            }
            printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                   ,firstDataE->travelDirection
                   ,firstDataE->turnDirection
                   ,firstDataE->timeOfArrival
                   ,timeCounter);
            if(maxWaitTime<(timeCounter-firstDataE->timeOfArrival)){
              maxWaitTime = timeCounter-firstDataE->timeOfArrival;
            }
            averageEast = averageEast + (timeCounter - firstDataE->timeOfArrival);
            amountEast++;
            timeCounter = timeCounter+turnTime(firstDataE);
            printf("%6.2f\n",timeCounter);
            firstDataE = findNewFirst(list,firstDataE,'E');
            if (firstDataE == NULL)
            {
              east = 0;
            }
            break;
          case 0:
            if(timeCounter < firstDataN->timeOfArrival)
            {
              timeCounter = firstDataN->timeOfArrival;
            }
            printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                   ,firstDataN->travelDirection
                   ,firstDataN->turnDirection
                   ,firstDataN->timeOfArrival
                   ,timeCounter);
            if(maxWaitTime<(timeCounter-firstDataN->timeOfArrival)){
              maxWaitTime = timeCounter-firstDataN->timeOfArrival;
            }
            averageNorth = averageNorth + (timeCounter - firstDataN->timeOfArrival);
            amountNorth++;
            timeCounter = timeCounter+turnTime(firstDataN);
            printf("%6.2f\n",timeCounter);
            firstDataN = findNewFirst(list,firstDataN,'N');
            if (firstDataN == NULL)
            {
              north = 0;
            }
            break;
          case -1:
            if(timeCounter < firstDataN->timeOfArrival)
            {
              timeCounter = firstDataN->timeOfArrival;
            }
            printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                   ,firstDataN->travelDirection
                   ,firstDataN->turnDirection
                   ,firstDataN->timeOfArrival
                   ,timeCounter);
            if(maxWaitTime<(timeCounter-firstDataN->timeOfArrival)){
              maxWaitTime = timeCounter-firstDataN->timeOfArrival;
            }
            averageNorth = averageNorth + (timeCounter - firstDataN->timeOfArrival);
            amountNorth++;
            timeCounter = timeCounter+turnTime(firstDataN);
            printf("%6.2f\n",timeCounter);

            firstDataN = findNewFirst(list,firstDataN,'N');
            if (firstDataN == NULL)
            {
              north = 0;
            }
            break;
        }
        break;
      //ifNEvsSW==0
      case 0:// northVsEast and southVsWest arrived at same time
        switch(northVSEast)
        {
          case 1://east first vs north
            switch(southVsWest)
            {
              case 1: //east and west are both first
                if(   (turnTime(firstDataE)==2)                                      //east going straight wins
                      || (turnTime(firstDataE)==turnTime(firstDataW))                   //east and west have same turning direction, east wins
                      || (turnTime(firstDataE)==1.5 && turnTime(firstDataW)==3.5) )     //east turning right vs west turning left, east wins
                {
                  if(timeCounter < firstDataE->timeOfArrival)
                  {
                    timeCounter = firstDataE->timeOfArrival;
                  }
                  printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                         ,firstDataE->travelDirection
                         ,firstDataE->turnDirection
                         ,firstDataE->timeOfArrival
                         ,timeCounter);
                  if(maxWaitTime<(timeCounter-firstDataE->timeOfArrival)){
                    maxWaitTime = timeCounter-firstDataE->timeOfArrival;
                  }
                  averageEast = averageEast + (timeCounter - firstDataE->timeOfArrival);
                  amountEast++;
                  timeCounter = timeCounter+turnTime(firstDataE);
                  printf("%6.2f\n",timeCounter);
                  firstDataE = findNewFirst(list,firstDataE,'E');
                  if (firstDataE == NULL)
                  {
                    east = 0;
                  }
                }
                else //west wins
                {
                  if(timeCounter < firstDataW->timeOfArrival)
                  {
                    timeCounter=firstDataW->timeOfArrival;
                  }
                  printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                         ,firstDataW->travelDirection
                         ,firstDataW->turnDirection
                         ,firstDataW->timeOfArrival
                         ,timeCounter);
                  if(maxWaitTime<(timeCounter-firstDataW->timeOfArrival)){
                    maxWaitTime = timeCounter-firstDataW->timeOfArrival;
                  }
                  averageWest = averageWest + (timeCounter - firstDataW->timeOfArrival);
                  amountWest++;
                  timeCounter = timeCounter+turnTime(firstDataW);
                  printf("%6.2f\n",timeCounter);

                  firstDataW = findNewFirst(list,firstDataW,'W');
                  if (firstDataW == NULL)
                  {
                    west = 0;
                  }
                }
                break;
              case -1: //east and south are both first, east is on right of south, east wins
              case 0: //east and west and south all arrive at the same time, east is on the furthest right, east wins
                if(timeCounter < firstDataE->timeOfArrival)
                {
                  timeCounter=firstDataE->timeOfArrival;
                }
                printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                       ,firstDataE->travelDirection
                       ,firstDataE->turnDirection
                       ,firstDataE->timeOfArrival
                       ,timeCounter);
                if(maxWaitTime<(timeCounter-firstDataE->timeOfArrival)){
                  maxWaitTime = timeCounter-firstDataE->timeOfArrival;
                }
                averageEast = averageEast + (timeCounter - firstDataE->timeOfArrival);
                amountEast++;
                timeCounter = timeCounter+turnTime(firstDataE);
                printf("%6.2f\n",timeCounter);
                firstDataE = findNewFirst(list,firstDataE,'E');
                if (firstDataE == NULL)
                {
                  east = 0;
                }
                break;
            }
          case -1: //north is first vs east
            switch(southVsWest)
            {
              case 1://north and west are first, west is on right, west wins
                if(timeCounter < firstDataW->timeOfArrival)
                {
                  timeCounter=firstDataW->timeOfArrival;
                }
                printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                       ,firstDataW->travelDirection
                       ,firstDataW->turnDirection
                       ,firstDataW->timeOfArrival
                       ,timeCounter);
                if(maxWaitTime<(timeCounter-firstDataW->timeOfArrival)){
                  maxWaitTime = timeCounter-firstDataW->timeOfArrival;
                }
                averageWest = averageWest + (timeCounter - firstDataW->timeOfArrival);
                amountWest++;
                timeCounter = timeCounter+turnTime(firstDataW);
                printf("%6.2f\n",timeCounter);

                firstDataW = findNewFirst(list,firstDataW,'W');
                if (firstDataW == NULL)
                {
                  west = 0;
                }
                break;
              case -1: //north and south are first
                if(   (turnTime(firstDataN)==2)                                      //north going straight wins
                      || (turnTime(firstDataN)==turnTime(firstDataS))                   //north and south have same turning direction, north wins
                      || (turnTime(firstDataN)==1.5 && turnTime(firstDataS)==3.5) )     //north turning right vs south turning left, north wins
                {
                  if(timeCounter < firstDataN->timeOfArrival)
                  {
                    timeCounter=firstDataN->timeOfArrival;
                  }
                  printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                         ,firstDataN->travelDirection
                         ,firstDataN->turnDirection
                         ,firstDataN->timeOfArrival
                         ,timeCounter);
                  if(maxWaitTime<(timeCounter-firstDataN->timeOfArrival)){
                    maxWaitTime = timeCounter-firstDataN->timeOfArrival;
                  }
                  averageNorth = averageNorth + (timeCounter - firstDataN->timeOfArrival);
                  amountNorth++;
                  timeCounter = timeCounter+turnTime(firstDataN);
                  printf("%6.2f\n",timeCounter);
                  firstDataN = findNewFirst(list,firstDataN,'N');
                  if (firstDataN == NULL)
                  {
                    north = 0;
                  }
                }
                else//south wins
                {
                  if(timeCounter < firstDataS->timeOfArrival)
                  {
                    timeCounter=firstDataS->timeOfArrival;
                  }
                  printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                         ,firstDataS->travelDirection
                         ,firstDataS->turnDirection
                         ,firstDataS->timeOfArrival
                         ,timeCounter);
                  if(maxWaitTime<(timeCounter-firstDataS->timeOfArrival)){
                    maxWaitTime = timeCounter-firstDataS->timeOfArrival;
                  }
                  averageSouth = averageSouth + (timeCounter - firstDataS->timeOfArrival);
                  amountSouth++;
                  timeCounter = timeCounter+turnTime(firstDataS);
                  printf("%6.2f\n",timeCounter);
                  firstDataS = findNewFirst(list,firstDataS,'S');
                  if (firstDataS == NULL)
                  {
                    south = 0;
                  }
                }
                break;
              case 0: //north and south and west all arrive at the same time, south is on the furthest right, south wins
                if(timeCounter < firstDataS->timeOfArrival)
                {
                  timeCounter=firstDataS->timeOfArrival;
                }
                printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                       ,firstDataS->travelDirection
                       ,firstDataS->turnDirection
                       ,firstDataS->timeOfArrival
                       ,timeCounter);
                if(maxWaitTime<(timeCounter-firstDataS->timeOfArrival)){
                  maxWaitTime = timeCounter-firstDataS->timeOfArrival;
                }
                averageSouth = averageSouth + (timeCounter - firstDataS->timeOfArrival);
                amountSouth++;
                timeCounter = timeCounter+turnTime(firstDataS);
                printf("%6.2f\n",timeCounter);
                firstDataS = findNewFirst(list,firstDataS,'S');
                if (firstDataS == NULL)
                {
                  south = 0;
                }
                break;
            }
          case 0: //north and east arrive at the same time
            switch(southVsWest)
            {
              case 1://north and east and west arrive at the same time, west is the furthest right, west wins
                if(timeCounter < firstDataW->timeOfArrival)
                {
                  timeCounter=firstDataW->timeOfArrival;
                }
                printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                       ,firstDataW->travelDirection
                       ,firstDataW->turnDirection
                       ,firstDataW->timeOfArrival
                       ,timeCounter);
                if(maxWaitTime<(timeCounter-firstDataW->timeOfArrival)){
                  maxWaitTime = timeCounter-firstDataW->timeOfArrival;
                }
                averageWest = averageWest + (timeCounter - firstDataW->timeOfArrival);
                amountWest++;
                timeCounter = timeCounter+turnTime(firstDataW);
                printf("%6.2f\n",timeCounter);
                firstDataW = findNewFirst(list,firstDataW,'W');
                if (firstDataW == NULL)
                {
                  west = 0;
                }
                break;
              case -1:// north and east and south all arrive at the same time, north is the furthest to the right, north wins
                if(timeCounter < firstDataN->timeOfArrival)
                {
                  timeCounter=firstDataN->timeOfArrival;
                }
                printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                       ,firstDataN->travelDirection
                       ,firstDataN->turnDirection
                       ,firstDataN->timeOfArrival
                       ,timeCounter);
                if(maxWaitTime<(timeCounter-firstDataN->timeOfArrival)){
                  maxWaitTime = timeCounter-firstDataN->timeOfArrival;
                }
                averageNorth = averageNorth + (timeCounter - firstDataN->timeOfArrival);
                amountNorth++;
                timeCounter = timeCounter+turnTime(firstDataN);
                printf("%6.2f\n",timeCounter);

                firstDataN = findNewFirst(list,firstDataN,'N');
                if (firstDataN == NULL)
                {
                  north = 0;
                }
                break;
              case 0: //all cars arrive at the same time, north wins(assumption made)
                if(timeCounter < firstDataN->timeOfArrival)
                {
                  timeCounter=firstDataN->timeOfArrival;
                }
                printf("Car going %c, turning %c, arrival time of %6.2f is entering intersection at %6.2f and will leave at "
                       ,firstDataN->travelDirection
                       ,firstDataN->turnDirection
                       ,firstDataN->timeOfArrival
                       ,timeCounter);
                if(maxWaitTime<(timeCounter-firstDataN->timeOfArrival)){
                  maxWaitTime = timeCounter-firstDataN->timeOfArrival;
                }
                averageNorth = averageNorth + (timeCounter - firstDataN->timeOfArrival);
                amountNorth++;
                timeCounter = timeCounter+turnTime(firstDataN);
                printf("%6.2f\n",timeCounter);
                firstDataN = findNewFirst(list,firstDataN,'N');
                if (firstDataN == NULL)
                {
                  north = 0;
                }
                break;
            }
        }
    }
  }
  if (amountNorth !=0)
  {
    printf("average wait time for north:%6.2f\n",(averageNorth/amountNorth));
  }
  if (amountEast!=0)
  {
    printf("average wait time for east:%6.2f\n",(averageEast/amountEast));
  }
  if (amountSouth!=0)
  {
    printf("average wait time for south:%6.2f\n",(averageSouth/amountSouth));
  }
  if (amountWest!=0)
  {
     printf("average wait time for west:%6.2f\n",(averageWest/amountWest));
  }
  if (amountNorth !=0 && amountSouth!=0 && amountEast!=0 && amountWest!=0){
    printf("average wait time:%6.2f\n",((averageEast+averageNorth+averageSouth+averageWest)/(amountEast+amountNorth+amountSouth+amountWest)));
  }
  printf("Max wait time:%6.2f\n",maxWaitTime);
  return timeCounter;
}

float turnTime(Data *firstData)
{
  switch(firstData->turnDirection)
  {
    case 'F':
      return 2.0;
      break;
    case 'R':
      return 1.5;
      break;
    case 'L':
      return 3.5;
      break;
    default:
      printf("invalid input:%c fix input file",firstData->turnDirection);
      return 0;
  }
}

Data* findNewFirst(List *list,Data *firstData, char direction)
{
  Data *newFirstData = NULL;
  Data *tempData = NULL;

  deleteDataFromList(list,firstData);


  Node *tempNode = list->head;

  //removes old data first
  while(tempNode!=NULL)
  {
    tempData= (Data *)tempNode->data;
    if (tempData->travelDirection == direction)
    {
      newFirstData = tempData;
      return newFirstData;
    }
    tempNode=tempNode->next;
  }
  return NULL;

}


