#include <stdio.h>
#include <stdlib.h>
#include "../include/main.h"
#include "../include/Queue.h"

int main(int argc, char *argv[])
{
  char travelDirection;  //travel direction, expecting one of 'N','S','E','W'
  char turnDirection;    //turn djrection, expecting one of 'F','R','L'
  float timeOfArrival;   //time of arrival at the intersection in seconds
  FILE *fp;              //pointer to input data file containing car data

  List *list = initializeList(printChar,&free,compareDataFunction,compareTimeFunction);  //a List used to store the input car data

  //open the input data file
  fp = fopen(argv[1], "r");

  printf("Data File Information \n");
  //read in the input data file and store the car data into a list (sorted by arrival time)
  while(fscanf(fp, "%c %c %f \n", &travelDirection, &turnDirection, &timeOfArrival)!=EOF)
  {
    Data *newData =malloc(sizeof(Data)*1);
    newData->travelDirection = travelDirection;
    newData->turnDirection = turnDirection;
    newData->timeOfArrival = timeOfArrival;
    insertSorted(list, newData);
    printf("%c %c %f \n",travelDirection,turnDirection,timeOfArrival);
  }
  fclose(fp); //close the data file

  printf("\nSorted List \n");
  printForward(list);
  printf("\n");

  calculateTime(list);
  return 0;
}
void printChar(void *toBePrinted)
{
  Data* newdata1 = toBePrinted;
  printf("%c %c %f \n", newdata1->travelDirection, newdata1->turnDirection, newdata1->timeOfArrival);
}


int compareTimeFunction(void *firstData, void *secondData)
{

  Data* newdata1 = firstData;
  Data* newdata2 = secondData;

  float first =  newdata1->timeOfArrival;
  float second =  newdata2->timeOfArrival;

  //printf("\n Comparing %f and %f",first,second);
  if(first==second)
  {
    //printf("\n 0:equal");
    return 0;
  }
  else if(first>second)
  {
    //printf("\n 1:first greater");
    return 1;
  }
  //printf("\n -1:second greater");
  return -1;
}

int compareDataFunction(void *firstData,void *secondData)
{

  Data* newdata1 = firstData;
  Data* newdata2 = secondData;

  //printf("\n Comparing %f and %f",first,second);
  if((newdata1->timeOfArrival==newdata2->timeOfArrival)&&newdata1->travelDirection==newdata2->travelDirection&&newdata1->turnDirection==newdata2->turnDirection)
  {
    //printf("\n 0:equal");
    return 0;
  }
  else
  {
    //printf("\n 1:not equal");
    return 1;
  }
}

