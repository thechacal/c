/*******************************************************************************

   Considere a seguinte situacao (sendo N>1 dado):

   Dois numeros inteiros (nao necessariamente diferentes) entre 2 e 20 sao
   escolhidos. Apenas a soma dos dois numeros e dada ao matematico Sergio.
   Apenas o produto dos dois numeros e dado ao matematico Paulo.

   Por telefone, Sergio diz a Paulo: 'Nao existem meios para que voce determine
   minha soma'. Uma hora depois, Paulo telefona de volta para dizer: 'Eu sei a
   sua soma'. Mais tarde, Sergio telefona novamente para Paulo para anunciar:
   'Agora eu sei o seu produto'.

   Este programa se coloca no lugar de Paulo. Dependendo do numero dado a Paulo,
   o dialogo acima pode ser verdadeiro ou falso. Sendo falso, o programa para.
   Por outro lado, supoe-se que Sergio dira exatamente o que aparece acima e o
   programa vai acreditar.

   Para compilar, inclua a biblioteca de matematica (-lm).

   Edluise Costa Moura a.k.a ThEcHaCaL
   Nov/2002
*******************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

void resolve(int s);

int p=0;

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
       i, j, np, ns,        /* contadores                                     */
       s,                   /* a soma dos numeros escolhidos                  */
       pMax, sMax;          /* cotas superiores para o produto e a soma       */

  if (argc<3) {
    fprintf(stderr, "Uso: %s cota_superior produto\n", argv[0]);
    exit(1);
  }

  N = atoi(argv[1]);
  if (N<2) {
    fprintf(stderr, "Cota superior invalida.\n");
    exit(1);
  }

  pMax = N*N;
  sMax = N+N;

  p = atoi(argv[2]);
  if (p<4 || p>pMax) {
    fprintf(stderr, "Produto invalido.\n");
    exit(1);
  }

  if ( (produto=malloc(pMax+1)) == NULL || (soma=malloc(sMax+1)) == NULL ) {
    fprintf(stderr, "Memoria nao disponivel.\n");
    exit(1);
  }

  /***
  *
  *  P_0 = { m natural; 4 <= m <= pMax },
  *
  *  Em vez de tomar
  *
  *  S_0 = { m natural; 4 <= m <= sMax }.
  *
  *  P toma
  *
  *  S_0 = { m natural; 4 <= m <= sMax e existe decomposicao (i,j) de m tal que
  *                     p=i*j }.
  *
  *  Sergio nao conhece S_0 ja que nao conhece p. Entretando, ele conhece s que
  *  e melhor que conhecer S_0.
  *
  ***/

  for(i=4; i<=pMax; i++)
    produto[i] = 1;

  for(i=4; i<=sMax; i++)
    soma[i] = 0;

  for(i=2; i<=N; i++)
    for(j=i; j<=N; j++)
      if(i*j==p)
        soma[i+j] = 1;

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
  *  Paulo diz "Eu sei a sua soma." sse S_0 = {s}.
  *
  ***/

  ns = 0;
  for(i=4; i<=sMax; i++)
    if(soma[i]) {
      ns++;
      s = i;
    }

  if(ns==1)
    resolve(s);

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

  if (!produto[p]) {
    fprintf(stderr, "Produto invalido.\n");
    exit(1);
  }

  /***
  *
  *  Ate aqui:
  *
  *  -> m esta em P(1) sse produto[m] = 1;
  *  -> p esta em P(1).
  *
  ***/

  /***
  *
  *  S_1 = { m em S_0; para toda decomposicao (i,j) de m temos i*j em P_1 }
  *      = S_0 - { m em S_0; existe uma decomposicao (i,j) de m tal que
  *                          i*j nao esta em P_1 }.
  *
  *  Sergio nao conhece S_1 ja que nao conhece S_0.
  *
  ***/

  printf("*** Sergio: Nao existem meios para que voce determine minha soma.\n");

  for(i=2; i<=N; i++)
    for(j=i; j<=N; j++)
      if(!produto[i*j])
        soma[i+j] = 0;

 /***
  *
  *  Ate aqui:
  *
  *  -> m esta em S(1) sse soma[m] = 1;
  *  -> s esta em S(1).
  *
  ***/

  /***
  *
  *  Paulo diz "Eu sei a sua soma." sse S_1 = {s}.
  *
  ***/

  ns = 0;
  for(i=4; i<=sMax; i++)
    if(soma[i]) {
      ns++;
      s = i;
    }

  if(ns==0)
    printf("*** Paulo : Voce tem razao.\n");
  else if(ns==1)
    resolve(s);
  else {
    printf("*** Paulo : Sua soma e um dos seguintes numeros:\n");
    for(i=4; i<=sMax; i++)
      if(soma[i])
        printf("%d ",i);
    putchar('\n');
  }

  exit(0);

}

void resolve(s)

int s;

{
  int i,j;

  printf("*** Paulo : Eu sei sua soma: %d.\n", s);

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
