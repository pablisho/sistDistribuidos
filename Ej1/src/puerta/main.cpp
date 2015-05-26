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

    char* mess = "Iniciando Puerta..";
    write(STDOUT_FILENO,mess,strlen(mess) );
    char ms[10];
    sprintf(ms ,"Parametros recibidos = %d",argc);
    write(STDOUT_FILENO,ms,strlen(ms) );
    int nroPuerta = atoi(argv[0]);
    int cantPersonas = atoi(argv[1]);
    int tiempoMedia = atoi(argv[2]);

    mess = "Obtenidos los params";
    write(STDOUT_FILENO,mess,strlen(mess) );

    mess = "Abierto el archivo";
    write(STDOUT_FILENO,mess,strlen(mess) );
    p = new Puerta(nroPuerta,cantPersonas,tiempoMedia);
    p->run();

    return 0;
}
