#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>
#include <string>

using namespace std;

int main(){
cout<<"My pid: "<<getpid()<<endl; 
cout<<"My parent's pid: "<<getppid()<<endl; 
int ch_status;
cout<<endl;
cout<<"FORK"<<endl;
pid_t ch_pid = fork();
if (ch_pid==-1){
	perror("fork failed");
	exit(-1);
}

if (ch_pid != 0){
	cout<<"I'm the parent: "<<getpid()<<";"<<"My child is:"<<ch_pid<<endl; 
	while(wait(&ch_status)==0){
            cout<<"Waiting while the child process will end..."<<endl<<endl; 
            sleep(1);
        }
    cout << "Child exit status: " << WEXITSTATUS(ch_status) << endl ;
}
else if (ch_pid==0){
        cout<<"Type 5 arguments: "<<endl;
        string *args =new string[6];
        const char  *null =args[5].c_str();
        null=NULL;
        for(int i=0;i<5;i++){
            cin>>args[i];
        }
        execl("4_1",args[0].c_str(),args[1].c_str(),args[2].c_str(),args[3].c_str(),args[4].c_str(),null,NULL);
}
  return 0;
}

