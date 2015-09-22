/*
 * Protótipo server que recebe um arquivo do protótipo client. ( FEITO )
 * Fazer a transferencia com criptografia SSL onde o conteúdo do arquivo a ser enviado está criptografado com AES. ( TO DO )
 *
 * Desenvolvido por:
 *
 * Edluise Costa a.k.a ThEcHaCaL
 * Iuri Diniz a.k.a CLX
 * Caio Vilar a.k.a Hellscoffe
 *
 * Seguranca em Cinema Digital 4k3D
 * ECT/UFRN
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <malloc.h>
#include <resolv.h>
#include "../mylibs/sync.h"

#define MYPORT 20000
#define BACKLOG 10 /* Numero maximo de conexoes */
#define FAIL    -1

int main(){

  int mysocket, newsocket;
  int on = 1;

  if((mysocket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    perror("socket");
    exit(1);
  }
  struct sockaddr_in zion;
  struct sockaddr_in neo;
  socklen_t tamanho;
  zion.sin_family = AF_INET;
  zion.sin_port = htons(MYPORT);
  zion.sin_addr.s_addr = INADDR_ANY;
  bzero(&(zion.sin_zero), 8);
  int status = setsockopt(mysocket, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on));
  if(-1 == status)
    perror("setsockopt(...,SO_REUSEADDR,...)");
  if(bind(mysocket, (struct sockaddr *)&zion, sizeof(struct sockaddr))== -1){
    perror("bind");
    exit(1);
  }
  if(listen(mysocket, BACKLOG) < 0){
    perror("listen");
    exit(1);
  }
  tamanho = sizeof(struct sockaddr_in);
  if((newsocket = accept(mysocket, (struct sockaddr *)&neo,&tamanho)) < 0){
    perror("accept");
  }
  printf("\nServidor: Chegando conexao\n");
  download(newsocket);
  close(newsocket);
  close(mysocket);
  push();

  return 0;
}
