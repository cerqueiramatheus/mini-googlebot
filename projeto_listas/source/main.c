#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "lista_pchave.h"
#include "listaencadeada.h"
#include "pchave.h"
#include "site.h"
#include "utils.h"

void imprime_menu() {
    printf("\n==============MENU==============\n");
    printf("OPÇÃO \tDESCRIÇÃO\n");
    printf("1 \tInserir um site\n");
    printf("2 \tRemover um site\n");
    printf("3 \tInserir palavra-chave\n");
    printf("4 \tAtualizar relevância\n");
    printf("5 \tSair\n");
    printf("================================\n\n");
}

void inserir_site(LISTA *lista_sites) {
    printf("\n==========INSERIR SITE==========\n");

    // Cria o site
    SITE *site = site_criar_completo();
    if (!lista_inserir_encadeada(lista_sites, site)) {
        printf("Erro! Código já existente!\n");
        site_apagar(&site);
    }

    // Exibe a lista atualizada
    lista_imprimir_encadeada(lista_sites);

    printf("================================\n\n");
}

void remover_site(LISTA *lista_sites) {
    printf("\n==========REMOVER SITE==========\n");

    // Recebe o código do site
    int codigo;
    printf("Digite o código do site:\n");
    scanf("%d", &codigo);

    // Tenta remover o site
    if (!lista_remover_site_encadeada(lista_sites, codigo))
        printf("Código inexistente. Não foi possível apagar o site!\n");

    // Imprime a nova lista
    lista_imprimir_encadeada(lista_sites);

    printf("================================\n\n");
}

void inserir_palavra_chave(LISTA *lista_sites) {
    printf("\n=====INSERIR PALAVRA-CHAVE======\n");

    // Recebe o código do site
    int codigo;
    printf("Digite o código do site:\n");
    scanf("%d", &codigo);

    // Busca o site
    SITE *site = lista_busca_encadeada(lista_sites, codigo);

    // Se existir, recebe e insere a nova palavra-chave
    if (site != NULL) {
        printf("Digite a nova palavra-chave:\n");

        char *auxiliar = NULL;
        do {
            limpa_entrada(stdin);
            auxiliar = ler_linha(stdin, LIMITE_STRING);

            if (auxiliar != NULL) {
                PCHAVE *pchave = pchave_criar(auxiliar);

                if (lista_pchave_inserir(site_get_palavras_chave(site), pchave) == FALSE) {
                    printf("Lista de palavras-chave cheia!\n");
                    pchave_apagar(&pchave);
                }

            } else {
                printf("Palavra-chave estoura o limite. Insira novamente:\n");
            }
        } while (auxiliar == NULL);

    } else {
        printf("Site não encontrado. Não é possível inserir palavra-chave!\n");
        site_apagar(&site);
    }

    // Imprime a lista atualizada
    lista_imprimir_encadeada(lista_sites);

    printf("================================\n\n");
}

void atualizar_relevancia(LISTA *lista_sites) {
    printf("\n======ATUALIZAR RELEVÂNCIA======\n");

    // Recebe o código do site
    int codigo;
    printf("Digite o código do site:\n");
    scanf("%d", &codigo);

    // Busca o site
    SITE *site = lista_busca_encadeada(lista_sites, codigo);

    // Se o site existir, recebe e atribui a nova relevância
    if (site != NULL) {
        int relevancia;
        printf("Digite a nova relevância:\n");
        scanf("%d", &relevancia);
        site_set_relevancia(site, relevancia);
    } else
        printf("Site inexistente. Impossível atualizar relevância!\n");

    // Imprime a nova lista
    lista_imprimir_encadeada(lista_sites);

    printf("================================\n\n");
}

int main() {
    FILE *arquivo_entrada = NULL;
    LISTA *lista_sites = NULL;
    int codigo, escolha = 0;

    //fazer a leitura do arquivo googlebot.txt
    arquivo_entrada = fopen("googlebot.txt", "r");

    //ler o arquivo de texto e adicionar os sites lidos em uma lista
    lista_sites = lista_criar_encadeada_ler_csv(arquivo_entrada);

    while (escolha != 5) {
        imprime_menu();
        printf("Digite sua escolha:\n");
        scanf("%d", &escolha);
        limpa_entrada(stdin);

        switch (escolha) {
            case 1:
                inserir_site(lista_sites);
                break;

            case 2:
                remover_site(lista_sites);
                break;

            case 3:
                inserir_palavra_chave(lista_sites);
                break;

            case 4:
                atualizar_relevancia(lista_sites);
                break;

            default:
                printf("Programa terminado\n");
                break;
        }
    }

    lista_apagar_encadeada(&lista_sites);
    fclose(arquivo_entrada);

    return EXIT_SUCCESS;
}
