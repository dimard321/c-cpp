#include <iostream>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <semaphore.h>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


using namespace std;
#define ERROR_CREATE_THREAD -1
#define ERROR_JOIN_THREAD -2

sem_t * sem= new sem_t;
ofstream file;

void *func(void *flag){
	cout<<"The thread start working"<<endl;
	int *ret;
	ret = new int;
	*ret =25;
	char symbol = '2';
	while(*((int*)flag)==0){
		sem_wait(sem);
		for(int i=0;i<5;i++){
			file<<symbol<<flush;
			sleep(1);
		}
		sem_post(sem);
		sleep(2);
	cout<<"Wrote 5 '2'"<<endl;	
	}
	pthread_exit(ret);
}

int main(){
	cout<<"Start the main programm"<<endl;
	file.open("info.txt", ios::app);
	if (file.is_open()){
		int flag=0;
		const char *name = "semaphore";
		sem=sem_open(name,O_CREAT,0644,1);
		pthread_t id;
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
		if((check=(pthread_join(id,(void**)&code)))!=0)
			{
	 		cout<<"can't join id, status = " << check;
	        exit(ERROR_JOIN_THREAD);
			}
		cout<<"The thread stoped working, return value is "<< *code<<endl;
		file.close();
		sem_close(sem);
		sem_unlink(name);
		delete code;
		cout<<"Delete ret was succesfull"<<endl; 
	}
	cout << "The program completed successfully"<<endl;
	return 0;
}