#include <stdio.h>
#include "../mylibs/github.h"

int main(int argc, char const *argv[]) {

  int dia, mes, ano;

  printf("Digite um dia: ");
  scanf("%d",&dia);
  printf("Digite um mês: ");
  scanf("%d",&mes);
  printf("Digite um ano: ");
  scanf("%d",&ano);
  printf("%d//%d//%d\n",dia,mes,ano );

  push();

  return 0;
}
