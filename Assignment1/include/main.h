#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
/**Function to print a character.
 *@pre must be a character
 *@param toBePrinted
 **/
void printChar(void *toBePrinted);
/**This compares the timeOfArrival between two cars.
 *@pre void must be of type data
 *@param firstdata and seconddata must be both pointers to data
 **/
int compareTimeFunction(void *firstData,void *secondData);
/**Function to be used for comparing data, mainly used for deleting nodes
 *@pre void must be of type data
 *@param firstdata and seconddata must be both pointers to data
 **/
int compareDataFunction(void *firstData,void *secondData);
#endif // MAIN_H_INCLUDED
