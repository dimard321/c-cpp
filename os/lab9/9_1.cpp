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
#include <sys/utsname.h>



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
vector <string> q_request; 
vector <string> q_qw;

struct utsname u;



void* f_reception(void*fl){
	cout<<"The thread (f_reception) start working"<<endl;
	char rcvbuf[256];
	addrlen=sizeof(saddr);
	while(*((int*)fl)==0){
		memset(rcvbuf,0,sizeof(rcvbuf));
		int recvcount = recvfrom(my_socket,rcvbuf,sizeof(rcvbuf),0,(struct sockaddr*)&saddr,&addrlen);
		if (recvcount == -1) {
			perror("recv error");
			sleep(1);
		}
		else{
			pthread_mutex_lock(&mut); 
			q_request.push_back(rcvbuf);
			pthread_mutex_unlock(&mut);
		}
	}
	int *ret1;
	ret1 = new int;
	*ret1 =25;
	pthread_exit(ret1);
}

void * f_process(void*fl){
	cout<<"The thread (f_process) start working"<<endl;
	while(*((int*)fl)==0){
		string tmp=" ";
		pthread_mutex_lock(&mut);
		if (!q_request.empty()){
			cout << "Request from client: " << q_request[0] <<flush<<endl; //message from client
			uname(&u);
			q_request.assign(1, u.sysname);
			tmp=q_request[0];
			q_request.erase(q_request.begin()); 
		}
		pthread_mutex_unlock(&mut);
		if(tmp!=" "){
			pthread_mutex_lock(&mutQW);
			q_qw.push_back(tmp);
			pthread_mutex_unlock(&mutQW);
		}	
		sleep(1);
	}
	int *ret3;
	ret3 = new int;
	*ret3 =75;
	pthread_exit(ret3);
}

void * f_br_question(void*fl){
	cout<<"The thread (f_br_question) start working"<<endl;
	char buf[256];
	int count = 0;
	addrlen=sizeof(saddr);
	while(*((int*)fl)==0){
		pthread_mutex_lock(&mutQW);
		if(!q_qw.empty()) {
			int size = sprintf(buf, "%s %d", q_qw[0].c_str(), count);
			q_qw.erase(q_qw.begin());
			pthread_mutex_unlock(&mutQW);
			int sentcount = sendto(my_socket,buf,size,0,(struct sockaddr*)&saddr,addrlen);
			if (sentcount == -1) {
			perror("send error: ");
			}
			sleep(1);
			count++;
		}
		else{
			pthread_mutex_unlock(&mutQW); 
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
	int *code[3];
	int fl_re=0; 
	int fl_process=0; 
	int fl_br_question=0;  
	pthread_mutex_init(&mut, NULL);
	pthread_mutex_init(&mutQW, NULL);
	my_socket = socket(AF_INET,SOCK_DGRAM,0);
	cout<<"server socket: "<<my_socket<<endl;
	fcntl(my_socket,F_SETFL,O_NONBLOCK);
	int optval = 1;
	setsockopt(my_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	bindaddr.sin_family = AF_INET;
	bindaddr.sin_port = htons(PORT2);
	bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(my_socket,(struct sockaddr*)&bindaddr,sizeof(bindaddr));
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT1);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if((check=(pthread_create(&id_reception,NULL,f_reception,(void*)&fl_re)))!=0){
			cout<<"can't create thread (f_reception), error = "  << check;
			exit(ERROR_CREATE_THREAD);
			}
	if((check=(pthread_create(&id_br_question,NULL,f_br_question,(void*)&fl_br_question)))!=0){
			cout<<"can't create thread (f_br_question), error = "  << check;
			exit(ERROR_CREATE_THREAD);
			}
	if((check=(pthread_create(&id_process,NULL,f_process,(void*)&fl_process)))!=0){
			cout<<"can't create thread (f_process), error = "  << check;
			exit(ERROR_CREATE_THREAD);
			}
	cout << "press 'Enter' to stop the program:..." << endl;
	getchar();
	cout<<endl;
	fl_re=1;
	fl_br_question=1;
	fl_process=1;
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
	if((check=(pthread_join(id_process,(void**)&code[2])))!=0){
	 		cout<<"can't join id_process, status = " << check;
	        exit(ERROR_JOIN_THREAD);
	}
	cout<<"The thread (f_process) stoped working, return value is "<< *code[2]<<endl;
	delete code[0];
	cout<<"Delete ret1 was succesfull"<<endl; 
	delete code[1];
	cout<<"Delete ret2 was succesfull"<<endl; 
	delete code[2];
	cout<<"Delete ret2 was succesfull"<<endl; 
	pthread_mutex_destroy(&mut);
	pthread_mutex_destroy(&mutQW);
	close(my_socket);
	cout<<"Programm was completed succesfully"<<endl;
	return 0;
}