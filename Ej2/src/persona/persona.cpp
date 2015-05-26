#include "persona.h"
#include "../common/mensaje.h"


#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <errno.h>

Persona::Persona(int id, int tiempoMedio, int cantPuertas){
    this->id =id;
    this->tiempo = tiempoMedio;
    this->cantPuertas =cantPuertas;
    srand(time(NULL)+id);
}

Persona::~Persona(){
}

void Persona::getIPC(){
    char msg[200];

    key_t claveMsg = ftok(DIRECTORIO,MSGENT);
    if((colaEntrada = msgget(claveMsg,0660)) == -1){
        perror("Lanzador: Error al crear la cola de mensajes");
    }
    sprintf(msg,"Obtenida la Cola de mensajes de entrada por la persona %d\n",id);
    write(STDOUT_FILENO,msg, strlen(msg));

    key_t claveMsg2 = ftok(DIRECTORIO,MSGRESP);
    if((colaRespuesta = msgget(claveMsg2,0660)) == -1){
        perror("Lanzador: Error al crear la cola de mensajes");
    }
    sprintf(msg, "Obtenida la cola de mensajes de respuestas por la persona %d \n", id);
    write(STDOUT_FILENO,msg, strlen(msg));
}

void Persona::run(){
    getIPC();
    bool entra  = entrar();
    if(entra){
        esperar();
        salir();
    }
}

bool Persona::entrar(){
    char msg[200];
    Mensaje m;
    int dest = rand() % this->cantPuertas +1;
    m.dest = dest;
    m.entra = true;
    m.idPersona = this->id;
    sprintf(msg, "La persona %d intenta entrar por la puerta %d \n",id,dest);
    write(STDOUT_FILENO,msg, strlen(msg));
    if(msgsnd(colaEntrada,&m,sizeof(Mensaje) - sizeof(long),0) == -1){
        perror("Error en envio en la cola de Entrada");
        exit(1);
    }
    sprintf(msg, "Mensaje enviado por la persona  %d, esperando resp... \n",id);
    write(STDOUT_FILENO,msg, strlen(msg));
    if(msgrcv(colaRespuesta,(Mensaje*)&m,sizeof(Mensaje) - sizeof(long),0,id)==-1){
        if(errno == EINVAL || errno == EIDRM){
            sprintf(msg, "TERMINA la puerta  %d",id);
            write(STDOUT_FILENO,msg, strlen(msg));
            exit(0);
        }else{
            perror("Error en la recepcion del mensaje");
            exit(1);
        }
    }
    return m.entra;
}

void Persona::esperar(){
    int time = rand() % this->tiempo;
    usleep(time);
    char msg[100];
    sprintf(msg, "La persona %d pasa adentro del museo %d usecs",id,time);
}

void Persona::salir(){
    char msg[200];
    Mensaje m;
    int dest = rand() % this->cantPuertas;
    m.dest = dest;
    m.entra =false;
    m.idPersona = this->id;
    sprintf(msg, "La persona %d intenta salir por la puerta %d",id,dest);
    if(msgsnd(colaEntrada,&m,sizeof(Mensaje) - sizeof(long),0) == -1){
        perror("Error en envio en la cola de Entrada");
        exit(1);
    }

    if(msgrcv(colaRespuesta,(Mensaje*)&m,sizeof(Mensaje) - sizeof(long),0,id)==-1){
        if(errno == EINVAL || errno == EIDRM){
            sprintf(msg, "TERMINA la persona  %d)",id);
            write(STDOUT_FILENO,msg, strlen(msg));
            exit(0);
        }else{
            perror("Error en la recepcion del mensaje");
            exit(1);
        }
    }
    sprintf(msg, "Salio la persona %d por la pierta  %d)",id,dest);
    write(STDOUT_FILENO,msg, strlen(msg));
}
