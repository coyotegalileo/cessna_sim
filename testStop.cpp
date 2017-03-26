#include "simulator.h"



bool testStop (float * state, float* atmosphere)
{
   bool stop=false;
   float tangentZ=100000;// Change
   float alpha;
   float V;
   float mach;

   // Altitude
   if(state[ZABS_OFF]<0)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n"<< "Sembra che l'altitudine è sceso da zero.";
      std::cout<<"La simulazione è stata interrota oppure non sarebbe più rappresentativo della realtà."<< std::endl;
   }
   if(state[ZABS_OFF]>tangentZ)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'altitudine è sceso da zero.";
      std::cout<<"La simulazione è stata interrota oppure non sarebbe più rappresentativo della realtà."<< std::endl;
   }

   //Alpha
   alpha=atan(state[W_OFF]/state[U_OFF]);
   if(alpha>ALPHA_MAX)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'areo è andato sopra l'incidenza massima. Stallo iminente.";
      std::cout<<"La simulazione è stata interrota oppure non sarebbe più rappresentativo della realtà."<< std::endl;

   }
   if(alpha<ALPHA_MIN)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'areo è andato sotto l'incidenza minima.";
      std::cout<<"La simulazione è stata interrota oppure non sarebbe più rappresentativo della realtà."<< std::endl;
   }


   //Velocita
   V = (sqrt(pow(state[U_OFF],2)+pow(state[V_OFF],2)+pow(state[W_OFF],2)));
   if(V<V_MIN)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'areo è sotto la velocità di stallo.";
      std::cout<<"La simulazione è stata interrota oppure non sarebbe più rappresentativo della realtà."<< std::endl;
   }
   if(V>V_MAX)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'areo è sopra la velocità massima.";
      std::cout<<"La simulazione è stata interrota oppure non sarebbe più rappresentativo della realtà."<< std::endl;
   }
   //Mach DR
   mach=V/atmosphere[SOUND_V_OFF];
   if(mach>MACH_DRAG_RISE)
    {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'areo è sopra il Mach drag rise.";
      std::cout<<"La simulazione è stata interrota oppure non sarebbe più rappresentativo della realtà."<< std::endl;
   }


   //Massa di combustibile





   return stop;
}
