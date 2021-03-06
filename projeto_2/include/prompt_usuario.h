#ifndef PROMPT_H
#define PROMPT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl_site.h"
#include "avl_pchave.h"
#include "lista_site.h"
#include "utils.h"
#include "pchave.h"

/**
 * Interface de aplicação dos TADs e comunicação com o usuário
 */

void imprime_menu();
SITE *site_criar_completo();
void inserir_site(AVL_SITE *lista_sites);
void remover_site(AVL_SITE *lista_sites);
void inserir_palavra_chave(AVL_SITE *lista_sites);
void atualizar_relevancia(AVL_SITE *lista_sites);
void busca_pchave(AVL_SITE *arvore);
void sugestao_sites(AVL_SITE *arvore);

#endif