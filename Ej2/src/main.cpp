#include "lanzador.h"

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 5){
        char* ms = "Cant incorrecta de parametros. \n Params cantPuertas, cantPersonas, usecs, capMaxima\n";
        write(STDOUT_FILENO,ms, strlen(ms));
        exit(1);
    }
    int cantPuertas = atoi(argv[1]);
    int personas = atoi(argv[2]);
    int usecs = atoi(argv[3]);
    int capMaxima =  atoi(argv[4]);

    Lanzador lanzador(cantPuertas,personas,usecs,capMaxima);
    lanzador.iniciarIPC();
    lanzador.lanzarPuertas();
   // lanzador.lanzarAdmin();

    lanzador.lanzarPersonas(personas);


    return 0;
}
