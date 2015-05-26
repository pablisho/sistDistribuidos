#ifndef PERSONA_INCLUDED
#define PERSONA_INCLUDED

#define DIRECTORIO "/home/pablo/distribuidos/Ej1"
#define MUTEX 200
#define SHM 201
#define MSGENT 202
#define MSGRESP 203
#define SEMCAP 204

class Persona{
    private:
    //param
    int id;
    int tiempo;
    int cantPuertas;

    //IPC
    int colaEntrada;
    int colaRespuesta;

    void getIPC();

    bool entrar();
    void esperar();
    void salir();

    public:
        Persona(int id, int tiempoMedio, int cantPuertas);
        virtual ~Persona();
        void run();

};

#endif // PERSONA_INCLUDED
