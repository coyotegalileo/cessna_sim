
#include "simulator.h"




int main()
{

    // Variables
    // Tables from .txt

    //Aerodynamic Tables Pointer
    float* aeroMatrx[AERO_MATRX_SIZE];
    //Aerodynamic Database
    float aeroSteadyMatrx[AERO_STEADY_MATR_SIZE*ALPHA_SIZE];
    float aeroXDerMatrx[AERO_XDER_MATR_SIZE*ALPHA_SIZE];
    float aeroYDerMatrx[AERO_YDER_MATR_SIZE*ALPHA_SIZE];
    float aeroZDerMatrx[AERO_ZDER_MATR_SIZE*ALPHA_SIZE];
    float aeroLDerMatrx[AERO_LDER_MATR_SIZE*ALPHA_SIZE];
    float aeroMDerMatrx[AERO_MDER_MATR_SIZE*ALPHA_SIZE];
    float aeroNDerMatrx[AERO_NDER_MATR_SIZE*ALPHA_SIZE];
    float aeroFCtrMatrx[AERO_FCTR_MATR_SIZE*ALPHA_SIZE];
    float aeroMCtrMatrx[AERO_MCTR_MATR_SIZE*ALPHA_SIZE];

    // Atmospheric Values (pressure temperature density speed_of_sound )
    float atmosphereParameters[ATMOSPHERE_SIZE];
    float atm0[ATMOSPHERE_SIZE]={101325,288.15,1.225,340}; //ISA -> 0 meters

    //Propulsion (xProp	yProp	zProp	lProp	mProp	nProp	lRM	mRM	nRM)
    float propParameters[PROP_PARAM_SIZE];

    //Flow Angles Parameters (alpha, beta, alpha_dot, beta_dot)
    float flowAngles[FLOW_ANGLES_SIZE];

    //Surfaces Control Parameters (delta_e,delta_a,delta_r)
    float controlParameters[CONTROL_SIZE]={0,0,0};

    //Trimming    (delta_e, delta_a,delta_r, propeller rotations)trim
    float trimParameters[TRIM_SIZE];

    //Dynamic Parameters   (X,Y,Z,L,M,N)
    float dynamicParameters[DYNAMIC_SIZE];

    // State Vectors (u v w p q r phi theta psi x y z m)
    float currentState[STATE_SIZE];
    float nextState[STATE_SIZE];

    //State Derivatives (du dv dw dp dq dr dphi dtheta dpsi dx dy dz dm)
    float derivedState[STATE_SIZE];

    //Time Related
    //Simulation Time
    float timeMax=TMAX_STANDARD;
    //Simulation Precision
    float timeInterval=TIME_PRECISION;
    //Current Time
    float timeCurrent=0;

   //Testing Stop Conditions
   bool stop;

   //Program Control Variables
   int i,j;

   //Initial Conditions Set by User
   float initial_V=60; //Testing parameters as default
   float initial_h=100;


/**********************************************************/
   // Program Start

   //To create a new file
   std::fstream inf;
   inf.open(SIM_FILE,std::ios::out|std::ios::trunc);
   // If we can't open the output file stream for reading
   if (!inf)
   {
      std::cerr << "Uh oh,looks like file could not be opened for writing!" << std::endl;
      exit(1);
   }
   inf.close();

   //Table Pointer Initialization
   aeroMatrx[0]=aeroSteadyMatrx;
   aeroMatrx[1]=aeroXDerMatrx;
   aeroMatrx[2]=aeroYDerMatrx;
   aeroMatrx[3]=aeroZDerMatrx;
   aeroMatrx[4]=aeroLDerMatrx;
   aeroMatrx[5]=aeroMDerMatrx;
   aeroMatrx[6]=aeroNDerMatrx;
   aeroMatrx[7]=aeroFCtrMatrx;
   aeroMatrx[8]=aeroMCtrMatrx;


   //Load Tables
   matrxLoader (aeroSteadyMatrx, AERO_STEADY_FILE, AERO_STEADY_MATR_SIZE*ALPHA_SIZE );
   matrxLoader (aeroXDerMatrx, AERO_XDER_FILE, AERO_XDER_MATR_SIZE*ALPHA_SIZE );
   matrxLoader (aeroYDerMatrx, AERO_YDER_FILE, AERO_YDER_MATR_SIZE*ALPHA_SIZE );
   matrxLoader (aeroZDerMatrx, AERO_ZDER_FILE, AERO_ZDER_MATR_SIZE*ALPHA_SIZE );
   matrxLoader (aeroLDerMatrx, AERO_LDER_FILE, AERO_LDER_MATR_SIZE*ALPHA_SIZE );
   matrxLoader (aeroMDerMatrx, AERO_MDER_FILE, AERO_MDER_MATR_SIZE*ALPHA_SIZE );
   matrxLoader (aeroNDerMatrx, AERO_NDER_FILE, AERO_NDER_MATR_SIZE*ALPHA_SIZE );
   matrxLoader (aeroFCtrMatrx, AERO_FCTR_FILE, AERO_FCTR_MATR_SIZE*ALPHA_SIZE );
   matrxLoader (aeroMCtrMatrx, AERO_MCTR_FILE, AERO_MCTR_MATR_SIZE*ALPHA_SIZE );
//matrxLoader (engineMatrx, ENGINE_FILE, ENGINE_MATR_SIZE );

/**********************************************************/
   //Initial Conditions Computation

   //User Input Data
   //input();
   //userInput(&initial_V, &initial_h);

   //Initial Atmosphere
   atmosfera(initial_h, atm0, atmosphereParameters);


   //Initial Trim
   trim(initial_V, initial_h,currentState, flowAngles, propParameters, atmosphereParameters, trimParameters, aeroMatrx);

   //Save First State
   //Writing in new file
   save(currentState, timeCurrent);
   timeCurrent=timeCurrent+timeInterval;
/**********************************************************/
   //Simulation Start

   for(i=1; i<timeMax/timeInterval; i++)
   {
      //Dynamic Parameters Computation
      dynamic(currentState,flowAngles,controlParameters,trimParameters,atmosphereParameters,aeroMatrx,dynamicParameters);

      //Derivatives Computation
      derivatives(currentState,propParameters,dynamicParameters,derivedState);

      //Display Simulation Time
      std::cout<<"\n\t"<< timeCurrent <<"\n";
      //Next State
      integrate(currentState,derivedState,nextState,timeInterval);

      //Save New State
      save(nextState, timeCurrent);

      //Test Stop
      stop=testStop(nextState, atmosphereParameters);


      if(stop==true)
      {
         //Stop Simulation
         break;
      }
      else
      {
         //Preparation for next iteration
         for(j=0;j<STATE_SIZE;j++)
         {
            currentState[j]=nextState[j];
         }

         timeCurrent=timeCurrent+timeInterval;

         // readManuever();

         //Refresh Atmosphere
         atmosfera(currentState[ZABS_OFF], atm0, atmosphereParameters);

         //Refresh Propulsion
        // propulsion(currentState,atmosphereParameters,engineParameters,propParameters,controlParameters); //Juntar manobra +trim

      }

   }

/**********************************************************/
   //Simulation Ended

   //Results
//   results();

   printf("\n\nSimulation Finished: Take the sim_results.dat file for results! \n\n");
    return 0;
}
