
#include "simulator.h"

#define POWER_SL 1
#define POWER_VAR_EXPONENT 1
#define RPM_MAX 1
#define RPM_MIN 1
#define RHO_SL 1

void engine(float rho, float* engineParameters)
{
//engine(currentState,rho, engineParameters);


   float maxPower=POWER_SL*pow((rho/RHO_SL),(POWER_VAR_EXPONENT));

   if(engineParameters[NROT_OFF]>RPM_MAX)
   {

   }
   if(engineParameters[NROT_OFF]<RPM_MIN)
   {

   }
}
