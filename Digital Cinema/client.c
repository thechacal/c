/*
Protótipo client que envia um arquivo ao protótipo servidor. ( FEITO )
Fazer a transferencia com criptografia SSL onde o conteúdo do arquivo a ser enviado está criptografado com AES. ( TO DO )

Desenvolvido por:

Edluise Costa a.k.a ThEcHaCaL
Iuri Diniz a.k.a CLX
Caio Vilar a.k.a Hellscoffe

Seguranca em Cinema Digital 4k3D
ECT/UFRN
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <malloc.h>
#include <resolv.h>
#include "../mylibs/sync.h" // https://github.com/thechacal/c/tree/master/mylibs

#define MYPORT 20000
#define FAIL    -1
#define HOSTNAME    "IP-SERVER-HOST"

int main(int argc, char *argv[]){

  int mysocket;
  struct hostent *he;
  struct sockaddr_in zion;

  if(argc != 2){
    fprintf(stderr,"Uso: ./client <arquivo a ser transmitido>\n");
    push();
    exit(1);
  }
  if((he=gethostbyname(HOSTNAME )) == NULL){
    Perror("gethostbyname");
    exit(1);
  }
  if((mysocket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    perror("socket");
    exit(1);
  }
  zion.sin_family = AF_INET;
  zion.sin_port = htons(MYPORT);
  zion.sin_addr = *((struct in_addr *)he->h_addr_list[0]);
  bzero(&(zion.sin_zero), 8);
  if(connect(mysocket,(struct sockaddr *)&zion, sizeof(struct sockaddr)) ==-1){
    perror("connect");
    exit(1);
  }else{
    printf("Conectado a [%s].\n",inet_ntoa(zion.sin_addr));
  }
  upload(mysocket,argv[1]);
  printf("Fechando a conexao.\n\n");
  close(mysocket);
  push();

  return 0;
}
