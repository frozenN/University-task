/*Compilar - gcc clienteudp.c -o clienteudp
  Executar - ./clienteudp 127.0.0.1 mensagem
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <sys/time.h> /* select() */

#define REMOTE_SERVER_PORT 1500
#define MAX_MSG 100

int sd, rc, i;
struct sockaddr_in cliAddr, remoteServAddr;
struct hostent *h;
char nomearq[10], myfile[10101], texto;
int strpos = 0;

void ssend(int argc, char *argv[]){

    if(argc<3) {
      printf("usage : %s <server> <data1> ... <dataN> \n", argv[0]);
      exit(1);
    }

    h = gethostbyname(argv[1]);
    if(h==NULL) {
      printf("%s: unknown host '%s' \n", argv[0], argv[1]);
      exit(1);
    }

    printf("%s: sending data to '%s' (IP : %s) \n", argv[0], h->h_name,
     inet_ntoa(*(struct in_addr *)h->h_addr_list[0]));


    remoteServAddr.sin_family = h->h_addrtype;
    memcpy((char *) &remoteServAddr.sin_addr.s_addr,
  	 h->h_addr_list[0], h->h_length);
    remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);

    sd = socket(AF_INET,SOCK_DGRAM,0);
    if(sd<0) {
      printf("%s: cannot open socket \n",argv[0]);
      exit(1);
    }

    cliAddr.sin_family = AF_INET;
    cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    cliAddr.sin_port = htons(0);

    rc = bind(sd, (struct sockaddr *) &cliAddr, sizeof(cliAddr));
    if(rc<0) {
      printf("%s: cannot bind port\n", argv[0]);
      exit(1);
    }
    rc = sendto(sd, myfile, strlen(myfile)+1, 0,
    	    (struct sockaddr *) &remoteServAddr,
    		    sizeof(remoteServAddr));

    if(rc<0) {
          printf("%s: cannot send data %d \n",argv[0],i-1);
          close(sd);
          exit(1);
        }

}

void rread(char *argv[])
{
  memcpy(nomearq, argv[2], sizeof(nomearq));
  FILE* arq;
  arq = fopen(nomearq,"rt");
  if(arq == NULL)
  {
    printf("Nao e possivel abrir o arquivo\n");
    exit(1);
  }
  while((fscanf(arq,"%c", &texto)) != EOF)
  {
    myfile[strpos] = texto;
    strpos++;
  }
  fclose(arq);
}

void receiveConfirm(char *argv[])
{
  while(1) {
    char msg[MAX_MSG];
    memset(msg,0x0,MAX_MSG);
    int cliLen = sizeof(cliAddr);
    int n = recvfrom(sd, msg, MAX_MSG, 0,
		 (struct sockaddr *) &cliAddr, &cliLen);
    if(n<0) {
      printf("%s: cannot receive data \n",argv[0]);
      continue;
    }
    printf("%s: from %s:UDP%u : %s \n",
	   argv[0],inet_ntoa(cliAddr.sin_addr),
	   ntohs(cliAddr.sin_port),msg);
     break;
   }
}

int main(int argc, char *argv[]) {
  rread(argv);
  ssend(argc, argv);
  receiveConfirm(argv);
  return 1;
}
