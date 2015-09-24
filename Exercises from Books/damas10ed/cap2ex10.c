#include <stdio.h>
#include <string.h>
#include "../../mylibs/github.h" // https://github.com/thechacal/c/tree/master/mylibs

int main(int argc, char const *argv[]) {

  char str[10],ano[10],mes[10],dia[10];
  int i=0;
  int j=0;
  int pos[1];
  int tamanho;

  printf("Date at the format aaaa-mm-dd:");
  scanf(" %10[^\n]",str);
  while(str[i]!='\0'){
    if(str[i]=='-'){
      pos[j]=i;
      j+=1;
    }
    i+=1;
  }
  j=0;
  for(i=(pos[1])+1;i<strlen(str);i++){
    dia[j]=str[i];
    j+=1;
  }
  //printf("%s\n",dia);
  j=0;
  for(i=pos[0]+1;i<pos[1];i++){
    mes[j]=str[i];
    j+=1;
  }
  //printf("%s\n",mes);
  j=0;
  //printf("%d\n",pos[0]);
  printf("New format: %s/%s/",dia,mes);
  for(i=0;i<pos[0];i++){
    ano[j]=str[i];
    printf("%c",str[i]);
    j+=1;
  }
  push("\n");
  //push();

  return 0;
}
