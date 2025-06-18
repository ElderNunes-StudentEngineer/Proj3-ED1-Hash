/*
* Trabalho de Estruturas de Dados - Hash
* Implementação usando o método do quadrado médio
*/

#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAMANHO_HASH 100 // Definindo o tamanho da tabela hash

typedef struct {
    int chave;
    int valor;
} Item;

typedef struct {
    Item *itens;
    int tamanho;
} Hash;

// Funções para manipulação de tabela hash
Hash* criar_hash(int tamanho);
void destruir_hash(Hash *hash);
void inserir_hash(Hash *hash, int chave, int valor);
int quadrado_medio(int chave, int tamanho);
int buscar_hash(Hash *hash, int chave);
void remover_hash(Hash *hash, int chave);
void imprimir_hash(Hash *hash); 


#endif