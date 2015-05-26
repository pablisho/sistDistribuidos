#ifndef LANZADOR_H_INCLUDED
#define LANZADOR_H_INCLUDED

#define DIRECTORIO "/home/pablo/distribuidos/Ej1"
#define MUTEX 200
#define SHM 201
#define MSGENT 202
#define MSGRESP 203
#define SEMCAP 204

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
        int actual;

        //Procesos
        std::vector<pid_t> puertas;

        //IPC
        int shmid;
        Museo* shmem;

        SemaforoBinario* mutex;
        SemaforoBinario* semCapacidad;

        int colaEntrada;
        int colaRespuesta;

    public:
        Lanzador(int cantPuertas, int cantPersonas,int tiempoMedia, int capMaxima);
        virtual ~Lanzador();
        void iniciarIPC();
        void lanzarPuertas();
        void lanzarAdmin();
        void lanzarPersonas(int cant);
        void removeIPC();
};

#endif // LANZADOR_H_INCLUDED
