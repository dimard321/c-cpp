#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;
#define ERROR_CREATE_THREAD -1
#define ERROR_JOIN_THREAD -2

struct my_buf{
	long mtype=1;
 	char mtext[256];
 	int flag;
};

int msqid;
struct msqid_ds *msgBuf;

void *function(void*args){
	cout<<"The thread start working"<<endl;
	char buff[256];
	int *ret;
	ret = new int;
	*ret =25;
	int i=0;
	struct my_buf *msgp= (my_buf*) args;
	int *fl=&(msgp->flag);
	while(*fl==0){
		sprintf(buff,"%s%d","some message:",i);
		strcpy(msgp->mtext,buff);
        if(msgsnd(msqid,msgp,sizeof(msgp->mtext),IPC_NOWAIT)!= 0){
            perror("Error msgsnd: ");
        }
        else{
            cout<<"Message sent: "<<msgp->mtext<<flush<<endl;
        }
		i++;
		sleep(1);
	}
	pthread_exit(ret);
}


int main(){
	pthread_t id;
	int check;
	int *code;
	struct my_buf msgp;
	msgp.flag=0;
	msqid=msgget((key_t)1, IPC_CREAT|0644);
	if(msqid== -1){
		perror("Error msgget: ");
	}
    cout<<"Waiting for reading program or exit"<<endl;
	if((check=(pthread_create(&id,NULL,function,(void*)&msgp)))!=0){
			cout<<"can't create id, error = "  << check;
			exit(ERROR_CREATE_THREAD);
			}
	cout<< "Press 'Enter' to stop it: "<<endl;
	getchar();	
	cout<<endl;
	msgp.flag=1;
	if((check=(pthread_join(id,(void**)&code)))!=0){
	 		cout<<"can't join id, status = " << check;
	        exit(ERROR_JOIN_THREAD);
	}
	cout<<"The thread stoped working, return value is "<< *code<<endl;
	delete code;
	cout<<"Delete ret was succesfull"<<endl; 
	msgctl(msqid, IPC_RMID,msgBuf);
	cout<<"Programm was completed succesfully"<<endl;
	return 0;
}