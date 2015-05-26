#include "lock.h"

Lock::Lock(SemaforoBinario* sem){
    this->sem = sem;
    sem->p();
}

Lock::~Lock(){
    sem->v();
}
