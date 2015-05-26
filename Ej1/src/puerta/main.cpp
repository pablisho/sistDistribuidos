#include <iostream>
#include <stdlib.h>
#include "puerta.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]){
    Puerta* p;

    char* mess = "Iniciando Puerta.. \n";
    write(STDOUT_FILENO,mess,strlen(mess) );
    char ms[200];

    int nroPuerta = atoi(argv[0]);
    int cantPersonas = atoi(argv[1]);
    int tiempoMedia = atoi(argv[2]);

    sprintf(ms ,"Parametros recibidos cant = %d, nroPuerta=%d, cantPersonas=%d,tiempo=%d \n",argc,
                nroPuerta,cantPersonas,tiempoMedia);
    write(STDOUT_FILENO,ms,strlen(ms) );

    p = new Puerta(nroPuerta,cantPersonas,tiempoMedia);
    p->run();

    return 0;
}
