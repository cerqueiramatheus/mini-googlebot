#include "prompt_usuario.h"

// Imprime o menu da interface
void imprime_menu() {
    printf("\n==============MENU==============\n");
    printf("OPÇÃO \tDESCRIÇÃO\n");
    printf("1 \tInserir um site\n");
    printf("2 \tRemover um site\n");
    printf("3 \tInserir palavra-chave\n");
    printf("4 \tAtualizar relevância\n");
    printf("5 \tBusca palavra-chave\n");
    printf("6 \tSugestão de sites\n");
    printf("7 \tSair\n");
    printf("================================\n\n");
}

// Lê as informações do stdin e cria um novo site completo a partir delas
// Retorna um site
SITE *site_criar_completo() {
    SITE *site = NULL;
    PCHAVE *pchave;
    char *nome = NULL, *auxiliar = NULL, *link = NULL;
    int codigo, relevancia;

    site = site_criar();
    printf("Digite o código do site:\n");
    scanf("%d", &codigo);
    printf("\n");

    // Caso o código esteja dentro do limite
    if (codigo <= LIMITE_CODIGO && codigo >= 0) {
        printf("Digite o nome do site:\n");
        limpa_entrada(stdin);
        nome = ler_linha(stdin, LIMITE_STRING);
        printf("\n");

        // Caso o nome esteja no limite da string
        if (nome != NULL) {
            printf("Digite a revelância do site:\n");
            scanf("%d", &relevancia);
            printf("\n");

            // Caso a relevância esteja dentro do limite
            if (relevancia <= LIMITE_RELEVANCIA && relevancia >= 0) {
                printf("Digite o link do site:\n");
                limpa_entrada(stdin);
                link = ler_linha(stdin, LIMITE_LINK);
                printf("\n");

                // Caso o nome esteja no link da string
                if (link != NULL) {
                    site_set_codigo(site, codigo);
                    site_set_nome(site, nome);
                    site_set_relevancia(site, relevancia);
                    site_set_link(site, link);

                    boolean end = FALSE;
                    AVL_PCHAVE *lp = site_get_palavras_chave(site);
                    printf("Insira uma palavra-chave:\n");

                    // Insere palavras-chave
                    while (!end) {
                        do {
                            auxiliar = ler_linha(stdin, LIMITE_STRING);
                            printf("\n");

                            if (auxiliar != NULL) {
                                pchave = pchave_criar(auxiliar);

                                if (avl_pchave_inserir(site_get_palavras_chave(site), pchave) == FALSE) {
                                    printf("\nLista de palavras-chave cheia!\n");
                                    pchave_apagar(&pchave);
                                    end = TRUE;
                                }

                            } else {
                                printf("\nPalavra-chave estoura o limite. Insira novamente:\n");
                            }
                        } while (auxiliar == NULL);
                        if (!end) {
                            char aux;
                            printf("Deseja inserir uma nova palavra-chave? [S][N]\n");
                            scanf("%c", &aux);
                            if (tolower(aux) == 'n') end = TRUE;
                            if (!end) printf("\nInsira uma nova palavra-chave:\n");
                            fgetc(stdin);
                        }
                    }

                    return site;
                }
            }
        }
    }

    site_apagar(&site);
    return NULL;
}

// Lê as informações de um site e o insere numa lista
void inserir_site(AVL_SITE *lista_sites) {
    printf("\n==========INSERIR SITE==========\n");

    // Cria o site
    SITE *site = site_criar_completo();

    if (site != NULL) {
        if (!avl_site_inserir(lista_sites, site)) {
            printf("\nErro! Código do site já existente!\n");
            site_apagar(&site);
        }
    } else {
        printf("Erro! Verifique o tamanho do código, nome, link ou relevância do site!\n");
        limpa_entrada(stdin);
    }

    // Exibe a lista atualizada
    printf("\n================================\n\n");
    avl_site_imprimir(lista_sites);
    printf("================================\n\n");
}

// Lê o código de um site e o remove de uma lista
void remover_site(AVL_SITE *lista_sites) {
    printf("\n==========REMOVER SITE==========\n");

    // Recebe o código do site
    int codigo;
    printf("Digite o código do site:\n");
    scanf("%d", &codigo);

    // Tenta remover o site
    if (!avl_site_remover(lista_sites, codigo))
        printf("\nCódigo inexistente. Não foi possível apagar o site!\n");

    else
        printf("\nSite removido com sucesso!");

    // Imprime a nova lista
    printf("\n================================\n\n");
    avl_site_imprimir(lista_sites);
    printf("================================\n\n");
}

// Lê o código de um site e insere uma palavra-chave
void inserir_palavra_chave(AVL_SITE *lista_sites) {
    printf("\n=====INSERIR PALAVRA-CHAVE======\n");

    // Recebe o código do site
    int codigo;
    printf("Digite o código do site:\n");
    scanf("%d", &codigo);
    printf("\n");

    // Busca o site
    SITE *site = avl_site_buscar(lista_sites, codigo);

    // Se existir, recebe e insere a nova palavra-chave
    if (site != NULL) {
        printf("Digite a nova palavra-chave:\n");

        char *auxiliar = NULL;
        do {
            limpa_entrada(stdin);
            auxiliar = ler_linha(stdin, LIMITE_STRING);
            printf("\n");

            if (auxiliar != NULL) {
                PCHAVE *pchave = pchave_criar(auxiliar);

                if (avl_pchave_inserir(site_get_palavras_chave(site), pchave) == FALSE) {
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
    printf("\n================================\n\n");
    avl_site_imprimir(lista_sites);
    printf("================================\n\n");
}

// Lê o código de um site e atualiza sua relevância
void atualizar_relevancia(AVL_SITE *lista_sites) {
    printf("\n======ATUALIZAR RELEVÂNCIA======\n");

    // Recebe o código do site
    int codigo;
    printf("Digite o código do site:\n");
    scanf("%d", &codigo);
    printf("\n");

    // Busca o site
    SITE *site = avl_site_buscar(lista_sites, codigo);

    // Se o site existir, recebe e atribui a nova relevância
    if (site != NULL) {
        int relevancia;
        printf("Digite a nova relevância:\n");
        scanf("%d", &relevancia);
        printf("\n");
        site_set_relevancia(site, relevancia);
        printf("Relevância alterada com sucesso!\n");
    } else
        printf("Site inexistente. Impossível atualizar relevância!\n");

    // Imprime a nova lista
    printf("\n================================\n\n");
    avl_site_imprimir(lista_sites);
    printf("================================\n\n");
}

// Lê uma palavra chave, busca entre os sites e exibe os correspondentes
void busca_pchave(AVL_SITE *arvore) {
    printf("\n======BUSCAR PALAVRA-CHAVE=======\n");
    printf("Digite a palavra-chave:\n");

    // Recebe a palavra
    char *auxiliar = ler_linha(stdin, LIMITE_STRING);
    printf("\n");

    // Busca pelos sites
    LISTA_SITE *lista = avl_site_buscar_pchave(arvore, auxiliar);
    if (lista != NULL)
        lista_site_imprimir(lista, 0);
    else
        printf("Nenhum site relevante encontrado\n");

    // Apaga a busca
    lista_site_apagar(&lista);

    free(auxiliar);
}

// Lê uma palavra chave, busca entre os sites e exibe as sugestões
void sugestao_sites(AVL_SITE *arvore) {
    printf("\n======SUGESTÃO DE SITES=======\n");
    printf("Digite a palavra-chave:\n");

    // Recebe a palavra
    char *auxiliar = ler_linha(stdin, LIMITE_STRING);
    printf("\n");

    // Passo A: buscar a palavra fornecida entre as palavras-chave de cada
    // site, selecionando aqueles que a contém
    LISTA_SITE *lista_preliminar = avl_site_buscar_pchave(arvore, auxiliar);

    // Passo B: coletar todas as palavras-chave dos sites selecionados
    // no Passo A
    AVL_PCHAVE *avl_pchave_destino = lista_site_get_pchaves(lista_preliminar);

    // Passo C: buscar os sites que contêm alguma das palavras-chave
    // identificadas no Passo B;
    LISTA_SITE *lista_site = lista_site_criar();
    PCHAVE *pchave = avl_pchave_get_raiz(avl_pchave_destino);
    while (pchave != NULL) {
        LISTA_SITE *sites_pchave_atual = avl_site_buscar_pchave(arvore, pchave_get_string(pchave));
        lista_site_inserir_sites(sites_pchave_atual, lista_site);
        pchave_apagar(&pchave);
        pchave = avl_pchave_get_raiz(avl_pchave_destino);
        lista_site_apagar(&sites_pchave_atual);
    }

    // Passo D: mostrar o nome e o link dos cinco (5) sites mais relevantes
    // ordenados por relevância
    lista_site_imprimir(lista_site, 1);

    // Libera memória
    lista_site_apagar(&lista_preliminar);
    avl_pchave_apagar(&avl_pchave_destino);
    lista_site_apagar(&lista_site);
    free(auxiliar);
}