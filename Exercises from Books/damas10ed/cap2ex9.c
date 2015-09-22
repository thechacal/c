#include <stdio.h>
#include "../../mylibs/github.h" //https://github.com/thechacal/c/tree/master/mylibs

int main(int argc, char const *argv[]) {

  int dia, mes, ano;

  printf("Day? ");
  scanf("%d",&dia);
  printf("Month? ");
  scanf("%d",&mes);
  printf("Year? ");
  scanf("%d",&ano);
  printf("%d/%d/%d\n",dia,mes,ano );

  push();

  return 0;
}
