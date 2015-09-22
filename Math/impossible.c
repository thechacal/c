/*******************************************************************************

   Este programa resolve o seguinte problema:

   "Dois numeros inteiros (nao necessariamente diferentes) entre 2 e 20 sao
   escolhidos. Apenas a soma dos dois numeros e dada ao matematico Sergio.
   Apenas o produto dos dois numeros e dado ao matematico Paulo.

   Por telefone, Sergio diz a Paulo: 'Nao existem meios para que voce determine
   minha soma'. Uma hora depois, Paulo telefona de volta para dizer: 'Eu sei a
   sua soma'. Mais tarde, Sergio telefona novamente para Paulo para anunciar:
   'Agora eu sei o seu produto'.

   Quais sao os dois numeros?"

   Para compilar, inclua a biblioteca de matematica (-lm).

   Edluise Costa Moura a.k.a ThEcHaCaL
   Nov/2002
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../mylibs/github.h"

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
       i, j, np, ns, n,     /* contadores                                     */
       p, s,                /* produto e soma dos numeros escolhidos          */
       pMax, sMax,          /* cotas superiores para o produto e a soma       */
       pant, sant;          /* variveis auxiliares                            */

  if (argc<2) {
    fprintf(stderr, "Uso: %s cota_superior\n", argv[0]);
    exit(1);
  }

  N = atoi(argv[1]);

  if (N<2) {
    fprintf(stderr, "Cota superior invalida.\n");
    exit(1);
  }

  pMax = N*N;
  sMax = N+N;

  if ( (produto=malloc(pMax+1)) == NULL || (soma=malloc(sMax+1)) == NULL ) {
    fprintf(stderr, "Memoria nao disponivel.\n");
    exit(1);
  }

  /***
  *
  *  Calculo de
  *
  *  P_0 = { m natural; 4 <= m <= pMax e p tem pelo menos uma fatoracao },
  *  S_0 = { m natural; 4 <= m <= sMax }.
  *
  ***/

  for(i=4; i<=pMax; i++)
    produto[i] = 0;

  for(i=2; i<=N; i++)
    for(j=i; j<=N; j++)
      produto[i*j] = 1;

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

  np = 0;
  for(i=4; i<=pMax; i++)
    if(produto[i])
      np++;
  printf("P_0 tem %d elemento(s).\n", np);

  np = 0;
  for(i=4; i<=sMax; i++)
    if(soma[i])
      np++;
  printf("S_0 tem %d elemento(s).\n", np);

  /***
  *
  *  Calculo de
  *
  *  P_1 = { m em P_0; m tem pelo menos duas fatoracoes }.
  *
  ***/

  printf("*** Sergio: Nao existem meios para que voce determine minha soma.\n");

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

  np = 0;
  for(i=4; i<=pMax; i++)
    if(produto[i])
      np++;
  printf("P_1 tem %d elemento(s).\n", np);

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

  /***
  *
  *  Ate aqui:
  *
  *  -> m esta em S_1 sse soma[m] = 1;
  *  -> s esta em S_1.
  *
  ***/

  ns = 0;
  for(i=4; i<=sMax; i++)
    if(soma[i])
      ns++;

  printf("S_1 tem %d elemento(s).\n", ns);

  /***
  *
  *  Calculo de
  *
  *  P_2 = { m em P_1; existe uma unica fatoracao (i,j) de m tal que
  *                    i+j esta em S_1 }.
  *
  ***/

  printf("*** Paulo : Eu sei a sua soma.\n");

  for(i=2; i<=N; i++)
    for(j=i; j<=N; j++)
      if(produto[i*j] && soma[i+j])
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
  *  Ate aqui:
  *
  *  -> m esta em P(2) sse produto[m] = 1;
  *  -> p esta em P(2);
  *
  ***/

  np = 0;
  for(i=4; i<=pMax; i++)
    if(produto[i])
      np++;

  printf("P_2 tem %d elemento(s).\n", np);

  /***
  *
  *  Calculo de
  *
  *  S_2 = { m in S_1; existe uma unica decomposicao (i,j) de m tal que
  *                    i*j esta em P_2 }.
  *
  ****/

  printf("*** Sergio: Agora eu sei o seu produto.\n");

  for(i=2; i<=N; i++)
    for(j=i; j<=N; j++)
      if(soma[i+j] && produto[i*j])
        soma[i+j]++;

  ns = 0;
  for(i=4; i<=sMax; i++)
    if(soma[i]==2) {
      soma[i] = 1;
      ns++;
      s = i;
    }
    else
      soma[i] = 0;

  /***
  *
  *  Ate aqui:
  *
  *  -> m esta em S_2 sse soma[m] = 1;
  *  -> s esta em S_2.
  *
  ***/

  printf("S_2 tem %d elemento(s).\n", ns);

  /***
  *
  *  Para n = 3, ... , definimos
  *
  *  P_n = { m em P_{n-1}; existe uma unica factoracao (i,j) de m tal que
  *                        i+j esta em S_{n-1} },
  *
  *  S_n = { m em S_{n-1}; existe uma unica decomposicao (i,j) de m tal que
  *                        i*j esta em P_n }.
  *
  ***/

  n = 3;

  while(np!=1 || ns!=1) {

    pant = np;
    sant = ns;

    /***
    *
    *  Calculo de P_n.
    *
    ***/

    if(np!=1) {
      np = 0;
      for(i=2; i<=N; i++)
        for(j=i; j<=N; j++)
          if(produto[i*j] && soma[i+j])
            produto[i*j]++;

      for(i=4; i<=pMax; i++)
        if(produto[i]==2) {
          produto[i] = 1;
          np++;
          /* p sera o maior produto admisivel */
          p = i;
        }
        else
          produto[i] = 0;
    }

    /***
    *
    *  Ate aqui:
    *
    *  -> m esta em P_n sse produto[m] = 1;
    *  -> p esta em P_n.
    *
    ***/

    printf("P_%d tem %d elemento(s).\n", n, np);

    /***
    *
    *  Calculo de S_n.
    *
    ***/

    if(ns!=1) {
      ns = 0;
      for(i=2; i<=N; i++)
        for(j=i; j<=N; j++)
          if(soma[i+j] && produto[i*j])
            soma[i+j]++;

      for(i=4; i<=sMax; i++)
        if(soma[i]==2) {
          soma[i] = 1;
          ns++;
          /* s sera a maior soma admissivel */
          s = i;
        }
        else
           soma[i] = 0;
    }

    /***
    *
    *  Ate aqui:
    *
    *  -> m esta em S_n sse soma[m] = 1;
    *  -> s esta em P_n.
    *
    ***/

    printf("S_%d tem %d elemento(s).\n", n, ns);

    /***
    *
    *  Verifica se o processo esta se repetindo sem avanco.
    *
    ***/

    if(np == pant && ns == sant) {
      printf("Sinto muito, o problema e \"literalmente impossivel\".\n");

      if (np) {
         printf("Produto(s) admissivel(is): ");
         for(i=4;i<=pMax;i++)
           if(produto[i])
             printf("%d ",i);
         putchar('\n');
      }

      if (ns) {
         printf("Soma(s) admissivel(is): ");
         for(i=4;i<=sMax;i++)
           if(soma[i])
             printf("%d ",i);
         putchar('\n');
      }

      exit(0);
    }

    n++;
  }

  printf("O produto vale %d e a soma vale %d.\n", p, s);

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
