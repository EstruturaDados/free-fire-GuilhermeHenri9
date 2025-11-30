#include <stdio.h>
#include <string.h>
#include <stdbool.h> 

typedef struct {
    char nome[30];
    char tipo[30];
    int quantidade;
    int prioridade; 
} Item;

enum CriterioOrdenacao { NAO_ORDENADO, POR_NOME, POR_TIPO, POR_PRIORIDADE };

#define CAPACIDADE_MAXIMA 10

int estadoOrdenacao = NAO_ORDENADO;

int main() {
    Item mochila[CAPACIDADE_MAXIMA];
    int totalItens = 0;
    int opcao, subOpcao;
    char termoBusca[30];
    int i, j;
    
    Item itemPivo; 
    long comparacoes; 
    int inicio, fim, meio; 
    bool encontrado;

    do {
        printf("\n===  MOCHILA MESTRE (Nvl 3) ===\n");
        printf("Estado atual: ");
        if (estadoOrdenacao == POR_NOME) printf("[Ordenado por NOME]\n");
        else if (estadoOrdenacao == POR_PRIORIDADE) printf("[Ordenado por PRIORIDADE]\n");
        else if (estadoOrdenacao == POR_TIPO) printf("[Ordenado por TIPO]\n");
        else printf("[Desordenado]\n");

        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n"); 
        printf("3. Ordenar Mochila (Insertion Sort)\n");
        printf("4. Listar Itens\n");
        printf("5. Busca Binaria (Requer Ordenacao por Nome)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: 
                if (totalItens < CAPACIDADE_MAXIMA) {
                    printf("\nNome: "); scanf(" %[^\n]", mochila[totalItens].nome);
                    printf("Tipo: "); scanf(" %[^\n]", mochila[totalItens].tipo);
                    printf("Qtd: ");  scanf("%d", &mochila[totalItens].quantidade);
                    
                    do {
                        printf("Prioridade (1-5): ");
                        scanf("%d", &mochila[totalItens].prioridade);
                    } while(mochila[totalItens].prioridade < 1 || mochila[totalItens].prioridade > 5);

                    totalItens++;
                    estadoOrdenacao = NAO_ORDENADO; 
                    printf("Item adicionado.\n");
                } else {
                    printf("Mochila cheia!\n");
                }
                break;

            case 2: 
                if (totalItens == 0) {
                    printf("Mochila vazia. Nada para remover.\n");
                } else {
                    printf("Nome do item para remover: ");
                    scanf(" %[^\n]", termoBusca);
                    
                    encontrado = false;
                    
                    for (i = 0; i < totalItens; i++) {
                        if (strcmp(mochila[i].nome, termoBusca) == 0) {
                            encontrado = true;
                            
                            for (j = i; j < totalItens - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            
                            totalItens--;
                            printf("🗑️ Item '%s' removido com sucesso.\n", termoBusca);
                            
                            break; 
                        }
                    }
                    
                    if (!encontrado) {
                        printf("❓ Item nao encontrado.\n");
                    }
                }
                break;
            
            case 3: 
                if (totalItens < 2) {
                    printf("Poucos itens para ordenar.\n");
                } else {
                    printf("\nCRITERIO DE ORDENACAO:\n");
                    printf("1. Nome\n2. Tipo\n3. Prioridade\nEscolha: ");
                    scanf("%d", &subOpcao);

                    comparacoes = 0;

                    for (i = 1; i < totalItens; i++) {
                        itemPivo = mochila[i]; 
                        j = i - 1;

                        bool deveMover = false;

                        while (j >= 0) {
                            comparacoes++; 

                            if (subOpcao == 1) { 
                                deveMover = (strcmp(mochila[j].nome, itemPivo.nome) > 0);
                            } else if (subOpcao == 2) { 
                                deveMover = (strcmp(mochila[j].tipo, itemPivo.tipo) > 0);
                            } else if (subOpcao == 3) { 
                                deveMover = (mochila[j].prioridade < itemPivo.prioridade);
                            }

                            if (deveMover) {
                                mochila[j + 1] = mochila[j]; 
                                j = j - 1;
                            } else {
                                break; 
                            }
                        }
                        mochila[j + 1] = itemPivo; 
                    }

                    printf("Ordenacao concluida com %ld comparacoes.\n", comparacoes);
                    
                    if (subOpcao == 1) estadoOrdenacao = POR_NOME;
                    else if (subOpcao == 2) estadoOrdenacao = POR_TIPO;
                    else if (subOpcao == 3) estadoOrdenacao = POR_PRIORIDADE;
                }
                break;

            case 4: 
                printf("\n--- Inventario ---\n");
                for (i = 0; i < totalItens; i++) {
                    printf("[%d] %s | Tipo: %s | Qtd: %d | Prioridade: %d\n", 
                        i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
                }
                break;

            case 5: 
                if (estadoOrdenacao != POR_NOME) {
                    printf("ERRO: Para busca binaria, ordene por NOME primeiro (Opcao 2 -> 1).\n");
                } else {
                    printf("\nBusca Rapida (Binaria): Digite o nome: ");
                    scanf(" %[^\n]", termoBusca);

                    inicio = 0;
                    fim = totalItens - 1;
                    encontrado = false;
                    int passos = 0;

                    while (inicio <= fim) {
                        passos++;
                        meio = (inicio + fim) / 2;
                        
                        int resultadoComparacao = strcmp(mochila[meio].nome, termoBusca);

                        if (resultadoComparacao == 0) {
                            printf("\nENCONTRADO em %d passo(s)!\n", passos);
                            printf("Item: %s | Qtd: %d | Prioridade: %d\n", 
                                mochila[meio].nome, mochila[meio].quantidade, mochila[meio].prioridade);
                            encontrado = true;
                            break;
                        } 
                        else if (resultadoComparacao < 0) {
                            inicio = meio + 1;
                        } 
                        else {
                            fim = meio - 1;
                        }
                    }

                    if (!encontrado) {
                        printf("Item nao encontrado (verificados %d passos).\n", passos);
                    }
                }
                break;

            case 0:
                printf("Finalizando sistema...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}