#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

using namespace std;
#define ERROR_CREATE_THREAD -1
#define ERROR_JOIN_THREAD -2

int fd[2];


void *f1(void *fl1){
cout<<"The first thread started working"<<endl;
int *ret1;
ret1 = new int;
*ret1 =10;


char buff[100];
int i=0;
int l=0;

while (*((int*)fl1)==0){
	l = sprintf(buff,"%s %d","some message:",i);
	write(fd[1], buff, l);
	i++;
	sleep(1);
}
pthread_exit(ret1);
}


void *f2(void *fl2){
cout<<"The second thread started working"<<endl;
int *ret2;
ret2=new int;
*ret2=20;


char buff[100];
int rc=0;

while (*((int*)fl2)==0){
	memset(buff,0,100);
	rc = read(fd[0], buff, 100);
	if (rc > 0){
		cout << buff<<flush<<endl;
		sleep(1);
	}
	else{
		perror("ERROR");
		sleep(1);

	}
}
pthread_exit(ret2);
}

int main()
{
	cout<< "Start"<<endl;
	int fl1 = 0;
	int fl2 = 0;
	pthread_t id1, id2;
	int check;
	int *code[2];
	//pipe2(fd, O_NONBLOCK);
	pipe(fd);
	int S1 = fcntl(fd[0],F_GETFL);
	int S2 = fcntl(fd[1],F_GETFL);
	fcntl(fd[0], F_SETFL, S1|O_NONBLOCK);
	fcntl(fd[1], F_SETFL, S2|O_NONBLOCK);
	if((check=(pthread_create(&id1,NULL,f1, &fl1)))!=0)
		{
		cout<<"can't create id1, error = "  << check;
		exit(ERROR_CREATE_THREAD);
		}
	
	if((check=(pthread_create(&id2,NULL,f2, &fl2)))!=0)
		{
		cout<<"can't create id2, error = "  << check;
		exit(ERROR_CREATE_THREAD);
		}
	cout<< "Press Enter to stop it: "<<endl;
	getchar();
	cout<<endl;
	fl1 = 1;
	fl2 = 1;
	if((check=(pthread_join(id1,(void**)&code[0])))!=0)
		{
 		cout<<"main error: can't join id1, status = " << check;
        	exit(ERROR_JOIN_THREAD);
		}

	if((check=(pthread_join(id2,(void**)&code[1])))!=0)
		{
 		cout<<"main error: can't join id2, status = " << check;
        	exit(ERROR_JOIN_THREAD);
		}
	cout<<endl;
	cout<<"The first thread stoped working, return value is "<< *code[0] <<endl;
	cout<<"The second thread stoped working, return value is "<< *code[1] <<endl;
	
	close(fd[0]);
	close(fd[1]);

	delete code[0];
	cout<<"Delete ret1 was succesfull"<<endl;
	delete code[1];
	cout<<"Delete ret2 was succesfull"<<endl; 
	cout << "The program completed successfully"<<endl;
	return 0;
}

