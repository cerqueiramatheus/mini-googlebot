#ifndef SITE_H
#include <stdio.h>

#include "utils.h"

#define SITE_H

// Para operações booleanas
#define boolean int
#define TRUE 1
#define FALSE 0

// Definições de limite previstas pelo exercício
#define LIMITE_PALAVRAS 10
#define LIMITE_STRING 50

typedef struct site_ SITE;

SITE *inserir_site(int codigo, char *nome, int relevancia, char *link, char **palavras_chave);

int remover_site(SITE **site);

void inserir_palavra_chave(SITE **site, char *nova_palavra);

void atualizar_relevancia(SITE **site, int nova_relevancia);

SITE **readFile(FILE *inputFile);

#endif