#include "lanzador.h"
#include "./common/processManager.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>

Lanzador::Lanzador(int cantPuertas, int cantPersonas, int tiempoMedia, int capMaxima ){
    this->cantPersonas = cantPersonas;
    this->cantPuertas = cantPuertas;
    this->tiempoMedia = tiempoMedia;
    this->capMaxima = capMaxima;
}

Lanzador::~Lanzador(){
}

void Lanzador::iniciarIPC(){
    //Crear e inicializar mutex
    int inicial = 0;
    this->mutex = new SemaforoBinario(MUTEX,inicial);
    char* mess = "Creado el Semaforo \n";
    write(STDOUT_FILENO,mess, strlen(mess));

    //Crear e inicializar la shared memory
    key_t claveShm = ftok(DIRECTORIO,SHM);
    if((shmid = shmget(claveShm,sizeof(Museo),IPC_CREAT | IPC_EXCL|0660)) == -1){
        perror("Lanzador: Error al crear la shared memory");
        exit(1);
    }

    if((shmem = (Museo*) shmat(shmid,0,0)) == (Museo*) -1){
        perror("Lanzador: Error al attachear la shared memory");
        exit(1);
    }

    mess = "Creada la shared memory \n";
    write(STDOUT_FILENO,mess, strlen(mess));
    shmem->abierto = false;
    shmem->personasAdentro = 0;
    shmem->maxPersonas = this->capMaxima;

}

void Lanzador::lanzarPuertas(){
    char id[10];
    char cantPersonas[10];
    char tiempoMedia[10];
    sprintf(cantPersonas, "%d",this->cantPersonas);
    sprintf(tiempoMedia, "%d", this->tiempoMedia);
    char mess[50];
    for(int i=0; i< this->cantPuertas; i++){
        sprintf(id,"%d",i);
        char* const argv[] = { const_cast<char*>(id),const_cast<char*>(cantPersonas),
                                const_cast<char*>(tiempoMedia),(char*)NULL};
        puertas.push_back(ProcessManager::run("./bin/puerta",argv));
        sprintf(mess,"Lanzada la puerta %d \n",i);
        write(STDOUT_FILENO,mess, strlen(mess));
    }
}

void Lanzador::removeIPC(){
    int shmid;
    key_t claveShm = ftok(DIRECTORIO,SHM);
    shmid = shmget(claveShm,sizeof(Museo),0660);
    shmctl(shmid,IPC_RMID,(struct shmid_ds*)0);
    this->mutex->eliminar();
}

