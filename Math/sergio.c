/*******************************************************************************

   Considere a seguinte situacao (sendo N>1 dado):

   Dois numeros inteiros (nao necessariamente diferentes) entre 2 e 20 sao
   escolhidos. Apenas a soma dos dois numeros e dada ao matematico Sergio.
   Apenas o produto dos dois numeros e dado ao matematico Paulo.

   Por telefone, Sergio diz a Paulo: 'Nao existem meios para que voce determine
   minha soma'. Uma hora depois, Paulo telefona de volta para dizer: 'Eu sei a
   sua soma'. Mais tarde, Sergio telefona novamente para Paulo para anunciar:
   'Agora eu sei o seu produto'.

   Este programa se coloca no lugar de Sergio. Dependendo do numero dado a
   Sergio, o dialogo acima pode ser verdadeiro ou falso. Sendo falso, o programa
   para. Por outro lado, supoe-se que Paulo dira exatamente o que aparece acima
   e o programa vai acreditar.

   Para compilar, inclua a biblioteca de matematica (-lm).

   Ed Moura a.k.a ThEcHaCaL
   Nov/2002
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../mylibs/github.h"

int s=0;

/***
*
* Parte principal.
*
***/

int main(argc, argv)

int argc;
char *argv[];

{
  char *produto,            /* produto[i] = 1 sse i e um produto admissivel   */
       *soma;               /* soma[i]    = 1 sse i e uma soma admissivel     */
  int  N=0,                 /* cota superior para os numeros escolhidos       */
       i, j, k, l, np, ns,  /* contadores                                     */
       p,                   /* o produto dos numeros escolhidos               */
       pMax, sMax;          /* cotas superiores para o produto e a soma       */

  if (argc<3) {
    fprintf(stderr, "Uso: %s cota_superior soma\n", argv[0]);
    exit(1);
  }

  N = atoi(argv[1]);
  if (N<2) {
    fprintf(stderr, "Cota superior invalida.\n");
    exit(1);
  }

  pMax = N*N;
  sMax = N+N;

  s = atoi(argv[2]);
  if (s<4 || s>sMax) {
    fprintf(stderr, "Soma invalida.\n");
    exit(1);
  }

  if ( (produto=malloc(pMax+1)) == NULL || (soma=malloc(sMax+1)) == NULL ) {
    fprintf(stderr, "Memoria nao disponivel.\n");
    exit(1);
  }

  /***
  *
  *  Calculo de
  *
  *  P_0 = { m natural; 4 <= m <= pMax },
  *  S_0 = { m natural; 4 <= m <= sMax }.
  *
  ***/

  for(i=4; i<=pMax; i++)
    produto[i] = 1;

  for(i=4; i<=sMax; i++)
    soma[i] = 1;

  /***
  *
  *  Ate aqui:
  *
  *  -> m esta em P_0 sse produto[m] = 1;
  *  -> p esta em P_0;
  *
  *  -> m esta em S_0 sse soma[m] = 1;
  *  -> s esta em S_0.
  *
  ***/

  /***
  *
  *  Calculo de
  *
  *  P_1 = { m em P_0; m tem pelo menos duas fatoracoes }.
  *
  ***/

  for(i=2; i<=N; i++)
    for(j=i; j<=N; j++)
      produto[i*j]++;

  for(i=4; i<=pMax; i++)
    produto[i] = (produto[i]>2);

  /***
  *
  *  Ate aqui:
  *
  *  -> m esta em P_1 sse produto[m] = 1;
  *  -> p esta em P_1.
  *
  ***/

  /***
  *
  *  Calculo de
  *
  *  S_1 = { m em S_0; para toda decomposicao (i,j) de m temos i*j em P_1 }
  *      = S_0 - { m em S_0; existe uma decomposicao (i,j) de m tal que
  *                          i*j nao esta em P_1 }.
  *
  ***/

  for(i=2; i<=N; i++)
    for(j=i; j<=N; j++)
      if(!produto[i*j])
        soma[i+j] = 0;

  if (!soma[s]) {
    printf("*** Sergio: Talvez voce possa determinar minha soma.\n");
    exit(0);
  }

  printf("*** Sergio: Nao existem meios para que voce determine minha soma.\n");

  /***
  *
  *  Ate aqui:
  *
  *  -> m esta em S_1 sse soma[m] = 1;
  *  -> s esta em S_1.
  *
  ***/

  /***
  *
  *  Em vez de tomar
  *
  *  P_2 = { m em P_1; existe uma unica fatoracao (i,j) de m tal que
  *                    i+j esta em S_1 }.
  *
  *  Sergio toma
  *
  *  P_2 = { m em P_1; exeiste uma unica fatoracao (i,j) de m tal
  *                    i+j = s }.
  *
  *  Paulo nao conhece P_2 ja que nao conhece s. Entretanto, ele conhece p, que
  *  e melhor do que conhecer P_2.
  *
  ***/

  printf("*** Paulo : Eu sei a sua soma.\n");

  for(i=2; i<=(j = s-i); i++)
    for(k=2; k<=N; k++)
      for(l=k; l<=N; l++)
        if(k*l==i*j && soma[k+l] && produto[i*j])
          produto[i*j]++;

  np = 0;
  for(i=4; i<=pMax; i++)
    if(produto[i]==2) {
      produto[i] = 1;
      np++;
      p = i;
    }
    else
      produto[i] = 0;

  /***
  *
  *  Ate aqui
  *
  *  -> m esta em P_2 sse produto[m] = 1;
  *  -> p esta em P_2.
  *
  ***/

  /***
  *
  *  Sergio dira "Agora eu sei o seu produto." sse P_2 = {p}.
  *
  ****/

  if(np!=1) {
    printf("*** Sergio: Seu produto e um dos seguintes numeros:\n");
    for(i=4; i<=pMax; i++)
      if(produto[i])
        printf("%d ",i);
    putchar('\n');
    exit(0);
  }

  printf("*** Sergio: Agora eu sei seu produto: %d.\n", p);

  /***
  *
  *  Calculando os numeros i e j. Sao raizes de
  *  (x-i)(x-j) = x^2 - (i+j)*x + i*j = x^2 - s x + p.
  *
  ***/

  i = (int) sqrt((double) (s*s - 4*p));
  j = i;

  i = 0.5 * (s-i);
  j = 0.5 * (s+j);

  printf("Os numeros escolhidos sao: %d e %d.\n", i, j);

  exit(0);
}
