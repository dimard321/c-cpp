#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]){
    cout <<endl<< "I'm the child:"<<getpid()<< endl;
    cout<<"Args from parent: ";
    for (int i = 0; i < argc; i++) {
        cout << argv[i];
        if (i != argc-1) cout << ", ";
        sleep (1);
    }
    cout<<endl;
    cout << "Parent's  pid: "<< getppid()<< endl;
    cout<<endl;
    exit(125);
}
