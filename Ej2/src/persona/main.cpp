#include <iostream>
#include "persona.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]){
    Persona* p;

    char* mess = "Iniciando Persona.. \n";
    write(STDOUT_FILENO,mess,strlen(mess) );
    char ms[200];

    int nroPersona = atoi(argv[0]);
    int cantPuertas = atoi(argv[1]);
    int tiempoMedia = atoi(argv[2]);

    sprintf(ms ,"Parametros recibidos cant = %d, idPersona=%d, cantPuertas=%d,tiempo=%d \n",argc,
                nroPersona,cantPuertas,tiempoMedia);
    write(STDOUT_FILENO,ms,strlen(ms) );

    p = new Persona(nroPersona,tiempoMedia, cantPuertas);
    p->run();

    return 0;
}
