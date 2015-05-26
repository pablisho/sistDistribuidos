#include "puerta.h"
#include "../common/lock.h"
#include "../common/mensaje.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <errno.h>

Puerta::Puerta(int nroPuerta){
    this->nroPuerta = nroPuerta;
}

Puerta::~Puerta(){

}

bool Puerta::ponerPersona(int idPersona){
    char mess[100];
    mutex->p();
    sprintf(mess, "Paso el semaforo la puerta %d \n", this->nroPuerta);
    write(STDOUT_FILENO,mess, strlen(mess));
    bool abierto = shmem->abierto;
    if(abierto){
        sprintf(mess, "Museo Abierto - puerta %d \n", this->nroPuerta);
        write(STDOUT_FILENO,mess, strlen(mess));
        while(shmem->personasAdentro == shmem->maxPersonas){
            sprintf(mess, "Museo LLeno. La persona %d espera. \n", idPersona);
            write(STDOUT_FILENO,mess, strlen(mess));
            mutex->v();
            semCapacidad->p();
            mutex->p();
        }
        sprintf(mess, "La persona %d entra por la puerta %d \n", idPersona, this->nroPuerta);
        write(STDOUT_FILENO,mess, strlen(mess));
        Mensaje m;
        m.dest =idPersona;
        m.entra = true;
        if(msgsnd(colaRespuesta,&m,sizeof(Mensaje) - sizeof(long),0) == -1){
            perror("Error en envio en la cola de Respuestas");
            exit(1);
        }

        shmem->personasAdentro++;
        sprintf(mess, "Hay %d personas \n", shmem->personasAdentro);
        write(STDOUT_FILENO,mess, strlen(mess));
        mutex->v();
        return true;

    }else{
        sprintf(mess, "Museo Cerrado, no se puede entrar", this->nroPuerta);
        write(STDOUT_FILENO,mess, strlen(mess));
        Mensaje m;
        m.dest =idPersona;
        m.entra = false;
        mutex->v();
        if(msgsnd(colaRespuesta,&m,sizeof(Mensaje) - sizeof(long),0) == -1){
            perror("Error en envio en la cola de Respuestas");
            exit(1);
        }
    }
    return false;
}

bool Puerta::sacarPersona(int idPersona){
    char mess[100];
    Lock l(mutex);
    sprintf(mess, "Paso el semaforo la puerta %d \n", this->nroPuerta);
    write(STDOUT_FILENO,mess, strlen(mess));
    sprintf(mess, "La persona sale por la puerta %d \n", this->nroPuerta);
    write(STDOUT_FILENO,mess, strlen(mess));
    Mensaje m;
    m.dest =idPersona;
    m.entra = true;
    mutex->v();
    if(msgsnd(colaRespuesta,&m,sizeof(Mensaje) - sizeof(long),0) == -1){
        perror("Error en envio en la cola de Respuestas");
        exit(1);
    }
    shmem->personasAdentro--;
    sprintf(mess, "Hay %d personas \n", shmem->personasAdentro);
    write(STDOUT_FILENO,mess, strlen(mess));
    if(shmem->personasAdentro == shmem->maxPersonas -1){
        semCapacidad->v();
    }
    return false;
}

void Puerta::getIPC(){
    char mess[100];
    sprintf(mess, "Obtenido el semaforo por la puerta %d \n", this->nroPuerta);
    write(STDOUT_FILENO,mess, strlen(mess));
    this->mutex = new SemaforoBinario(MUTEX);
    this->semCapacidad = new SemaforoBinario(SEMCAP);

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

    key_t claveMsg = ftok(DIRECTORIO,MSGENT);
    if((colaEntrada = msgget(claveMsg,0660)) == -1){
        perror("Lanzador: Error al crear la cola de mensajes");
    }
    sprintf(mess, "Obtenida la cola de mensajes de entrada por la puerta %d \n", this->nroPuerta);
    write(STDOUT_FILENO,mess, strlen(mess));

    key_t claveMsg2 = ftok(DIRECTORIO,MSGRESP);
    if((colaRespuesta = msgget(claveMsg2,0660)) == -1){
        perror("Lanzador: Error al crear la cola de mensajes");
    }
    sprintf(mess, "Obtenida la cola de mensajes de respuestas por la puerta %d \n", this->nroPuerta);
    write(STDOUT_FILENO,mess, strlen(mess));

}

Mensaje Puerta::recibirPersona(){
    char* mess;
    Mensaje msg;
    if(msgrcv(colaEntrada,(Mensaje*)&msg,sizeof(Mensaje) - sizeof(long),0,0)==-1){
        if(errno == EINVAL || errno == EIDRM){
            sprintf(mess, "TERMINA la puerta  %d)",nroPuerta);
            write(STDOUT_FILENO,mess, strlen(mess));
            exit(0);
        }else{
            perror("Error en la recepcion del mensaje");
            exit(1);
        }
    }
    sprintf(mess, "Recibido mensaje de la persona %d, quiere entrar? %d",msg.idPersona,msg.idPersona);
    write(STDOUT_FILENO,mess, strlen(mess));
    return msg;
}

void Puerta::run(){
    getIPC();
    Mensaje m;
    while(true){
        m = recibirPersona();
        if (m.entra){
            ponerPersona(m.idPersona);
        }else{
            sacarPersona(m.idPersona);
        }
    }
}

