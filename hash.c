#include "hash.h"

Hash* criar_hash(int tamanho) {
    Hash *hash = (Hash *)malloc(sizeof(Hash));
    hash->tamanho = tamanho;
    hash->itens = (Item *)malloc(tamanho * sizeof(Item));
    
    for (int i = 0; i < tamanho; i++) {
        hash->itens[i].chave = -1; // Inicializando chaves como -1 para indicar vazio
        hash->itens[i].valor = 0;
    }
    
    return hash;
}

void destruir_hash(Hash *hash) {
    if (hash != NULL) {
        free(hash->itens);
        free(hash);
    }
}

static int contar_digitos(long num) {
    if (num == 0) return 1;
    int contagem = 0;
    while (num != 0) {
        num /= 10; // Remove o último dígito
        contagem++;
    }
    return contagem;
}

int quadrado_medio(int chave, int tamanho) {
    long quadrado = (long)chave * chave; // Calcula o quadrado da chave
    int num_digitos = contar_digitos(quadrado); // Conta os dígitos do quadrado
    int meio = num_digitos / 2; // Encontra o meio do número
    int deslocamento = (num_digitos % 2 == 0) ? meio - 1 : meio; // Ajusta o deslocamento para números pares/ímpares
    
    // Extrai os dígitos do meio
    long divisor = pow(10, deslocamento);
    long resto = (quadrado / divisor) % 100; // Extrai dois dígitos do meio
    
    return resto % tamanho; // Retorna o índice na tabela hash
}

void inserir_hash(Hash *hash, int chave, int valor) {
    int indice = quadrado_medio(chave, hash->tamanho); // Usando o quadrado médio para encontrar o índice
    while (hash->itens[indice].chave != -1) { // Percorrendo até encontrar um espaço vazio
        if (hash->itens[indice].chave == chave) { // Se a chave já existe, atualiza o valor
            hash->itens[indice].valor = valor;
            return;
        }
        indice = (indice + 1) % hash->tamanho; // Probing linear
    }
    hash->itens[indice].chave = chave; // Insere a nova chave
    hash->itens[indice].valor = valor; // Insere o valor associado à chave
}

int buscar_hash(Hash *hash, int chave) {
    int indice = quadrado_medio(chave, hash->tamanho);
    int pos_original = indice;
    
    do {
        if (hash->itens[indice].chave == chave) {
            return hash->itens[indice].valor;
        }
        if (hash->itens[indice].chave == -1) {
            break; // Não encontrado
        }
        indice = (indice + 1) % hash->tamanho;
    } while (indice != pos_original);
    
    return -1; // Não encontrado
}

void remover_hash(Hash *hash, int chave) {
    int indice = abs(chave) % hash->tamanho; // Usando módulo para encontrar o índice
    while (hash->itens[indice].chave != -1) { // Percorrendo até encontrar a chave ou um espaço vazio
        if (hash->itens[indice].chave == chave) {
            hash->itens[indice].chave = -1; // Marca como vazio
            hash->itens[indice].valor = 0; // Zera o valor
            return;
        }
        indice = (indice + 1) % hash->tamanho; // Probing linear
    }
}

void imprimir_hash(Hash *hash) {
    for (int i = 0; i < hash->tamanho; i++) {
        if (hash->itens[i].chave != -1) { // Verifica se o espaço não está vazio
            printf("Chave: %d, Valor: %d\n", hash->itens[i].chave, hash->itens[i].valor);
        }
    }
}