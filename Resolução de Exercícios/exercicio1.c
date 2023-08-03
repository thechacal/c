#include <stdio.h>

#define NUM_PROJETOS 10

// Definindo a struct para agrupar as informações do projeto
struct Projeto {
    int numero;
    float saldo;
};

int main() {
    // Criando um vetor para armazenar as informações dos projetos
    struct Projeto projetos[NUM_PROJETOS];

    // Inicializando o vetor de projetos com saldo zero
    for (int i = 0; i < NUM_PROJETOS; i++) {
        projetos[i].numero = i;
        projetos[i].saldo = 0;
    }

    int numeroProjeto;
    float valor;
    char tipoDespesa;

    // Loop para ler as informações até que o número do projeto seja -1
    while (1) {
        printf("Digite o numero do projeto (-1 para encerrar): ");
        scanf("%d", &numeroProjeto);

        if (numeroProjeto == -1) {
            break; // Encerra o loop caso seja digitado -1
        }

        printf("Digite o valor: ");
        scanf("%f", &valor);

        printf("Digite o tipo de despesa (R - Receita, D - Despesa): ");
        scanf(" %c", &tipoDespesa);

        // Atualizando o saldo do projeto de acordo com o tipo de despesa
        if (tipoDespesa == 'R' || tipoDespesa == 'r') {
            projetos[numeroProjeto].saldo += valor;
        } else if (tipoDespesa == 'D' || tipoDespesa == 'd') {
            projetos[numeroProjeto].saldo -= valor;
        } else {
            printf("Tipo de despesa invalido! Use 'R' para Receita ou 'D' para Despesa.\n");
        }
    }

    // Imprimindo o saldo final de cada projeto
    printf("\nSaldo final de cada projeto:\n");
    for (int i = 0; i < NUM_PROJETOS; i++) {
        printf("Projeto %d: R$ %.2f\n", projetos[i].numero, projetos[i].saldo);
    }

    return 0;
}
