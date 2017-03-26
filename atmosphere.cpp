#include "simulator.h"

void atmosfera(float h, float atm0[], float atm[])
{
    // atm = p t rho a
    atm[1]=atm0[1]-0.0065*h;//temperatura in quota riferita a temperatura a terra
    atm[0]=atm0[0]*pow((atm[1]/atm0[1]),5.2561);//pressione in quota
    atm[2]=1.2257*pow((atm[1]/atm0[1]),4.2561);//densità
    atm[3]=sqrt(48.27593248*8.314472*atm[1]);//velocità del suono
   return ;
}
