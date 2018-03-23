#include    <stdio.h>
#include    <sys/types.h>
#include    <sys/ipc.h>
#include    <sys/sem.h>
#include    <sys/shm.h>
#include    <stdlib.h>
#include    <unistd.h>
#include 	<time.h>
#include 	<sys/wait.h>
#include 	"keys.h"
#include 	"fabryka.h"


	int N; //elementy y
	int M; //elementy z
	int P; //elemetny yz
	int R,S,T; //czas pracy 1-x dla Y,Z,YZ
	int Yproduced, Zproduced, Yconsumed, Zconsumed;
	pid_t pid, parent_pid;

	int Yshmid,Ybin_sem_id, Yfill_id,Yempty_id,Ysem_counter_id;
	int Zshmid,Zbin_sem_id, Zfill_id,Zempty_id,Zsem_counter_id;
	int YZshmid,  YZbin_sem_id,YZsem_counter_id;
	int *Ybufor, *Zbufor, *YZbufor;




int main()
{
	printf("Wpisz liczbę procesów Y, Z, YZ, ");
	scanf("%d %d %d", &M, &N, &P);
	printf("Wpisz czas pracy o 1-x dla procesów Y, Z, YZ ");
	scanf("%d %d %d", &R, &S, &T);


	if ((Yshmid=shmget(0, 6*(sizeof(int)),IPC_CREAT | 0666))<0)
	{
		perror("Yshget");
		exit(1);
	}
	Ybufor = shmat(Yshmid, 0, 0);
	Ybufor[0]=0;
	if ((Zshmid=shmget(0, 6*(sizeof(int)),IPC_CREAT | 0666))<0)
	{
		perror("Zshget");
		exit(1);
	}
	Zbufor = shmat(Zshmid, 0, 0);
	Zbufor[0]=0;
	if ((YZshmid=shmget(0, 11*(sizeof(int)),IPC_CREAT | 0666))<0)
	{
		perror("YZshget");
		exit(1);
	}
	YZbufor = shmat(YZshmid, 0, 0);
	YZbufor[0]=0;

	if((Ybin_sem_id=allocate_sem(Ybin_sem, IPC_CREAT |0666))<0) exit(1);
	init_sem(Ybin_sem_id, 1);
	if((Yfill_id=allocate_sem(Yfill, IPC_CREAT |0666))<0) exit(1);
	init_sem(Yfill_id, 0);
	if((Yempty_id=allocate_sem(Yempty, IPC_CREAT |0666))<0) exit(1);
	init_sem(Yempty_id, 5);
	if((Ysem_counter_id=allocate_sem(Ycount, IPC_CREAT |0666))<0) exit(1);
	init_sem(Ysem_counter_id, 10);

	if((Zbin_sem_id=allocate_sem(Zbin_sem, IPC_CREAT |0666))<0) exit(1);
	init_sem(Zbin_sem_id, 1);
	if((Zfill_id=allocate_sem(Zfill, IPC_CREAT |0666))<0) exit(1);
	init_sem(Zfill_id, 0);
	if((Zempty_id=allocate_sem(Zempty, IPC_CREAT |0666))<0) exit(1);
	init_sem(Zempty_id, 5);
	if((Zsem_counter_id=allocate_sem(Zcount, IPC_CREAT |0666))<0) exit(1);
	init_sem(Zsem_counter_id, 10);

	if((YZbin_sem_id=allocate_sem(YZbin_sem, IPC_CREAT |0666))<0) exit(1);
	init_sem(YZbin_sem_id, 1);
	if((YZsem_counter_id=allocate_sem(YZcount, IPC_CREAT |0666))<0) exit(1);
	init_sem(YZsem_counter_id, 10);

	parent_pid = getpid();

	if((pid=fork())==0)
	{
		forking(M -1);
		Yproduce();
	}else if((pid=fork())==0)
	{
		forking(N -1);
		Zproduce();
	}else if((pid=fork())==0)
	{
		forking(P-1);
		YZconsume();
	}

	if(parent_pid==getpid())
	{
		for(int i = 0; i<(M+N+P);++i)
			wait(NULL);
		shmdt(Ybufor);
		shmdt(Zbufor);
		shmdt(YZbufor);
		shmctl(Yshmid,IPC_RMID, 0);
		shmctl(Zshmid,IPC_RMID, 0);
		shmctl(YZshmid,IPC_RMID, 0);

		deallocate_sem(Ysem_counter_id);
		deallocate_sem(Ybin_sem_id);
		deallocate_sem(Yempty_id);
		deallocate_sem(Yfill_id);

		deallocate_sem(Zsem_counter_id);
		deallocate_sem(Zbin_sem_id);
		deallocate_sem(Zempty_id);
		deallocate_sem(Zfill_id);

		deallocate_sem(YZsem_counter_id);
		deallocate_sem(YZbin_sem_id);

	}
	return 0;



}

void forking(int n)
{
	int i;
	pid_t pid;
	for (i = 0; i < n; ++i)
	{
		pid = fork();
		if (pid == 0) return;
	}
}



void Yproduce()
{
	int item=0;
	time_t tt;
	srand(time(&tt));

	while(sem_counter(Ysem_counter_id))
	{	sleep(rand()%R+1);
		sem_down(Yempty_id);
		sem_down(Ybin_sem_id);
		queue_push(Ybufor,item);
        printf("Produced %d on Y by %d \n",item,getpid());

        sem_up(Ybin_sem_id);
		sem_up(Yfill_id);
        item = (item+1)%10;
	}

}

void Zproduce()
{
	int item=0;
	time_t tt;
	srand(time(&tt));
	while(sem_counter(Zsem_counter_id))
	{
		sleep(rand()%S+1);
		sem_down(Zempty_id);
		sem_down(Zbin_sem_id);
		queue_push(Zbufor,item);
        printf("Produced %d on Z by %d \n",item,getpid());
		item+=1;
		sem_up(Zbin_sem_id);
		sem_up(Zfill_id);
	}


}

void YZconsume()
{
	int item;
	time_t tt;
	srand(time(&tt));
	while (sem_counter(YZsem_counter_id)) {
		sleep(rand()%T+1);
		sem_down(Yfill_id);
		sem_down(Zfill_id);
		sem_down(Ybin_sem_id);
		sem_down(Zbin_sem_id);
        item = 10*queue_pop(Ybufor)+queue_pop(Zbufor);
        printf("Final prouct:%d by %d \n",item, getpid());
		sem_up(Zbin_sem_id);
		sem_up(Ybin_sem_id);
		sem_up(Yempty_id);
		sem_up(Zempty_id);



	}
}

void queue_push(int *queue, int item)
{
    queue[queue[0] + 1] = item;
    ++queue[0];


}

int queue_pop(int *queue)
{
    int i;
    int ret = queue[1];
    for(i=1; i<queue[0]; ++i) {
        queue[i] = queue[i+1];
    }
    --queue[0];
    return ret;

}
int  allocate_sem(key_t key, int sem_flags)
{
    return semget(key, 1, sem_flags);
}

int deallocate_sem(int semid)
{
    union semun arg;
    return semctl(semid,1, IPC_RMID, arg);
}

int init_sem(int semid, int value)
{
    union semun arg;
    arg.val = value;
    return semctl(semid, 0, SETVAL, arg);
}

int sem_down(int semid)
{
    struct sembuf sem = { 0, -1, 0 };
    return semop(semid, &sem, 1);


}

int sem_up(int semid)
{
    struct sembuf sem = { 0, 1, 0 };
    return semop(semid, &sem, 1);
}

int sem_counter(int semid)
{
    struct sembuf sem = { 0, -1, IPC_NOWAIT };
    if( semop(semid, &sem, 1)<0) return 0;
    return 1;
}


