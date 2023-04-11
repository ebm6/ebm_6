/* GitHub link!!!!!!!!!!!!!!!!!!!!!!!
*
*    https://github.com/ebm6/ebm_6.git
*
*
**/
#include <stdio.h>

/****************************************************************
* Function: ArrayChanger(int arraysyze, int cmpArray[arraysyze])
*  
* Description: print the maximum, minimum and avarege values of an
*              n position array, also classified the even elements.
*         
* Inputs:  int arraysyze, int cmpArray[arraysyze]
* Outputs: newsize
***************************************************************/
int ArrayChanger(int arraysyze, int cmpArray[arraysyze])
{
   /*Local Variables*/
   int newsize = 0;
   int i = 0;
   int minimum = cmpArray[0];
   int maximum = cmpArray[0];
   float average = 0;
   
   /*Code*/
   printf("\nThe next array is just the even number(s) typed:\n");
   for (i =0; i< arraysyze; i++)
   {
      average = (average + cmpArray[i]);

      if(cmpArray[i]%2 == 0)                           //Classify the even numbers
      {
         printf("[%i] ",cmpArray[i]);  
         newsize ++;
      }
      if((minimum > cmpArray[i]) && i != 0)            //Minimum Number
      {
         minimum = cmpArray[i];
      }
      if((maximum < cmpArray[i]) && i != 0)            //Maximum Number
      {
         maximum = cmpArray[i];
      }
   }
   if(newsize == 0)
   {
      printf("no even number");
   }
   average = average/i;
   printf("\n\nFor the original typed array:\nThe average value is: %.2f\nThe Maximum value is: %i\nThe Minimum value is: %i", average, maximum, minimum);
   return newsize;
}

/****************************************************************
* Function: main(void)
*  
* Description: Main function.
*         
* Inputs:  None
* Outputs: 0
***************************************************************/
int main(void) 
{
   /*Local variables*/
   int arraysyze = 0;

   printf("Type the array size: ");
   scanf("%d", &arraysyze);

   /*Depended local variable*/
   int values[arraysyze];

   /*Code*/
   if(arraysyze > 0)                             //Must be bigger than zero
   {
      printf("\nEnter %i integers: ", arraysyze);

      /* taking input and storing it in an array*/
      for(int i = 0; i < arraysyze; ++i)
      {
         scanf("%d", &values[i]);
      }
      /*Print the result and call the function that will verify the array*/
      printf("\n\nFor the even number(s) array:\nThe new array size is: %i ", ArrayChanger(arraysyze,values));
   }
   printf("\nEND!");
   return 0;
}