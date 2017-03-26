#include "simulator.h"


void integrate(float * currentState, float* derivedState, float* nextState, float interval)
{
   //To advance in simulation
   int i;
   for(i=0;i<STATE_SIZE;i++)
   {
      nextState[i]=currentState[i]+interval*derivedState[i];
   }
}
