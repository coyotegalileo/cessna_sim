#include "simulator.h"


void derivatives(float* currentState,float* propParameters,float *dynamicParameters,float* derivedState)
{


   //Gravitic Terms
   float xGrav=currentState[MASS_OFF]*GRAVITY_ACCEL* sin(currentState[THETA_OFF]);
   float yGrav=-currentState[MASS_OFF]*GRAVITY_ACCEL* cos(currentState[THETA_OFF])*sin(currentState[PHI_OFF]);
   float zGrav=-currentState[MASS_OFF]*GRAVITY_ACCEL* cos(currentState[THETA_OFF])*cos(currentState[PHI_OFF]);


   //Inertial Terms
   float xInert=currentState[MASS_OFF]*currentState[Q_OFF]*currentState[W_OFF]-currentState[MASS_OFF]*currentState[R_OFF]*currentState[V_OFF];
   float yInert=currentState[MASS_OFF]*currentState[R_OFF]*currentState[U_OFF]-currentState[MASS_OFF]*currentState[P_OFF]*currentState[W_OFF];
   float zInert=currentState[MASS_OFF]*currentState[P_OFF]*currentState[V_OFF]-currentState[MASS_OFF]*currentState[Q_OFF]*currentState[U_OFF];

   float lInert=(JZ_GEO-JY_GEO)*currentState[Q_OFF]*currentState[R_OFF]-(JXZ_GEO)*currentState[P_OFF]*currentState[Q_OFF];
   float mInert=(JX_GEO-JZ_GEO)*currentState[P_OFF]*currentState[R_OFF]+(JXZ_GEO)*(std::pow(currentState[P_OFF],2)-std::pow(currentState[R_OFF],2));
   float nInert=(JY_GEO-JX_GEO)*currentState[P_OFF]*currentState[Q_OFF]-(JXZ_GEO)*currentState[Q_OFF]*currentState[R_OFF];


   //Propulsive Terms
   /*
   xProp=;
   yProp=;
   zProp=;

   lProp=;
   mProp=;
   nProp=;
   */
   //Gyroscopic Terms
   /*
   lRM=;
   mRM=;
   nRM=;
   */
   //Aerodynamic Terms
   //The dynamic vector carries these!


   //Derivatives
   derivedState[U_OFF]=(dynamicParameters[X_OFF]-xInert-xGrav-propParameters[XPROP_OFF])/currentState[MASS_OFF];
   derivedState[V_OFF]=(dynamicParameters[Y_OFF]-yInert-yGrav-propParameters[YPROP_OFF])/currentState[MASS_OFF];
   derivedState[W_OFF]=(dynamicParameters[Z_OFF]-zInert-zGrav-propParameters[ZPROP_OFF])/currentState[MASS_OFF];

   derivedState[P_OFF]=(1/(JX_GEO*JZ_GEO-JXZ_GEO*JXZ_GEO))*(JZ_GEO*dynamicParameters[L_OFF]+JXZ_GEO*dynamicParameters[N_OFF]-JZ_GEO*lInert-JXZ_GEO*nInert/*+ Derivadas de J*/-JZ_GEO*propParameters[LPROP_OFF]-JXZ_GEO*propParameters[NPROP_OFF]);
   derivedState[Q_OFF]=(dynamicParameters[M_OFF]-mInert-propParameters[MPROP_OFF]/*-Variação de Jy*/)/JY_GEO;
   derivedState[R_OFF]=(1/(JX_GEO*JZ_GEO-JXZ_GEO*JXZ_GEO))*(JX_GEO*dynamicParameters[N_OFF]+JXZ_GEO*dynamicParameters[L_OFF]-JX_GEO*nInert-JXZ_GEO*lInert/*+ Derivadas de J*/-JX_GEO*propParameters[NPROP_OFF]-JXZ_GEO*propParameters[LPROP_OFF]);

   derivedState[PHI_OFF]=currentState[P_OFF]+currentState[Q_OFF]*tan(currentState[THETA_OFF])*sin(currentState[PHI_OFF])+currentState[R_OFF]*tan(currentState[THETA_OFF])*cos(currentState[PHI_OFF]);
   derivedState[THETA_OFF]=currentState[Q_OFF]*cos(currentState[PHI_OFF])-currentState[R_OFF]*sin(currentState[PHI_OFF]);
   derivedState[PSI_OFF]=currentState[R_OFF]*cos(currentState[PHI_OFF])/cos(currentState[THETA_OFF])+currentState[Q_OFF]*currentState[R_OFF]*sin(currentState[PHI_OFF])/cos(currentState[THETA_OFF]);

   derivedState[XABS_OFF]=currentState[U_OFF]*cos(currentState[PSI_OFF])*cos(currentState[THETA_OFF])+currentState[V_OFF]*(cos(currentState[PSI_OFF])*sin(currentState[THETA_OFF])*sin(currentState[PHI_OFF])-sin(currentState[PSI_OFF])*cos(currentState[PHI_OFF]))+currentState[W_OFF]*(cos(currentState[PSI_OFF])*sin(currentState[THETA_OFF])*cos(currentState[PHI_OFF])+sin(currentState[PSI_OFF])*sin(currentState[PHI_OFF]));
   derivedState[YABS_OFF]=currentState[U_OFF]*sin(currentState[PSI_OFF])*cos(currentState[THETA_OFF])+currentState[V_OFF]*(sin(currentState[PSI_OFF])*sin(currentState[THETA_OFF])*sin(currentState[PHI_OFF])+cos(currentState[PSI_OFF])*cos(currentState[PHI_OFF]))+currentState[W_OFF]*(sin(currentState[PSI_OFF])*sin(currentState[THETA_OFF])*cos(currentState[PHI_OFF])+cos(currentState[PSI_OFF])*sin(currentState[PHI_OFF]));
   derivedState[ZABS_OFF]=currentState[U_OFF]*sin(currentState[THETA_OFF])-currentState[V_OFF]*cos(currentState[THETA_OFF])*sin(currentState[PHI_OFF])-currentState[W_OFF]*cos(currentState[THETA_OFF])*cos(currentState[PHI_OFF]);

// TODO (PedroFilipe#1#): Change to variable mass ...
//
   derivedState[MASS_OFF]=0;/*Change*/
}
