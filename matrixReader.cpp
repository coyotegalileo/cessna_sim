#include "simulator.h"

void matrxLoader (float *matrxPtr, const std::string& fileName, int sizes )
 {
   int i;
   std::ifstream inf(fileName.c_str());

   // If we couldn't open the output file stream for reading
   if (!inf)
   {
      std::cerr << "Uh oh,looks like file could not be opened for reading!" << std::endl;
      exit(1);
   }

   // Filling the array
   for(i=0;i<sizes;i++)
   {
      inf>>matrxPtr[i];
   }

 }
