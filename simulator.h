

#ifndef _SIMUL_H
#define _SIMUL_H
/**********************************/
//Libraries Used
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"
#include "off_sets.h"
#include "airplane_char.h"


/**********************************/
//Variable Vectors Size (Flux Table Order)
#define STATE_SIZE 13
#define FLOW_ANGLES_SIZE 4
#define CONTROL_SIZE 3
#define TRIM_SIZE 4
#define DYNAMIC_SIZE 6
#define PROP_PARAM_SIZE 9
#define ENGINE_PARAM_SIZE 2
#define ATMOSPHERE_SIZE 4


/**********************************/
//Simulation Parameters
#define TIME_PRECISION 0.1
#define TMAX_STANDARD 2000

#define TRIM_TOLERANCE 0.001


/**********************************/
//Physical Constants
#define GRAVITY_ACCEL 9.81


/**********************************/
//Conversions
#define TO_DEGREES 180/3.14
#define TO_RAD  3.14/180


/**********************************/
//File Names
#define AERO_STEADY_FILE  "steady.txt"
#define AERO_XDER_FILE    "xder.txt"
#define AERO_YDER_FILE    "yder.txt"
#define AERO_ZDER_FILE    "zder.txt"
#define AERO_LDER_FILE    "lder.txt"
#define AERO_MDER_FILE    "mder.txt"
#define AERO_NDER_FILE    "nder.txt"
#define AERO_FCTR_FILE    "fctr.txt"
#define AERO_MCTR_FILE    "mctr.txt"

#define ENGINE_FILE  "engine.txt"
#define PROP_FILE    "prop.txt"
#define SIM_FILE     "sim_results.dat"


/**********************************/
//Sizes of Tables

//Number of Tables
#define AERO_MATRX_SIZE 9
//Data to read size
#define ALPHA_SIZE 126
//Number Of Parameters of each
#define AERO_STEADY_MATR_SIZE 7
#define AERO_XDER_MATR_SIZE 8
#define AERO_YDER_MATR_SIZE 7
#define AERO_ZDER_MATR_SIZE 8
#define AERO_LDER_MATR_SIZE 7
#define AERO_MDER_MATR_SIZE 8
#define AERO_NDER_MATR_SIZE 7
#define AERO_FCTR_MATR_SIZE 7
#define AERO_MCTR_MATR_SIZE 7


#endif
