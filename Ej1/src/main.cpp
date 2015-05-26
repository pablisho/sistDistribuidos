#include "lanzador.h"
#include "admin.h"

#include <iostream>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]){
    Lanzador lanzador(5,10,1000000);
    lanzador.iniciarIPC();
    lanzador.lanzarPuertas();

    bool salir = false;

    Admin a;
    while(!salir){
        char* mess = "Admin: q a c";
        write(STDOUT_FILENO,mess, strlen(mess));
        std::string entrada;
        std::cin >> entrada;
        if(entrada == "q"){
            salir=true;
        }else if(entrada == "a"){
            a.abrirMuseo();
        }else if(entrada == "c"){
            a.cerrarMuseo();
        }
    }

    return 0;
}
