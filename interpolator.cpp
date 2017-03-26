/**********************************************/
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*                                           */
/*********************************************/

#include "simulator.h"



void interpolator ( float *valueInterpol, float *table, const int paramNumber, float *interpolMatrx, int sizeInter)
{



   int i=0,j, k=0, k_old;

   if(valueInterpol[i]*TO_DEGREES<-5||valueInterpol[i]*TO_DEGREES>20)
   {
      printf("\nWARNING!\n");
      printf("Seems like the angle of attack was out of range! ---> Simulation Stopped!");
      exit(0);
   }


   //Cycle to find the place where the values are interpolated
      while(k<sizeInter)
      {
         // Control of having several values in the same interval
         k_old=k;
         // Test if value is within -> interpolate
         if(table[i*paramNumber]<=valueInterpol[k]*TO_DEGREES && table[paramNumber*(i+1)]>=valueInterpol[k]*TO_DEGREES)
         {
               // Atrubutes the first column
               interpolMatrx[0+k*paramNumber]=valueInterpol[k];
               // Cycle to interpolate the elements of the row.
               for(j=1; j<paramNumber; j++)
               {
                  interpolMatrx[j+k*paramNumber]=linearInterpol(valueInterpol[k]*TO_DEGREES, table[i*paramNumber], table[paramNumber*(i+1)], table[i*paramNumber+j], table[paramNumber*(i+1)+j]);
               }
               k++;
         }
         // Control of having several values in the same interval
         if(k_old==k)
            i++;
      }




 }

// The function that makes the interpolation work
 float linearInterpol(float x, float x1, float x2, float y1, float y2)
 {
   float y;

   y= y1 + (x-x1) * (y2-y1) / (x2-x1);

   return y;
 }

 void matrxSizeDet (int *nPar, int*nLin, const std::string& fileName )
 {
   std::string line, aux;
   int nLines=0, nParam=-1; // -1 because of the \n character
   std::ifstream inf(fileName.c_str());

   // If we couldn't open the output file stream for reading
   if (!inf)
   {
      std::cerr << "Uh oh,looks like file could not be opened for reading!" << std::endl;
      exit(1);
   }

   // Gets first line to count parameters
   getline (inf,line);
   nLines++;
   // Counting of row elements
   std::istringstream lineStream(line);
   while(lineStream)
   {
     lineStream>>aux;
     nParam++;
   }

   // Counting of rows
   while(getline (inf,line))
      {
         nLines++;
      }

   // Attribution of the numbers
   *nPar=nParam;
   *nLin=nLines;
 }
