#include "admin.h"
#include "./common/lock.h"
#include "./common/processManager.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>


Admin::Admin(){
    getIPC();
}

Admin::~Admin(){
}

void Admin::getIPC(){
    char mess[100];
    sprintf(mess, "Obtenido el semaforo por el admin \n");
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
    sprintf(mess, "Obtenida la shared mem por el admin");
    write(STDOUT_FILENO,mess, strlen(mess));
}

void Admin::abrirMuseo(){
    this->shmem->abierto =true;
    this->mutex->v();
}

void Admin::cerrarMuseo(){
    Lock l(mutex);
    this->shmem->abierto=false;
}
