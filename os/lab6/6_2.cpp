#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>      
#include <sys/stat.h>  
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctime>

using namespace std;
#define ERROR_CREATE_THREAD -1
#define ERROR_JOIN_THREAD -2

sem_t *wsem = new sem_t;
sem_t *rsem= new sem_t;
void *addr;
struct shared_use_st *ptr;

void *func(void *flag){
	cout<<"The thread start working"<<endl;
	int *ret;
	ret = new int;
	*ret =25;

	while(*((int*)flag)==0){
		sem_wait(wsem);
		cout<<"Value: "<<*(int*)ptr<<flush<<endl;
		sleep(2);
		sem_post(rsem);
		}
	pthread_exit(ret);
}

int main(){
	cout<<"Start the main programm"<<endl;
	srand(time(0));
	int flag=0;
	int proj_id=0;
	pthread_t id;
	int mem_id=shmget((key_t)1234,4096, 0666 | IPC_CREAT);
	if(mem_id == -1){
		exit(EXIT_FAILURE);
	}
	addr=shmat(mem_id,(void*)0,0);
	if(addr ==(void*)-1){
		exit(EXIT_FAILURE);
	}
	ptr= (struct shared_use_st *)addr;
	const char *name_wsem="wr_sem";
	const char *name_rsem="r_sem";
	wsem=sem_open(name_wsem,O_CREAT,S_IRWXU,0);
	if(wsem==SEM_FAILED) exit(-1);
	rsem=sem_open(name_rsem,O_CREAT,S_IRWXU,0);
	if(rsem==SEM_FAILED) exit(-1);

	int check;
	int *code;
	if((check=(pthread_create(&id,NULL,func,&flag)))!=0){
			cout<<"can't create id, error = "  << check;
			exit(ERROR_CREATE_THREAD);
			}
	cout<< "Press 'Enter' to stop it: "<<endl;
	getchar();	
	cout<<endl;
	flag=1;
	if((check=(pthread_join(id,(void**)&code)))!=0){
	 		cout<<"can't join id, status = " << check;
	        exit(ERROR_JOIN_THREAD);
	}
	cout<<"The thread stoped working, return value is "<< *code<<endl;
	delete code;
	cout<<"Delete ret was succesfull"<<endl; 
	sem_close(wsem);
	sem_close(rsem); 
	sem_unlink(name_wsem);
	sem_unlink(name_rsem);
	if(shmdt(addr)==-1){
		exit(EXIT_FAILURE);
	}
	if(shmctl(mem_id,IPC_RMID,0)==-1){
		exit(EXIT_FAILURE);
	}
	return 0;
}