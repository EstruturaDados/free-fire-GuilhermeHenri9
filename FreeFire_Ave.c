#include <stdio.h>
#include <string.h> 

typedef struct {
    char nome[30];
    char tipo[30];
    int quantidade;
} Item;

#define CAPACIDADE_MAXIMA 10

int main() {
    Item mochila[CAPACIDADE_MAXIMA];
    int totalItens = 0; 
    int opcao;
    
    char termoBusca[30]; 
    int i, j, encontrou; 

    do {
        printf("\n=== MOCHILA DO AVENTUREIRO (Nvl 2) ===\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item (NOVO)\n"); 
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: 
                if (totalItens < CAPACIDADE_MAXIMA) {
                    printf("Nome: "); scanf("%s", mochila[totalItens].nome);
                    printf("Tipo: "); scanf("%s", mochila[totalItens].tipo);
                    printf("Qtd: ");  scanf("%d", &mochila[totalItens].quantidade);
                    totalItens++;
                    printf("Item adicionado.\n");
                } else {
                    printf("Mochila cheia!\n");
                }
                break;

            case 2: 
                if (totalItens == 0) {
                    printf("Mochila vazia.\n");
                } else {
                    printf("Nome para remover: ");
                    scanf("%s", termoBusca);
                    encontrou = 0;
                    
                    for (i = 0; i < totalItens; i++) {
                        if (strcmp(mochila[i].nome, termoBusca) == 0) {
                            encontrou = 1;
                            for (j = i; j < totalItens - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            totalItens--;
                            printf("Item removido.\n");
                            break;
                        }
                    }
                    if (!encontrou) printf("Item nao encontrado.\n");
                }
                break;

            case 3: 
                printf("\n--- Inventario Completo ---\n");
                for (i = 0; i < totalItens; i++) {
                    printf("%d. %s (Tipo: %s) - Qtd: %d\n", 
                        i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                }
                break;

            case 4: 
                if (totalItens == 0) {
                    printf("A mochila esta vazia. Nada para buscar.\n");
                } else {
                    printf("\nDigite o nome do item para buscar: ");
                    scanf("%s", termoBusca);

                    encontrou = 0; 

                    for (i = 0; i < totalItens; i++) {
                        if (strcmp(mochila[i].nome, termoBusca) == 0) {
                            printf("\n--- ITEM ENCONTRADO! ---\n");
                            printf("Nome: %s\n", mochila[i].nome);
                            printf("Tipo: %s\n", mochila[i].tipo);
                            printf("Quantidade: %d\n", mochila[i].quantidade);
                            printf("Posicao na mochila: %d\n", i + 1);
                            
                            encontrou = 1; 
                            break; 
                        }
                    }

                    if (!encontrou) {
                        printf("\nO item '%s' nao esta na mochila.\n", termoBusca);
                    }
                }
                break;

            case 0:
                printf("Guardando a mochila...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}