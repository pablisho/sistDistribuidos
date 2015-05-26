#ifndef LANZADOR_H_INCLUDED
#define LANZADOR_H_INCLUDED

#define DIRECTORIO "/home/pablo/distribuidos/Ej1"
#define MUTEX 200
#define SHM 201

#include "./common/museo.h"
#include "./common/semaforoBinario.h"

#include <vector>
#include <sys/types.h>

class Lanzador {
    private:
        //Parametros
        int cantPersonas;
        int cantPuertas;
        int tiempoMedia;
        int capMaxima;

        //Procesos
        std::vector<pid_t> puertas;

        //IPC
        int shmid;
        Museo* shmem;

        SemaforoBinario* mutex;

    public:
        Lanzador(int cantPuertas, int cantPersonas,int tiempoMedia);
        virtual ~Lanzador();
        void iniciarIPC();
        void lanzarPuertas();
};

#endif // LANZADOR_H_INCLUDED
