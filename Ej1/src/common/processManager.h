#ifndef PROCESSMANAGER_H_INCLUDED
#define PROCESSMANAGER_H_INCLUDED

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

class ProcessManager {
private:
	ProcessManager();
public:
	pid_t static run(const char* path, char* const argv[]);
	void static wait();
	virtual ~ProcessManager();
};


#endif // PROCESSMANAGER_H_INCLUDED
