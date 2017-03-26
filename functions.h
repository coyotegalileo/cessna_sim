
#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H


//Functions organized by file name

//atmosphere.cpp
void atmosfera(float h, float atm0[], float atm[]);

//derivatives.cpp
void derivatives(float* currentState,float* propParameters,float *dynamicParameters,float* derivedState);

//dynamic.cpp
void dynamic(float* currentState, float *flowAngles, float *controlParameters, float *trimPrameters,float* atmosphereParameters , float** aeroMatrx, float *dynamicParameters);

//engine.cpp
void engine(float rho, float* engineParameters);

//input.cpp
void input(void);

//integrator.cpp
void integrate(float * currentState, float* derivedState, float* nextState, float interval);

//interpolator.cpp
void interpolator ( float *valueInterpol, float *table, const int paramNumber, float *interpolMatrx, int sizeInter);
float linearInterpol(float x, float x1, float x2, float y1, float y2);
void matrxSizeDet (int *nPar, int*nLin, const std::string& fileName );

//matrixInvert.cpp
void ludcmp(float *matrix,float* L, float* U ,int sizeM);
void lubksb(float *columnInput ,float* L, float* U,float* columnOutput ,int sizeM);
void matrixInvert(float* matrix,float *inv, int sizeM);

//matrxLoader.cpp
void matrxLoader (float *matrxPtr, const std::string& fileName, int size );

//save.cpp
void save(float* current, float time);

//testStop.cpp
bool testStop (float * state, float* atmosphere);

//trim.cpp
void trim(float initial_V, float h_initial, float* currentState, float* flowAngles, float* propParameters, float* atmosphereParameters, float* trimParameters,float** aeroMatrx);










#endif
