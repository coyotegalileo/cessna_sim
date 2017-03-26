#ifndef _AIRPLANE_C_H
#define _AIRPLANE_C_H


//Plane Geometry
#define WING_S_GEO 16.300000000
#define WING_C_GEO 1.49
#define WING_B_GEO 10.92000000000000

#define JX_GEO 1272.5
#define JY_GEO 1806.7
#define JZ_GEO 2640.3
#define JXZ_GEO 0

//Initial Parameters
#define MASS_INITIAL 1043

//Limits
#define ALPHA_MAX 20*TO_RAD
#define ALPHA_MIN -5*TO_RAD
#define V_MIN 25.4813
#define V_MAX 81.3613
#define MACH_DRAG_RISE 0.6
#define DE_MAX  20
#define DE_MIN -20
#define DA_MAX  20
#define DA_MIN -20
#define DR_MAX  20
#define DR_MIN -20


#endif
