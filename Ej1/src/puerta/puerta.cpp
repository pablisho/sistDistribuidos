#include "puerta.h"
#include "../common/lock.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>

Puerta::Puerta(int nroPuerta, int cantPersonas, int mediaTiempo){
    this->cantPersonas = cantPersonas;
    this->mediaTiempo = mediaTiempo;
    this->nroPuerta = nroPuerta;
    srand(time(NULL) + nroPuerta);
}

Puerta::~Puerta(){

}

bool Puerta::ponerPersona(){
    char mess[100];
    Lock l(mutex);
    sprintf(mess, "Paso el semaforo la puerta %d \n", this->nroPuerta);
    write(STDOUT_FILENO,mess, strlen(mess));
    if(shmem->abierto){
        sprintf(mess, "Mueseo Abierto - puerta %d \n", this->nroPuerta);
        write(STDOUT_FILENO,mess, strlen(mess));
        if(shmem->personasAdentro < shmem->maxPersonas){
            sprintf(mess, "La persona entra por la puerta %d \n", this->nroPuerta);
            write(STDOUT_FILENO,mess, strlen(mess));
            shmem->personasAdentro++;
            sprintf(mess, "Hay %d personas \n", shmem->personasAdentro);
            write(STDOUT_FILENO,mess, strlen(mess));
            return true;
        }else{
            sprintf(mess, "Capacidad maxima, la persona se va \n");
            write(STDOUT_FILENO,mess, strlen(mess));
        }
    }
    return false;
}

bool Puerta::sacarPersona(){
    char mess[100];
    Lock l(mutex);
    sprintf(mess, "Paso el semaforo la puerta %d \n", this->nroPuerta);
    write(STDOUT_FILENO,mess, strlen(mess));
    if(shmem->abierto){
        sprintf(mess, "Mueseo Abierto - puerta %d \n", this->nroPuerta);
        write(STDOUT_FILENO,mess, strlen(mess));
        if(shmem->personasAdentro > 0){
            sprintf(mess, "La persona sale por la puerta %d \n", this->nroPuerta);
            write(STDOUT_FILENO,mess, strlen(mess));
            shmem->personasAdentro--;
            sprintf(mess, "Hay %d personas \n", shmem->personasAdentro);
            write(STDOUT_FILENO,mess, strlen(mess));
        }else{
            sprintf(mess, "No habia personas, no tiene sentido sacar \n", shmem->personasAdentro);
            write(STDOUT_FILENO,mess, strlen(mess));
        }
    }else{
        sprintf(mess, "Mueseo Cerrado. Si hay personas las saco.", this->nroPuerta);
        write(STDOUT_FILENO,mess, strlen(mess));
        if(shmem->personasAdentro){
            sprintf(mess, "%d personas salen por la puerta %d.", shmem->personasAdentro,this->nroPuerta);
            write(STDOUT_FILENO,mess, strlen(mess));
        }
        shmem->personasAdentro = 0;
        return true;
    }
    return false;
}

void Puerta::getIPC(){
    char mess[100];
    sprintf(mess, "Obtenido el semaforo por la puerta %d \n", this->nroPuerta);
    write(STDOUT_FILENO,mess, strlen(mess));
    this->mutex = new SemaforoBinario(MUTEX);

    //Obtener la shared memory
    key_t claveShm = ftok(DIRECTORIO,SHM);
    if((shmid = shmget(claveShm,sizeof(Museo),0660)) == -1){
        perror("Lanzador: Error al crear la shared memory");
        exit(1);
    }

    if((shmem = (Museo*) shmat(shmid,0,0)) == (Museo*) -1){
        perror("Lanzador: Error al attachear la shared memory");
        exit(1);
    }
    sprintf(mess, "Obtenida la shared mem por la puerta %d \n", this->nroPuerta);
    write(STDOUT_FILENO,mess, strlen(mess));

}

void Puerta::generarPersona(){
    int t = rand() % this->mediaTiempo;
    usleep(t);
    char mess[100];
    sprintf(mess, "Persona generada por la puerta %d desp de %d usecs \n", this->nroPuerta,t);
    write(STDOUT_FILENO,mess, strlen(mess));
}

void Puerta::run(){
    getIPC();
    for(int i=0; i<this->cantPersonas; i++){
        generarPersona();
        int entra = rand() % 2;
        char mess[100];
        if (entra){
            //sprintf(mess,"La persona intenta entrar por la puerta %d \n",this->nroPuerta);
            //write(STDOUT_FILENO,mess, strlen(mess));
            ponerPersona();
        }else{
            //sprintf(mess,"La persona intenta salir por la puerta %d \n",this->nroPuerta);
            //write(STDOUT_FILENO,mess, strlen(mess));
            bool cerrado = sacarPersona();
            if (cerrado){
                break;
            }
        }
    }
}

