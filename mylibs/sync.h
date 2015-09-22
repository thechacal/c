/*
 * Sync é um protótipo de biblioteca que propõe a transferência de arquivos binários entre um cliente e um host.
 *
 * Desenvolvido por:
 *
 * Edluise Costa a.k.a ThEcHaCaL
 * Iuri Diniz a.k.a CLX
 * Caio Vilar a.k.a Hellscoffe
 *
 * Seguranca em Cinema Digital 4k3D
 * ECT/UFRN
 * */

#ifndef SYNC_H_
#define SYNC_H_

#define MAXNAMESIZE 32
#define MAXSTRUCTSIZE 48
#define MAXDATASIZE 256
#define VERSION	1

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "github.h"

struct header{
  int sync;//4bytes //default 0x7cab hex value
	char filename[MAXNAMESIZE];//32bytes
	int filesize;//4 byte
	int header_size;//4
	int version;//4bytes
	//48 bytes;
};


int upload(int sd,char* file){

  char buffer[MAXDATASIZE];
	struct stat st;
	int fd;
	int read_bytes;
	int sent_bytes;
	struct header hd;
  void *p = buffer;
	FILE *fp;
	hd.sync = 31915;
	fp = fopen(file,"rb");

	if(fp == NULL){
    printf("Arquivo não encontrado!\n");
		return 1;
	}
	if((stat(file,&st) < 0)){
    printf("Falha ao tentar pegar o tamanho do arquivo:[%s]",file);
		return 1;
	}
	hd.filesize = st.st_size;
	strcpy(hd.filename,file);
	hd.version = VERSION;
	hd.header_size = sizeof(hd);
	printf("Dados do cabeçalho: \n|\tSync\t|\tFilename\t|\tFilesize\t|\tHeader Size\t|\tVersion\t|\n|\t%d\t|\t%s\t|\t%d\t|\t%d\t|\t%d\t|\n",hd.sync,hd.filename,hd.filesize,hd.header_size,hd.version);

	if((send(sd,(void *)&hd,MAXSTRUCTSIZE,0)) < 0){
    printf("Falhou em mandar o cabeçalho!\n");
		return 1;
	}
	while(1){
    fd = fileno(fp);
		read_bytes = read(fd,buffer,MAXDATASIZE);
		if(read_bytes < 0){
      printf("Erro ao ler o arquivo[%s].\n",hd.filename);
			break;
		}
		if(read_bytes == 0){
      break;
		}
		while(read_bytes > 0){
			sent_bytes = send(sd,p,read_bytes,0);
			if(sent_bytes < 0){
        printf("Erro ao escrever no socket!\n");
				break;
			}
			read_bytes -= sent_bytes;
			p += sent_bytes;
    }
  }
	fclose(fp);
	printf("Arquivo enviado.\n");
	printf("Fechando a conexão.\n");
	close(sd);

	return 0;
}


int download(int sd){
  struct header hd2;
	char buffer[MAXDATASIZE];
	int recv_bytes;
	int bytes_file;
	int written_bytes;
	FILE *fp;
	void *pheader = &hd2;
	if((recv(sd,(void *)buffer,MAXDATASIZE,0)) < 0){
    printf("Falhou em receber o cabeçalho do arquivo.\n");
		return 1;
	}
	memcpy(pheader,(void*)buffer,MAXSTRUCTSIZE);
	if(hd2.sync != 31915){
    printf("Cabeçalho de arquivo corrompido.\n");
		return 1;
	}
	else{
    printf("Dados do cabeçalho: \n|\tSync\t|\tFilename\t|\tFilesize\t|\tHeader Size\t|\tVersion\t|\n|\t%d\t|\t%s\t|\t%d\t|\t%d\t|\t%d\t|\n",hd2.sync,hd2.filename,hd2.filesize,hd2.header_size,hd2.version);
	}
	fp = fopen(hd2.filename,"w");
	bytes_file = hd2.filesize;
	bzero(&buffer,sizeof(buffer));
	while(bytes_file > 0){
		recv_bytes = recv(sd,(void*)buffer,MAXDATASIZE,0);
		if(recv_bytes < 0){
      printf("Erro ao receber o arquivo.\n");
			return 1;
		}
		written_bytes = fwrite((void*)buffer, recv_bytes,1,fp);
		if(written_bytes < 0){
			printf("Falha ao tentar escrever no arquivo.\n");
			return 1;
		}
		if(written_bytes == 0){
			break;
		}
		bytes_file -= written_bytes;
	}
	fclose(fp);
	printf("Arquivo enviado.\n");
	printf("Fechando a conexão.\n");
	close(sd);
  push();
  
	return 0;
}
#endif
