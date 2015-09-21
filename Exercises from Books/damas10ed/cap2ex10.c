#include <stdio.h>
#include "../../mylibs/github.h"

int main(int argc, char const *argv[]) {

  char str[10];
  int dia, mes, ano;

  printf("Date at the format aaaa-mm-dd: ");
  scanf("%d",&dia);
  printf("%d/%d/%d\n",dia,mes,ano );

  //push();

  return 0;
}
