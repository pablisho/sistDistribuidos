/*
 * ProcessManager.cpp
 *
 *  Created on: 14/04/2014
 *      Author: agustin
 */

#include "processManager.h"
#include <iostream>
ProcessManager::ProcessManager() {
}

pid_t ProcessManager::run(const char* path, char* const argv[]){
	pid_t id = fork ();
        if(id<0){
        	std::string mensaje = "No se pudo iniciar el proceso: " + std::string(strerror(errno));
        	std::cout <<  mensaje << std::endl;
        	return id;
        }else if ( id == 0 ) {
			execv(path, argv);
			std::string mensaje = "No se pudo cargar el ejecutable" + std::string(path) + ": " + std::string(strerror(errno));
			std::cout <<  mensaje << std::endl;
			exit(1);
		} else {
			return id;
		}
}

void ProcessManager::wait(){
	::wait(NULL);
}

ProcessManager::~ProcessManager() {
}
