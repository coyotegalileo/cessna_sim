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
      std::cout<<"\n --> WARNING <--\n"<< "Sembra che l'altitudine � sceso da zero.";
      std::cout<<"La simulazione � stata interrota oppure non sarebbe pi� rappresentativo della realt�."<< std::endl;
   }
   if(state[ZABS_OFF]>tangentZ)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'altitudine � sceso da zero.";
      std::cout<<"La simulazione � stata interrota oppure non sarebbe pi� rappresentativo della realt�."<< std::endl;
   }

   //Alpha
   alpha=atan(state[W_OFF]/state[U_OFF]);
   if(alpha>ALPHA_MAX)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'areo � andato sopra l'incidenza massima. Stallo iminente.";
      std::cout<<"La simulazione � stata interrota oppure non sarebbe pi� rappresentativo della realt�."<< std::endl;

   }
   if(alpha<ALPHA_MIN)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'areo � andato sotto l'incidenza minima.";
      std::cout<<"La simulazione � stata interrota oppure non sarebbe pi� rappresentativo della realt�."<< std::endl;
   }


   //Velocita
   V = (sqrt(pow(state[U_OFF],2)+pow(state[V_OFF],2)+pow(state[W_OFF],2)));
   if(V<V_MIN)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'areo � sotto la velocit� di stallo.";
      std::cout<<"La simulazione � stata interrota oppure non sarebbe pi� rappresentativo della realt�."<< std::endl;
   }
   if(V>V_MAX)
   {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'areo � sopra la velocit� massima.";
      std::cout<<"La simulazione � stata interrota oppure non sarebbe pi� rappresentativo della realt�."<< std::endl;
   }
   //Mach DR
   mach=V/atmosphere[SOUND_V_OFF];
   if(mach>MACH_DRAG_RISE)
    {
      //Signal program
      stop=true;

      //Warning
      std::cout<<"\n --> WARNING <--\n";
      std::cout<< "Sembra che l'areo � sopra il Mach drag rise.";
      std::cout<<"La simulazione � stata interrota oppure non sarebbe pi� rappresentativo della realt�."<< std::endl;
   }


   //Massa di combustibile





   return stop;
}
