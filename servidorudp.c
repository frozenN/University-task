/*Compilar - gcc servidorudp.c -o servidorudp
  Executar - ./servidorudp
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */
#include <stdlib.h>

#define LOCAL_SERVER_PORT 1500
#define MAX_MSG 100

int sd, rc, n, cliLen;
struct sockaddr_in cliAddr, servAddr;
char msg[MAX_MSG];
FILE *arq;
char nome_arquivo[20];
int i;
char msgzinha[100];

void receive(int argc, char *argv[])
{
  sd=socket(AF_INET, SOCK_DGRAM, 0);
  if(sd<0) {
    printf("%s: cannot open socket \n",argv[0]);
    exit(1);
  }

  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(LOCAL_SERVER_PORT);
  rc = bind (sd, (struct sockaddr *) &servAddr,sizeof(servAddr));
  if(rc<0) {
    printf("%s: cannot bind port number %d \n",
	   argv[0], LOCAL_SERVER_PORT);
    exit(1);
  }

  printf("%s: waiting for data on port UDP %u\n",
	   argv[0],LOCAL_SERVER_PORT);

  while(1) {

    memset(msg,0x0,MAX_MSG);


    cliLen = sizeof(cliAddr);
    n = recvfrom(sd, msg, MAX_MSG, 0,
		 (struct sockaddr *) &cliAddr, &cliLen);

    makefile();

    if(n<0) {
      printf("%s: cannot receive data \n",argv[0]);
      continue;
    }


          memcpy(msgzinha, "Ola cliente, sua mensagem foi recebida", 100);

          rc = sendto(sd, msgzinha, strlen(msgzinha)+1, 0,
            (struct sockaddr *) &cliAddr,sizeof(cliAddr));

          if(rc<0)
          {
               printf("%s: cannot send data %d \n",argv[0],i-1);
               close(sd);
               exit(1);
          }
             break;


   }

}

void makefile()
{
  strcpy(nome_arquivo, "saida.txt");
  arq = fopen(nome_arquivo, "wt");
  if(arq == NULL)
  {
     printf("Nao e possivel iniciar o arquivo\n");
     exit(1);
  }
  fprintf(arq,msg);
  fclose(arq);
}

int main(int argc, char *argv[]) {
    receive(argc, argv);
    return 0;

}
