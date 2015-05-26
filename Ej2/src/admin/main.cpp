#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"

using namespace std;

int main(int args, char* argv[]){

    Admin a;


    int abrir = atoi(argv[1]);
    if(abrir){
        a.abrirMuseo();
    }else{
        a.cerrarMuseo();
    }
    return 0;
}
