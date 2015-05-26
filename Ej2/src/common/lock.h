#ifndef LOCK_INCLUDED
#define LOCK_INCLUDED

#include "semaforoBinario.h"

class Lock{
    private:
        SemaforoBinario* sem;
    public:
        Lock(SemaforoBinario* sem);
        virtual ~Lock();
};

#endif // LOCK_INCLUDED
