****************************************************
Logan Bell		    0972170
CIS2520		 	    Assignment1
June 3rd 2018	            lbell03@uoguelph.ca
****************************************************


************************
Program Description
**************************
This code takes information from a file which contains data for cars at an intersection. the cars have a direction, a time of arrival, and and turning direction. This program states the time the cars come at, the time they enter the intersection, and has average wait times and the maximum wait times.


************
Compilation
************
 To compile this code:
 run: make

****************************
Known Limitations, Issues and Errors
****************************
This program doesn't display averages if there are 0 cars in a specific direction.
This program makes the assumtion that if a north and south car are going the same direction, the north car gets to go first
This program makes the assumtion that if a east and west car are going the same direction, the east car gets to go first.
This program makes the assumtion that if all cars arrive at the same time from all directions, the north car gets to go first.



