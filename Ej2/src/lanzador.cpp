#include "lanzador.h"
#include "./common/processManager.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>

Lanzador::Lanzador(int cantPuertas, int cantPersonas, int tiempoMedia, int capMaxima ){
    this->cantPersonas = cantPersonas;
    this->cantPuertas = cantPuertas;
    this->tiempoMedia = tiempoMedia;
    this->capMaxima = capMaxima;
    this->actual = 0;
}

Lanzador::~Lanzador(){
}

void Lanzador::iniciarIPC(){
    //Crear e inicializar mutex
    int inicial = 1;
    this->mutex = new SemaforoBinario(MUTEX,inicial);
    this->semCapacidad = new SemaforoBinario(SEMCAP,1);
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


    //Crear la cola de mensajes
    key_t claveMsg = ftok(DIRECTORIO,MSGENT);
    if((colaEntrada = msgget(claveMsg,IPC_CREAT|IPC_EXCL|0660)) == -1){
        perror("Lanzador: Error al crear la cola de mensajes");
    }
    mess = "Creada la Cola de mensajes de Entrada\n";
    write(STDOUT_FILENO,mess, strlen(mess));
     //Crear la cola de mensajes
    key_t claveMsg2 = ftok(DIRECTORIO,MSGRESP);
    if((colaRespuesta = msgget(claveMsg2,IPC_CREAT|IPC_EXCL|0660)) == -1){
        perror("Lanzador: Error al crear la cola de mensajes");
    }
    mess = "Creada la Cola de mensajes de Respuestas\n";
    write(STDOUT_FILENO,mess, strlen(mess));

}

void Lanzador::lanzarPuertas(){
    char id[10];
    char mess[50];
    for(int i=0; i< this->cantPuertas; i++){
        sprintf(id,"%d",i+1);
        char* const argv[] = { const_cast<char*>(id),(char*)NULL};
        puertas.push_back(ProcessManager::run("./bin/puerta",argv));
        sprintf(mess,"Lanzada la puerta %d \n",i+1);
        write(STDOUT_FILENO,mess, strlen(mess));
    }
}

void Lanzador::lanzarPersonas(int cant){
    char mess[200];
    char id[10];
    char cantPuertas[10];
    char tiempoMedia[10];
    sprintf(cantPuertas,"%d",this->cantPuertas);
    sprintf(tiempoMedia,"%d",this->tiempoMedia);
    for(int i=0; i<cant;i++){
        sprintf(id,"%d",actual + i + 1);
        char* const argv[] = { const_cast<char*>(id),const_cast<char*>(cantPuertas),
                                const_cast<char*>(tiempoMedia),(char*)NULL};
        puertas.push_back(ProcessManager::run("./bin/persona",argv));
        sprintf(mess,"Lanzada la persona %d \n",actual +i +1 );
        write(STDOUT_FILENO,mess, strlen(mess));
    }
}

void Lanzador::lanzarAdmin(){
    char* const argv[] = { (char*)NULL};
    ProcessManager::run("./bin/admin",argv);
}

void Lanzador::removeIPC(){
    int shmid;
    key_t claveShm = ftok(DIRECTORIO,SHM);
    shmid = shmget(claveShm,sizeof(Museo),0660);
    shmctl(shmid,IPC_RMID,(struct shmid_ds*)0);
    this->mutex->eliminar();
    this->semCapacidad->eliminar();
    msgctl(colaEntrada, IPC_RMID,NULL);
    msgctl(colaRespuesta, IPC_RMID,NULL);
}

