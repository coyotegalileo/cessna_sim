/**/
/* Possibly the alpha dot and beta dots are needed. They haven't been added yet! */
/**/

#include "simulator.h"



void dynamic(float* currentState, float *flowAngles, float *controlParameters, float *trimPrameters,float* atmosphereParameters , float** aeroMatrx, float *dynamicParameters)
{

   float rho=atmosphereParameters[RHO_OFF];
   //Velocity
   float vTotal;
   //Surfaces deflection angle
   float delta_e, delta_a, delta_r;
   //Vectors Holding Aerodynamic Derivatives
   float steady[AERO_STEADY_MATR_SIZE];
   float xder[AERO_XDER_MATR_SIZE];
   float yder[AERO_YDER_MATR_SIZE];
   float zder[AERO_ZDER_MATR_SIZE];
   float lder[AERO_LDER_MATR_SIZE];
   float mder[AERO_MDER_MATR_SIZE];
   float nder[AERO_NDER_MATR_SIZE];
   float fctr[AERO_FCTR_MATR_SIZE];
   float mctr[AERO_MCTR_MATR_SIZE];


   //Alpha Computation
   flowAngles[ALPHA_OFF]=atan(currentState[W_OFF]/currentState[U_OFF]);//trimPrameters[ALPHA_TRIM_OFF];
   //Beta Computation
   flowAngles[BETA_OFF]=atan(currentState[V_OFF]/currentState[U_OFF]);

   //Surfaces Deflection
   delta_e=controlParameters[DE_OFF]+trimPrameters[DE_TRIM_OFF];
   delta_a=controlParameters[DA_OFF]+trimPrameters[DA_TRIM_OFF];
   delta_r=controlParameters[DR_OFF]+trimPrameters[DR_TRIM_OFF];
   //Vtotal Computation
   vTotal= std::sqrt(std::pow(currentState[U_OFF],2)+std::pow(currentState[V_OFF],2)+std::pow(currentState[W_OFF],2));


   // Interpolations
   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[STEADY_TAB_OFF], AERO_STEADY_MATR_SIZE, steady, 1);

   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[XDER_TAB_OFF], AERO_XDER_MATR_SIZE, xder, 1);
   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[YDER_TAB_OFF], AERO_YDER_MATR_SIZE, yder, 1);
   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[ZDER_TAB_OFF], AERO_ZDER_MATR_SIZE, zder, 1);

   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[LDER_TAB_OFF], AERO_LDER_MATR_SIZE, lder, 1);
   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[MDER_TAB_OFF], AERO_MDER_MATR_SIZE, mder, 1);
   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[NDER_TAB_OFF], AERO_NDER_MATR_SIZE, nder, 1);

   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[FCTR_TAB_OFF], AERO_FCTR_MATR_SIZE, fctr, 1);
   interpolator ( &flowAngles[ALPHA_OFF], aeroMatrx[MCTR_TAB_OFF], AERO_MCTR_MATR_SIZE, mctr, 1);





   //Aerodynamic Forces
   dynamicParameters[X_OFF]=0.5*rho*std::pow(vTotal,2)*WING_S_GEO*(steady[CX_OFF] + xder[CXA_OFF]*flowAngles[ALPHA_OFF] + xder[CXAP_OFF]*flowAngles[ALPHA_DOT_OFF]*WING_C_GEO/(2*vTotal) + xder[CXB_OFF]*flowAngles[BETA_OFF] + xder[CXP_OFF]*currentState[P_OFF]*(WING_B_GEO/(2*vTotal)) + xder[CXQ_OFF]*currentState[Q_OFF]*(WING_C_GEO/(2*vTotal)) + xder[CXR_OFF]*currentState[R_OFF]*(WING_B_GEO/(2*vTotal)) + fctr[CXDE_OFF]*delta_e);

   dynamicParameters[Y_OFF]=0.5*rho*std::pow(vTotal,2)*WING_S_GEO*(steady[CY_OFF] + yder[CYA_OFF]*flowAngles[ALPHA_OFF] + yder[CYB_OFF]*flowAngles[BETA_OFF] + yder[CYBP_OFF]*flowAngles[BETA_DOT_OFF]*WING_B_GEO/(2*vTotal) + yder[CYP_OFF]*currentState[P_OFF]*(WING_B_GEO/(2*vTotal)) + yder[CYQ_OFF]*currentState[Q_OFF]*(WING_C_GEO/(2*vTotal)) + yder[CYR_OFF]*currentState[R_OFF]*(WING_B_GEO/(2*vTotal)) + fctr[CYDA_OFF]*delta_a + fctr[CYDR_OFF]*delta_r);

   dynamicParameters[Z_OFF]=0.5*rho*std::pow(vTotal,2)*WING_S_GEO*(steady[CZ_OFF] + zder[CZA_OFF]*flowAngles[ALPHA_OFF] + zder[CZAP_OFF]*flowAngles[ALPHA_DOT_OFF]*WING_C_GEO/(2*vTotal) + zder[CZB_OFF]*flowAngles[BETA_OFF] + zder[CZP_OFF]*currentState[P_OFF]*(WING_B_GEO/(2*vTotal)) + zder[CZQ_OFF]*currentState[Q_OFF]*(WING_C_GEO/(2*vTotal)) + zder[CZR_OFF]*currentState[R_OFF]*(WING_B_GEO/(2*vTotal)) + fctr[CZDE_OFF]*delta_e);

   //Aerodynamic Moments
   dynamicParameters[L_OFF]=0.5*rho*std::pow(vTotal,2)*WING_S_GEO*WING_B_GEO*(steady[CL_OFF] +lder[CLA_OFF]*flowAngles[ALPHA_OFF] + lder[CLB_OFF]*flowAngles[BETA_OFF] + lder[CLP_OFF]*currentState[P_OFF]*(WING_B_GEO/(2*vTotal)) + lder[CLQ_OFF]*currentState[Q_OFF]*(WING_C_GEO/(2*vTotal)) + lder[CLR_OFF]*currentState[R_OFF]*(WING_B_GEO/(2*vTotal)) + mctr[CLDA_OFF]*delta_a + mctr[CLDR_OFF]*delta_r);

   dynamicParameters[M_OFF]=0.5*rho*std::pow(vTotal,2)*WING_S_GEO*WING_C_GEO*(steady[CM_OFF] +mder[CMA_OFF]*flowAngles[ALPHA_OFF] + mder[CMAP_OFF]*flowAngles[ALPHA_DOT_OFF]*WING_C_GEO/(2*vTotal) + mder[CMB_OFF]*flowAngles[BETA_OFF] + mder[CMP_OFF]*currentState[P_OFF]*(WING_B_GEO/(2*vTotal)) + mder[CMQ_OFF]*currentState[Q_OFF]*(WING_C_GEO/(2*vTotal)) + mder[CMR_OFF]*currentState[R_OFF]*(WING_B_GEO/(2*vTotal)) + mctr[CMDE_OFF]*delta_e);

   dynamicParameters[N_OFF]=0.5*rho*std::pow(vTotal,2)*WING_S_GEO*WING_B_GEO*(steady[CN_OFF] +nder[CNA_OFF]*flowAngles[ALPHA_OFF] + nder[CNB_OFF]*flowAngles[BETA_OFF] + nder[CNP_OFF]*currentState[P_OFF]*(WING_B_GEO/(2*vTotal)) + nder[CNQ_OFF]*currentState[Q_OFF]*(WING_C_GEO/(2*vTotal)) + nder[CNR_OFF]*currentState[R_OFF]*(WING_B_GEO/(2*vTotal)) + mctr[CNDA_OFF]*delta_a + mctr[CNDR_OFF]*delta_r);


}
