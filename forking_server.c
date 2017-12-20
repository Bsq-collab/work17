#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  int from_client;
  int ppid;
  ppid=getpid();
  while(1){
    from_client=server_setup();
    if(getpid()!= ppid){//not parent pid.
      subserver(from_client);//calls subserver because it's not the parent...
    }
  }
}

void subserver(int from_client) {
  int to_client;
  char buffer[BUFFER_SIZE];
  to_client=server_connect(from_client);//after connecting
  while(read(from_client,buffer,sizeof(buffer))){//read til false
    printf("[received] %s \n", buffer);
    process(buffer);//add a 0 to first index
    write(to_client,buffer,sizeof(buffer));//writes back to client
    printf("write to client");
  }
}

void process(char * s) {
  s[0]='0';
}
