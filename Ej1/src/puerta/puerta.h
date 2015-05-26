#ifndef PUERTA_H_INCLUDED
#define PUERTA_H_INCLUDED

#define DIRECTORIO "/home/pablo/distribuidos/Ej1"
#define MUTEX 200
#define SHM 201

#include "../common/semaforoBinario.h"
#include "../common/museo.h"

class Puerta{
    private:
        // Parametros
        int cantPersonas;
        int mediaTiempo;
        int nroPuerta;
        int logFd;

        //IPCs
        int shmid;
        Museo* shmem;

        SemaforoBinario* mutex;

        void getIPC();
        bool ponerPersona();
        bool sacarPersona();
        void generarPersona();
    public:
        Puerta(int nroPuerta, int cantPersonas, int mediaTiempo);
        virtual ~Puerta();
        void run();

    };

#endif // PUERTA_H_INCLUDED
