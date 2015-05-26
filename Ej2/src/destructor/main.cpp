#include <iostream>
#include "../common/semaforoBinario.h"
#include "../common/museo.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>


#define DIRECTORIO "/home/pablo/distribuidos/Ej1"
#define MUTEX 200
#define SHM 201
#define MSGENT 202
#define MSGRESP 203
#define SEMCAP 204

using namespace std;

int main()
{
    int shmid;

    SemaforoBinario* mutex = new SemaforoBinario(MUTEX);
    SemaforoBinario* semCapacidad = new SemaforoBinario(SEMCAP);

    key_t claveMsg = ftok(DIRECTORIO,MSGENT);
    key_t claveMsg2 = ftok(DIRECTORIO,MSGRESP);
    int colaEntrada = msgget(claveMsg,0660);
    int colaRespuesta = msgget(claveMsg2,0660);;
    key_t claveShm = ftok(DIRECTORIO,SHM);
    shmid = shmget(claveShm,sizeof(Museo),0660);

    shmctl(shmid,IPC_RMID,(struct shmid_ds*)0);
    mutex->eliminar();
    semCapacidad->eliminar();
    msgctl(colaEntrada, IPC_RMID,NULL);
    msgctl(colaRespuesta, IPC_RMID,NULL);
}
