#include "simulator.h"


void save(float* current, float time)
{
   int i;
//Writing in new file
   std::fstream inf;
   inf.open(SIM_FILE,std::ios::out|std::ios::app);

   // If we can't open the output file stream for reading
   if (!inf)
   {
      std::cerr << "Uh oh,looks like file could not be opened for writing!" << std::endl;
      exit(1);
   }

   inf<<time<<"\t";
   // Filling the array
   for(i=0;i<STATE_SIZE;i++)
   {
      inf<<current[i]<<"\t";
   }
   inf<<"\n";
}
