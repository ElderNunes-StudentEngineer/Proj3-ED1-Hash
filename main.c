#include "hash.h"

int main(void){
    Hash *hash = criar_hash(TAMANHO_HASH);
    if (hash == NULL) {
        fprintf(stderr, "Erro ao criar a tabela hash.\n");
        return 1;
    }
    // Inserindo alguns valores na tabela hash
    inserir_hash(hash, 1, 100);
    inserir_hash(hash, 2, 200);
    inserir_hash(hash, 3, 300);
    inserir_hash(hash, 4, 400);

    // Imprimindo a tabela hash
    printf("Tabela Hash:\n");
    imprimir_hash(hash);
    
    // Buscando valores
    int valor = buscar_hash(hash, 2);
    printf("\nValor associado à chave 2: %d\n", valor);

    // Removendo um valor
    remover_hash(hash, 3);
    printf("\nTabela Hash após remoção da chave 3:\n");
    imprimir_hash(hash);

    // Destruindo a tabela hash
    destruir_hash(hash);
    printf("\nTabela Hash destruída.\n");

    return 0;
}