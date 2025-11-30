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
    char nomeParaRemover[30];
    int i, j, encontrou;

    do {
        printf("\n=== MOCHILA DO AVENTUREIRO (%d/%d) ===\n", totalItens, CAPACIDADE_MAXIMA);
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: 
                if (totalItens < CAPACIDADE_MAXIMA) {
                    printf("\n--- Novo Item ---\n");
                    
                    printf("Nome: ");
                    scanf("%s", mochila[totalItens].nome);
                    
                    printf("Tipo: ");
                    scanf("%s", mochila[totalItens].tipo);
                    
                    printf("Quantidade: ");
                    scanf("%d", &mochila[totalItens].quantidade);
                    
                    totalItens++;
                    printf("Item guardado com sucesso!\n");
                } else {
                    printf("A mochila esta cheia! Remova algo antes.\n");
                }
                break;

            case 2:
                if (totalItens == 0) {
                    printf("A mochila ja esta vazia.\n");
                } else {
                    printf("Nome do item para remover: ");
                    scanf("%s", nomeParaRemover);
                    
                    encontrou = 0;
                    for (i = 0; i < totalItens; i++) {
                        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
                            encontrou = 1;
                            
                            for (j = i; j < totalItens - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            
                            totalItens--;
                            printf("🗑️ Item '%s' jogado fora.\n", nomeParaRemover);
                            break;
                        }
                    }
                    
                    if (!encontrou) {
                        printf("Item nao encontrado na mochila.\n");
                    }
                }
                break;

            case 3:
                printf("\n--- Conteudo da Mochila ---\n");
                if (totalItens == 0) {
                    printf("A mochila esta vazia (cri, cri...).\n");
                } else {
                    for (i = 0; i < totalItens; i++) {
                        printf("Slot %d: %s | Tipo: %s | Qtd: %d\n", 
                                i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                    }
                }
                break;

            case 0:
                printf("Saindo do inventario...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}