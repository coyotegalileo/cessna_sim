#include <stdio.h>
#include <math.h>
#include <cmath>

int main()
{
// PREPROCESSING
    float pitch,dia,R,RPM,tip,xt,hub,xs,rho,n,omega,k,eff0,V,alpha,clalfa,cd0,e,S,AR,PI,thrust,torque,rad,theta,t2,th,sigma,a,b,V0,V2,phi,alfa,cl,cd,Vlocal,DtDr,DqDr,tem1,tem2,anew,bnew,a2[100],b2[100],t,q,J,eff;


// Dati necessari DA INPUT:
    pitch=0.0; /* angolo di incidenza (DA INPUT)*/
    rho=1.225; /* densità aria (DA INPUT) */
    V=60; /* velocità flusso indisturbato = velocità aereo (DA INPUT)*/
    RPM=2100.; /* numero giri al minuto DA INPUT */



// Altri dati:
    dia=2; /* diametro disco dell elica */
    R=dia/2.0; /* raggio disco dell elica */
    clalfa=3.984900; /* coefficiente CL_alfa */
    cd0=0.0235;
    e=0.8; /* fattore di Oswald */
    S=0.14605; /* area della pala */
    AR=pow(R,2)/S; /* Aspect Ratio */
    PI=3.14159265;

    n=RPM/60.0; /* trasforma in numero giri al secondo */
    omega=n*2.0*PI; /* velocità angolare di rotazione espressa in radianti al secondo */

// Vettore distanza stazioni dal centro
    float r1[49]={0.2,0.21,0.23,0.25,0.27,0.29,0.3,
              0.31,0.33,0.35,0.37,0.39,0.4,
              0.41,0.43,0.45,0.47,0.49,0.5,
              0.51,0.53,0.55,0.57,0.59,0.6,
              0.61,0.63,0.65,0.67,0.69,0.7,
              0.71,0.73,0.75,0.77,0.79,0.8,
              0.81,0.83,0.85,0.87,0.89,0.9,
              0.91,0.93,0.95,0.97,0.99,1};

// Vettore corda locale in corrispondenza della rispettiva stazione
    float chord[49]={0.198,0.198,0.198,0.198,0.198,0.198,0.198,
                     0.198,0.198,0.198,0.198,0.198,0.198,
                     0.198,0.198,0.198,0.198,0.198,0.198,
                     0.198,0.198,0.198,0.198,0.198,0.198,
                     0.198,0.198,0.198,0.198,0.197,0.197,
                     0.197,0.195,0.194,0.192,0.188,0.186,
                     0.185,0.179,0.174,0.167,0.157,0.152,
                     0.146,0.132,0.115,0.092,0.055,0.001};

// Vettore Blade Angle - svergolamento pala nella rispettiva stazione
    float BA[49]={58.875,57.565,55.069,52.731,50.545,48.501,
                  47.53,46.591,44.806,43.137,41.576,40.115,
                  39.42,38.746,37.463,36.258,35.125,34.06,
                  33.551,33.057,32.111,31.217,30.373,29.575,
                  29.191,28.818,28.001,26.32,25.473,24.657,
                  24.261,23.871,23.113,22.38,21.671,21.085,
                  20.75,20.42,19.875,19.248,18.739,18.346,
                  18.156,17.969,17.607,17.259,16.923,16.6,
                  16.443};

// Vettore stazioni lungo la pala

    k=0; /* inizializzo k */
    eff0=0; /* inizializzo l'efficienza */
    thrust=0.0; /* inizializzo la spinta */
    torque=0.0; /* inizializzo il momento torcente */



 //PROCESSING
    int j,finished,sum;

    for(j=0;j<49;j++) /* ciclo sulle stazioni */
        {
            rad=r1[j]; /* distanza della stazione dal centro del disco */
            theta=BA[j]+pitch;
            th=theta/180.0*PI;
            sigma=2.0*chord[j]/2.0/PI/rad;
            a=0.1; /* axial inflow factor */
            b=0.01; /* angular inflow factor */
            finished=0;

            for(sum=1;sum<500;sum++)
            {
                while (finished==0) /* lancia il ciclo di implementazione fino a convergenza, per ricavare a e b */
                {
                    V0=V*(1+a); /* vettore velocità assiale */
                    V2=omega*rad*(1-b); /* vettore velocità "angolare"  */
                    phi=atan2(V0,V2); /* angolo tra i vettori di velocità V0 e V2 */
                    alpha=th-phi;
                    cl=clalfa*alpha; /* cl=cl_alfa*alfa */
                    cd=cd0+(pow(cl,2))/(PI*AR*e); /* si calcola il cd come cd=cd0+cd_induced=(cd_skinfriction+cd_form)+cd_induced con cd_induced=(cl^2)/(pi*AR*e) */
                    Vlocal=sqrt(V0*V0+V2*V2); /* velocità V1 in modulo */
                    DtDr=0.5*rho*Vlocal*Vlocal*2.0*chord[j]*(cl*cos(phi)-cd*sin(phi)); /* spinta infinitesima stazione */
                    DqDr=0.5*rho*Vlocal*Vlocal*2.0*chord[j]*rad*(cd*cos(phi)+cl*sin(phi)); /* momento torcente infinitesimo stazione */
                    tem1=DtDr/(4.0*PI*rad*rho*V*V*(1+a)); /* restituisce il coefficiente a */
                    tem2=DqDr/(4.0*PI*rad*rad*rad*rho*V*(1+a)*omega); /* restituisce il coefficiente b */
                    anew=0.5*(a+tem1); /* va a rivalutare il coefficiente a */
                    bnew=0.5*(b+tem2); /* va a rivalutare il coefficiente b */

                    if ((std::abs(anew-a)<1.0e-5)&&((std::abs(bnew-b)<1.0e-5))) //Scarto che accetto
                         finished=1;

                    a=anew;
                    b=bnew;
                }}
            thrust=thrust+DtDr*(r1[1]-r1[0]); /* va a calcolare la spinta data dalla somma delle stazioni */
            torque=torque+DqDr*(r1[1]-r1[0]); /* va a calcolare il momento torcente dato dalla somma delle stazioni */
        }


//POSTPROCESSING
    printf("Thrust: %f",thrust);
    printf("Torque: %f",torque);
//EVENTUALMENTE (OPTIONAL)
    //t=thrust/(rho*n*n*dia*dia*dia*dia); /* coefficiente adimensionale della spinta */
    //q=torque/(rho*n*n*dia*dia*dia*dia*dia); /* coefficiente adimensionale del momento torcente */
    //J=V/(n*dia);
    /*if (t<0)
        eff=0.0;
    else
        eff=t/q*J/(2.0*PI); /* efficienza dell'elica, ovviamente solo se esiste una componente di spinta positiva */

    //printf("Efficienza: %f",eff);*/
    }
