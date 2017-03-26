#ifndef _OFF_SETS_H
#define _OFF_SETS_H


/**********************************/
/*Arrays Off Sets (Same Order as in Table of Flux)*/

// State Off-Sets
#define U_OFF 0
#define V_OFF 1
#define W_OFF 2
#define P_OFF 3
#define Q_OFF 4
#define R_OFF 5
#define PHI_OFF 6
#define THETA_OFF 7
#define PSI_OFF 8
#define XABS_OFF 9
#define YABS_OFF 10
#define ZABS_OFF 11
#define MASS_OFF 12

// flowAngles Off-Sets
#define ALPHA_OFF 0
#define BETA_OFF 1
#define ALPHA_DOT_OFF 2
#define BETA_DOT_OFF 3

// controlParameters Off-Sets
#define DE_OFF 0
#define DA_OFF 1
#define DR_OFF 2

// trimParameters Off-Sets
#define DE_TRIM_OFF 0
#define DA_TRIM_OFF 1
#define DR_TRIM_OFF 2
#define N_TRIM_OFF 3

// dynamicParameters Off-Sets
#define X_OFF 0
#define Y_OFF 1
#define Z_OFF 2
#define L_OFF 3
#define M_OFF 4
#define N_OFF 5

// propParameters Off-Sets
#define XPROP_OFF 0
#define YPROP_OFF 1
#define ZPROP_OFF 2
#define LPROP_OFF 3
#define MPROP_OFF 4
#define NPROP_OFF 5
#define LRM_OFF 6
#define MRM_OFF 7
#define NRM_OFF 8

// engineParameters Off-Sets
#define NROT_OFF 0
#define QS_OFF 1
#define POWER_OFF 2

//atmosphereParameters Off- Sets
#define PRESSURE_OFF 0
#define TEMPERATURE_OFF 1
#define RHO_OFF 2
#define SOUND_V_OFF 3




/**********************************/
/* Tables Off Sets */

//Array of Tables
#define STEADY_TAB_OFF 0
#define XDER_TAB_OFF 1
#define YDER_TAB_OFF 2
#define ZDER_TAB_OFF 3
#define LDER_TAB_OFF 4
#define MDER_TAB_OFF 5
#define NDER_TAB_OFF 6
#define FCTR_TAB_OFF 7
#define MCTR_TAB_OFF 8

// steady Off-Sets
#define CX_OFF 1
#define CY_OFF 2
#define CZ_OFF 3
#define CL_OFF 4
#define CM_OFF 5
#define CN_OFF 6

// xder Off-Sets
#define A_OFF 0
#define CXA_OFF 1
#define CXAP_OFF 2
#define CXU_OFF 3
#define CXQ_OFF 4
#define CXB_OFF 5
#define CXP_OFF 6
#define CXR_OFF 7

// yder Off-Sets
#define CYB_OFF 1
#define CYBP_OFF 2
#define CYP_OFF 3
#define CYR_OFF 4
#define CYA_OFF 5
#define CYQ_OFF 6

// zder Off-Sets
#define CZA_OFF 1
#define CZAP_OFF 2
#define CZU_OFF 3
#define CZQ_OFF 4
#define CZB_OFF 5
#define CZP_OFF 6
#define CZR_OFF 7

// lder Off-Sets
#define CLB_OFF 1
#define CLBP_OFF 2
#define CLP_OFF 3
#define CLR_OFF 4
#define CLA_OFF 5
#define CLQ_OFF 6

// mder Off-Sets
#define CMA_OFF 1
#define CMAP_OFF 2
#define CMU_OFF 3
#define CMQ_OFF 4
#define CMB_OFF 5
#define CMP_OFF 6
#define CMR_OFF 7

// nder Off-Sets
#define CNB_OFF 1
#define CNBP_OFF 2
#define CNP_OFF 3
#define CNR_OFF 4
#define CNA_OFF 5
#define CNQ_OFF 6

// fctr Off-Sets
#define CXDE_OFF 1
#define CXDLE_OFF 2
#define CZDE_OFF 3
#define CZDLE_OFF 4
#define CYDA_OFF 5
#define CYDR_OFF 6

// mctr Off-Sets
#define CLDA_OFF 1
#define CLDR_OFF 2
#define CMDE_OFF 3
#define CMDLE_OFF 4
#define CNDA_OFF 5
#define CNDR_OFF 6
/**********************************/
#endif
