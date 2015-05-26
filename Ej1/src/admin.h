#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#define DIRECTORIO "/home/pablo/distribuidos/Ej1"
#define MUTEX 200
#define SHM 201

#include "./common/semaforoBinario.h"
#include "./common/museo.h"

class Admin{
    private:

        //IPCs
        int shmid;
        Museo* shmem;

        SemaforoBinario* mutex;

        void getIPC();
    public:
        Admin();
        virtual ~Admin();
        void abrirMuseo();
        void cerrarMuseo();


};

#endif // ADMIN_H_INCLUDED
