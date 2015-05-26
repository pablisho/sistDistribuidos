#ifndef PUERTA_H_INCLUDED
#define PUERTA_H_INCLUDED

#define DIRECTORIO "/home/pablo/distribuidos/Ej1"
#define MUTEX 200
#define SHM 201
#define MSGENT 202
#define MSGRESP 203
#define SEMCAP 204

#include "../common/semaforoBinario.h"
#include "../common/museo.h"
#include "../common/mensaje.h"

class Puerta{
    private:
        // Parametros
        int nroPuerta;

        //IPCs
        int shmid;
        Museo* shmem;

        SemaforoBinario* mutex;
        SemaforoBinario* semCapacidad;

        int colaEntrada;
        int colaRespuesta;


        void getIPC();
        bool ponerPersona(int persona);
        bool sacarPersona(int persons);
        Mensaje recibirPersona();
    public:
        Puerta(int nroPuerta);
        virtual ~Puerta();
        void run();

    };

#endif // PUERTA_H_INCLUDED
