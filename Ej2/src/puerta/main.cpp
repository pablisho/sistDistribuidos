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

    sprintf(ms ,"Parametros recibidos cant = %d, nroPuerta=%d, \n",argc,
                nroPuerta);
    write(STDOUT_FILENO,ms,strlen(ms) );

    p = new Puerta(nroPuerta);
    p->run();

    return 0;
}
