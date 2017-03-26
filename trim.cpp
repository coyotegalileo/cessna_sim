

#include "simulator.h"


void residuals(float * currentState,float * flowAngles, float *controlParameters, float* trimParameters, float* atmosphereParameters, float** aeroMatrx, float* dynamicParameters, float* propParameters, float* residuals);

void trim(float initial_V, float h_initial, float* currentState, float* flowAngles, float* propParameters, float* atmosphereParameters, float* trimParameters,float** aeroMatrx)
{
   int i,j,n;
   float k;
   bool stop;

   // Initial Atributions (Steady Level Flight)
   currentState[V_OFF]=0;

   currentState[P_OFF]=0;
   currentState[Q_OFF]=0;
   currentState[R_OFF]=0;
   currentState[PHI_OFF]=0;

   currentState[PSI_OFF]=0; //Change posterior to different choices by user

   currentState[XABS_OFF]=0;
   currentState[YABS_OFF]=0;
   currentState[ZABS_OFF]=h_initial;
   currentState[MASS_OFF]=MASS_INITIAL;

   //Flow Angles Atributions
   flowAngles[BETA_OFF]=0;
   flowAngles[ALPHA_DOT_OFF]=0;
   flowAngles[BETA_DOT_OFF]=0;


  //Trim Guess
   trimParameters[DA_TRIM_OFF]=0;
   trimParameters[DE_TRIM_OFF]=0;
   trimParameters[DR_TRIM_OFF]=0;
   trimParameters[N_TRIM_OFF]=0;
   //trimParameters[ALPHA_TRIM_OFF]=0;

   //Control Parameters
   float controlParameters[CONTROL_SIZE]={0,0,0};


   float tTrim;
   float txTrim;
   float tzTrim;

   //Initial Guess
   float alphaTry=((currentState[MASS_OFF]*GRAVITY_ACCEL)/(0.5*initial_V*initial_V*atmosphereParameters[RHO_OFF]*WING_S_GEO)-(0.15500000))/(4.44497337);

   float deTry;

   flowAngles[ALPHA_OFF]=alphaTry;
   currentState[THETA_OFF]=alphaTry;
   currentState[W_OFF]=sqrt(pow(tan(flowAngles[ALPHA_OFF]),2)*pow(initial_V,2)/(pow(tan(flowAngles[ALPHA_OFF]),2)+1));
   if(flowAngles[ALPHA_OFF]<0)
   {
      currentState[W_OFF]=currentState[W_OFF]*-1;
   }
   currentState[U_OFF]=sqrt(pow(initial_V,2)-pow(currentState[W_OFF],2));



    // Interpolations
   float steady[AERO_STEADY_MATR_SIZE];
   float mder[AERO_MDER_MATR_SIZE];
   float mctr[AERO_MCTR_MATR_SIZE];
   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[STEADY_TAB_OFF], AERO_STEADY_MATR_SIZE, steady, 1);
   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[MDER_TAB_OFF], AERO_MDER_MATR_SIZE, mder, 1);
   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[MCTR_TAB_OFF], AERO_MCTR_MATR_SIZE, mctr, 1);




   deTry=-(steady[CM_OFF] +mder[CMA_OFF]*flowAngles[ALPHA_OFF] + mder[CMAP_OFF]*flowAngles[ALPHA_DOT_OFF]*WING_C_GEO/(2*initial_V) + mder[CMB_OFF]*flowAngles[BETA_OFF] + mder[CMP_OFF]*currentState[P_OFF]*(WING_B_GEO/(2*initial_V)) + mder[CMQ_OFF]*currentState[Q_OFF]*(WING_C_GEO/(2*initial_V)) + mder[CMR_OFF]*currentState[R_OFF]*(WING_B_GEO/(2*initial_V)))/mctr[CMDE_OFF];



   trimParameters[DE_TRIM_OFF]=deTry;

   //Dynamic parameters
   float aerodynamicParameters[DYNAMIC_SIZE];
   dynamic(currentState,flowAngles,controlParameters,trimParameters,atmosphereParameters,aeroMatrx,aerodynamicParameters);


   float xA=aerodynamicParameters[X_OFF];
   float zA=aerodynamicParameters[Z_OFF];

   txTrim= -1*(currentState[MASS_OFF]*GRAVITY_ACCEL*sin(currentState[THETA_OFF])-xA);
   tzTrim= -1*(-currentState[MASS_OFF]*GRAVITY_ACCEL*cos(currentState[THETA_OFF])-zA);

   tTrim=sqrt(txTrim*txTrim+tzTrim*tzTrim);

   tTrim=tTrim+1;

   propParameters[XPROP_OFF]=txTrim;
   propParameters[ZPROP_OFF]=tzTrim;


   //Test
   float result[STATE_SIZE];
   derivatives(currentState,propParameters,aerodynamicParameters,result);


   result[1]=1;
}


void propulsion (float N,float* propParameters,float* state)
{

   float max_T=5000;

   propParameters[0]=max_T*N*cos(state[THETA_OFF]);
   propParameters[1]=0;
   propParameters[2]=max_T*N*sin(state[THETA_OFF]);

}
