#include "semaforoBinario.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

SemaforoBinario::SemaforoBinario(int identificador, int initVal){
    key_t clave = ftok(DIRECTORIO,identificador);
    this->id = semget(clave, 1, IPC_CREAT|IPC_EXCL|0660);

    union semnum {
		int val;
		struct semid_ds* buf;
		ushort* array;
	};

	semnum init;
	init.val = initVal;
	int resultado = semctl (this->id,0,SETVAL,init);
	if(resultado ==-1){
        throw "Fallo Inicializacion del Semaforo";
	}

}

SemaforoBinario::SemaforoBinario(int identificador){
     key_t clave = ftok(DIRECTORIO,identificador);
    this->id = semget(clave, 1, 0660);

}

int SemaforoBinario::p(){
    struct sembuf operacion;

	operacion.sem_num = 0;	// numero de semaforo
	operacion.sem_op  = -1;	// restar 1 al semaforo
	operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion,1 );
	if(resultado==-1){
        throw "Fallo el P";
	}
	return resultado;
}

int SemaforoBinario::v(){
    struct sembuf operacion;

	operacion.sem_num = 0;	// numero de semaforo
	operacion.sem_op  = 1;	// sumar 1 al semaforo
	operacion.sem_flg = SEM_UNDO;

	int resultado = semop ( this->id,&operacion,1 );
	if (resultado==-1){
       throw "Fallo el V";
	}
	return resultado;

}

void SemaforoBinario :: eliminar () {
	semctl ( this->id,0,IPC_RMID,(struct semid_ds*)0 );
}

