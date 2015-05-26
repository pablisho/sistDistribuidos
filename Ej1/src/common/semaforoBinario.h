#ifndef SEMAFOROBINARIO_H_INCLUDED
#define SEMAFOROBINARIO_H_INCLUDED

#define DIRECTORIO "/home/pablo/distribuidos/Ej1"

class SemaforoBinario {
    public:
        SemaforoBinario(int identificador, int initVal);
        SemaforoBinario(int identificador);
        ~SemaforoBinario();
        void eliminar();
        int p();
        int v();

    private:
        int id;
};

#endif // SEMAFOROBINARIO_H_INCLUDED
