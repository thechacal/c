#include <stdio.h>
#include <string.h>
#include "../../mylibs/github.h" // https://github.com/thechacal/c/tree/master/mylibs

int main(int argc, char const *argv[]) {

  char str[10],mes[10],dia[10];
  int i,j,pos[1];

  i=j=0;
  printf("\nType de Date at the format aaaa-mm-dd: ");
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
  j=0;
  for(i=pos[0]+1;i<pos[1];i++){
    mes[j]=str[i];
    j+=1;
  }
  j=0;
  printf("New format: %s/%s/",dia,mes);
  for(i=0;i<pos[0];i++){
    printf("%c",str[i]);
    j+=1;
  }
  puts("\n");
  push();

  return 0;
}
