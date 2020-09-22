#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
#define NAME "/tmp/name2"
#define ERROR_CREATE_THREAD -1
#define ERROR_JOIN_THREAD -2
int fd_ch;


void *function(void*flag){
	cout<<"The thread start working"<<endl;
	char buff[256];
	int *ret;
	ret = new int;
	*ret =25;
	int i=0;
	while(*((int*)flag)==0){
		memset(buff,0,sizeof(buff));
		ssize_t rc = read(fd_ch, buff, sizeof(buff));
		if (rc == -1){
            perror("Error read: ");
            sleep(1);
        }
        else if(rc>0){
            cout <<"Received message:  "<< buff<<flush<<endl;
            sleep(1);
        }
        else if(rc==0){
        	sleep(1);
        }
	}

	pthread_exit(ret);
}

int main(){
	int flag=0;
	pthread_t id;
	int check;
	int *code;
	fd_ch=mkfifo(NAME,0644);
	if (fd_ch == -1){
        perror("Error mkfifo: ");
    }
    fd_ch = open(NAME, O_RDONLY|O_NONBLOCK);
    if (fd_ch == -1){
        	perror("Error read open: ");
    }
    printf("Waiting for reading program or exit\n");
	if((check=(pthread_create(&id,NULL,function,&flag)))!=0){
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
	close(fd_ch);
    unlink(NAME);
    cout<<"Programm was completed succesfully"<<endl;
	return 0;
}