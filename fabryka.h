#include <sys/types.h>

union semun {
    int val;
    struct semid_ds *buf;
    ushort* array;
};

int allocate_sem(key_t, int);

int deallocate_sem(int);

int init_sem(int, int);

int sem_down(int);

int sem_up(int);

int sem_counter(int);

void Zproduce();

void Yproduce();

void YZconsume();

void queue_push(int *, int);

int queue_pop(int*);

void forking(int);
