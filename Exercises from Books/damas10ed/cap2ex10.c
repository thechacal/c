#include <stdio.h>
#include "../../mylibs/github.h"

int main(int argc, char const *argv[]) {

  char str[15];

  printf("Date at the format aaaa-mm-dd:");
  scanf("%s",str);
  printf("%s\n",str);

  push();

  return 0;
}
