#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

using namespace std;
#define NAME "/tmp/name2"
#define ERROR_CREATE_THREAD -1
#define ERROR_JOIN_THREAD -2
int fd_ch;
pthread_t id2;
void sig_handler(int signo)
{
	printf("get SIGPIPE\n");
}

void* func(void* flag) {
	cout<<"The thread (func) to send a message start working"<<endl;
	char buff[256];
    int i= 0;
    int* ret2;
    ret2 = new int;
    *ret2 = 50;
    while (*((int*)flag)==0) {
        int size = sprintf(buff, "%s%d", "some message ",i);
 		write(fd_ch, buff, size);
        i++;
        sleep(1);
    }
    pthread_exit(ret2);
}

void *function_open(void*flag){
	cout<<"The thread (function_open) start working"<<endl;
	int check;
	while(*((int*)flag)==0){
	    if ((fd_ch = open(NAME, O_WRONLY|O_NONBLOCK)) == -1){
	        perror("Error open: ");
	        sleep(1);
	    }
	    else{
	    	check = pthread_create(&id2, NULL, func, flag);
			if (check != 0){
					cout<<"can't create id2, error = "  << check;
					exit(ERROR_CREATE_THREAD);
				}
			int *ret1;
			ret1 = new int;
			*ret1 =25;
			pthread_exit(ret1);
	    }
	}
	return NULL;
}

int main(){
	int flag=0;
	pthread_t id;
	int check;
	int *code[2];
	signal(SIGPIPE,sig_handler);
	fd_ch=mkfifo(NAME,0644);
	if (fd_ch == -1){
        perror("Error mkfifo: ");
    }
    cout<<"Waiting for reading program or exit"<<endl;

	if((check=(pthread_create(&id,NULL,function_open,&flag)))!=0){
			cout<<"can't create id, error = "  << check;
			exit(ERROR_CREATE_THREAD);
			}
	cout<< "Press 'Enter' to stop it: "<<endl;
	getchar();	
	cout<<endl;
	flag=1;
	if((check=(pthread_join(id,(void**)&code[0])))!=0){
	 		cout<<"can't join id, status = " << check;
	        exit(ERROR_JOIN_THREAD);
	}
	cout<<"The thread (function_open) stoped working, return value is "<< *code[0]<<endl;
	if((check=(pthread_join(id2,(void**)&code[1])))!=0){
	 		cout<<"can't join id2, status = " << check;
	        exit(ERROR_JOIN_THREAD);
	}
	cout<<"The thread (func) stoped working, return value is "<< *code[1]<<endl;
	delete code[0];
	cout<<"Delete ret1 was succesfull"<<endl; 
	delete code[1];
	cout<<"Delete ret2 was succesfull"<<endl; 
	close(fd_ch);
    unlink(NAME);
    cout<<"Programm was completed succesfully"<<endl;
	return 0;
}