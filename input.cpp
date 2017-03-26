#include "simulator.h"




void input(void)
{
    int scelta=0,i=0,j=0;
    float atm0[4]={101325,288,1.225,340}, h=0, atm[4];
    printf("\n\t\t\t\t   ATMOSFERA ISA\n\n");// vedere codice scii per inserire caratteri spciali
    printf(" La simulazione verra' svolta segueno il modello di atmosfera ISA avente a quota zero (Sea Level) => h=0 m i seguenti valori caratteristici:\n\n");
    printf("\t Pressione            P  =  101325  Pa \n");
    printf("\t Tremperatura         T  =  15      C \n");
    printf("\t Densita'            rho =  1,225   kg/m^3 \n\n");
    printf("\t velocita' del suono  a  =  340     m/s \n\n");
    printf("Se non si desidera procedere con questi paramentri e' possible modificarli, \nreinserendoli sia per h=0 m sia per la quota desiderata di inizio simulazione.\n");
    do
    {
        printf("\nPreme:\n \t1 se si vuole procedere senza modifica;\n \t2 per modificare i dati a h=0 m ;\n \t3 per modifica a una quota specifica; \n\t\n");
        scanf("%d", &scelta);
        getchar();// si mette per evitare che si inserisca per sbalgio una lettera
        if (scelta==2 || scelta==3)
        {
            quo:
            atm0[0]=120001;
            printf("\n Inserire valore della pressione alla quata desiderata [Pa]: ");
            scanf("%f", &atm0[0]);
            getchar();// lo mettiamo solo per ovviare alla eventualità che l utente inserisca una lettera per sbaglio
            if (atm0[0]<25000 || atm0[0]>120000 )//mettere valore di quota di tangenza
            {
                printf("\n valore non valido ; \t immettere un valore tra 25000 e 120000 Pa");
                goto quo;
            }

            qua:
            printf("\n Inserire valore della temperatura alla quota desiderata [°C]: ");
            scanf("%f", &atm0[1]);
            if (atm0[1]<-50 || atm0[1]>50)//mettere valore di quota di tangenza
            {
                getchar();
                printf("\n valore non valido ; \t immettere un valore tra -50 e 50 °C");
                goto qua;
            }
            atm0[1]=atm0[1]+273.15;
            i=1;
            getchar();

            qui:
            if (scelta==3)
            {
                h=-1;
                printf("\n Inserire la quota desiderata [m]: ");
                scanf("%f", &h);

                if (h<0 || h>7000)//mettere valore di quota di tangenza
                {    getchar();
                     printf("\n valore non valido; \t immettere un valore tra 0 e 7000 m");
                     goto qui;
                }


                atm0[0]=atm0[0]/pow((atm0[1]/(atm0[1]+0.0065*h)),5.2561);//pressione in quota
                atm0[1]=atm0[1]+0.0065*h;//temperatura in quota riferita a temperatura a terra
            }
            printf("\n Condizioni iniziali a %f m ( %f feat) impostate dall'utente salvate!\n\n", h, h*3.28084);
        }

        if(scelta==1)
        {
           i=1;
        }

        if (scelta!=1 && scelta!=2 && scelta!=3)
            printf("\nvalore inserito non valido, rileggere meglio le istruzioni\n");


    }while (i==0);
    for(j=0;j<4;j++)
    printf( "atm0, %d  %f  ",j+1,atm0[j]);

    atmosfera( h, atm0, atm);


    printf("\natmosfera impostata correttamente\n");

}


