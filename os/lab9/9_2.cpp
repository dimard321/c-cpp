#include <iostream>
#include <sys/types.h>         
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sys/stat.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>



using namespace std;
#define ERROR_CREATE_THREAD -1
#define ERROR_JOIN_THREAD -2
#define PORT1 7000
#define PORT2 8000

struct sockaddr_in bindaddr;  
struct sockaddr_in saddr; 
socklen_t addrlen;
int my_socket;
pthread_mutex_t mut;
pthread_mutex_t mutQW;


void* f_reception(void*fl){
	cout<<"The thread (f_reception) start working"<<endl;
	char buf[256];
	int count=0;
	addrlen=sizeof(saddr);
	while(*((int*)fl)==0){
		sleep(1);
		memset(buf,0,sizeof(buf));
		int size = sprintf(buf, "Give me info about OS name, iteration: %d", count);
		int sentcount = sendto(my_socket,buf,size,0,(struct sockaddr*)&saddr,addrlen);
		if (sentcount == -1) {
			perror("send error: ");
		}
		count++;
	}
	int *ret1;
	ret1 = new int;
	*ret1 =25;
	pthread_exit(ret1);
}


void * f_br_question(void*fl){
	cout<<"The thread (f_br_question) start working"<<endl;
	char buf[256];
	addrlen=sizeof(saddr);
	while(*((int*)fl)==0){
		memset(buf,0,sizeof(buf));
		int recvcount = recvfrom(my_socket,buf,sizeof(buf),0,(struct sockaddr*)&saddr,&addrlen);
		if (recvcount == -1) {
			perror("recv error");
			sleep(1);
		}
		else{
			cout << "Information from server (with iteration): OS name:  " << buf <<flush<<endl;
			sleep(1);
		}
	}
	int *ret2;
	ret2 = new int;
	*ret2 =50;
	pthread_exit(ret2);
}	

int main(){
	pthread_t id_reception, id_process, id_br_question;
	int check;
	int *code[2];
	int fl_re=0; 
	int fl_br_question=0;  
	my_socket = socket(AF_INET,SOCK_DGRAM,0);
	fcntl(my_socket,F_SETFL,O_NONBLOCK);
	cout<<"client socket: "<<my_socket<<endl;
	int optval = 1;
	setsockopt(my_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	bindaddr.sin_family = AF_INET;
	bindaddr.sin_port = htons(PORT1);
	bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(my_socket,(struct sockaddr*)&bindaddr,sizeof(bindaddr));
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT2);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if((check=(pthread_create(&id_reception,NULL,f_reception,(void*)&fl_re)))!=0){
			cout<<"can't create thread (f_reception), error = "  << check;
			exit(ERROR_CREATE_THREAD);
			}
	if((check=(pthread_create(&id_br_question,NULL,f_br_question,(void*)&fl_br_question)))!=0){
			cout<<"can't create thread (f_br_question), error = "  << check;
			exit(ERROR_CREATE_THREAD);
			}
	cout << "press 'Enter' to stop the program:..." << endl;
	getchar();
	cout<<endl;
	fl_re=1;
	fl_br_question=1;
	if((check=(pthread_join(id_reception,(void**)&code[0])))!=0){
	 		cout<<"can't join id_reception, status = " << check;
	        exit(ERROR_JOIN_THREAD);
	}
	cout<<"The thread (f_reception) stoped working, return value is "<< *code[0]<<endl;
	if((check=(pthread_join(id_br_question,(void**)&code[1])))!=0){
	 		cout<<"can't join id_br_question, status = " << check;
	        exit(ERROR_JOIN_THREAD);
	}
	cout<<"The thread (f_br_question) stoped working, return value is "<< *code[1]<<endl;
	delete code[0];
	cout<<"Delete ret1 was succesfull"<<endl; 
	delete code[1];
	cout<<"Delete ret2 was succesfull"<<endl; 
	close(my_socket);
	cout<<"Programm was completed succesfully"<<endl;
	return 0;
}