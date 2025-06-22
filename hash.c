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
    if (hash == NULL) return;
    
    int indice = quadrado_medio(chave, hash->tamanho);
    int pos_original = indice;
    int vazios = 0;
    
    do {
        if (hash->itens[indice].chave == chave) {
            hash->itens[indice].valor = valor;
            printf("Valor atualizado para chave %d.\n", chave);
            return;
        }
        if (hash->itens[indice].chave == -1) {
            hash->itens[indice].chave = chave;
            hash->itens[indice].valor = valor;
            printf("Elemento inserido na posicao %d.\n", indice);
            return;
        }
        indice = (indice + 1) % hash->tamanho;
        vazios++;
    } while (indice != pos_original && vazios < hash->tamanho);
    
    printf("Erro: Tabela hash cheia! Nao foi possivel inserir a chave %d.\n", chave);
}

int buscar_hash(Hash *hash, int chave) {
    if (hash == NULL) return -1; // Retorna -1 se a tabela hash for nula
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
    if (hash == NULL) return; // Retorna se a tabela hash for nula
    int indice = quadrado_medio(chave, hash->tamanho);
    int pos_original = indice;

    do {
        if (hash->itens[indice].chave == chave) {
            hash->itens[indice].chave = -1; // Marca como vazio
            hash->itens[indice].valor = 0; // Limpa o valor
            printf("Elemento com chave %d removido.\n", chave);
            return;
        }
        if (hash->itens[indice].chave == -1) {
            break; // Não encontrado
        }
        indice = (indice + 1) % hash->tamanho;
    } while (indice != pos_original);
    printf("Chave %d não encontrada para remoção.\n", chave);

}

void imprimir_hash(Hash *hash) {
    if (hash == NULL) return;
    
    printf("\n--- TABELA HASH (Tamanho: %d) ---\n", hash->tamanho);
    for (int i = 0; i < hash->tamanho; i++) {
        if (hash->itens[i].chave != -1) {
            printf("Posição %d: Chave: %d, Valor: %d\n", i, hash->itens[i].chave, hash->itens[i].valor);
        } else {
            printf("Posição %d: Vazia\n", i);
        }
    }
    printf("-----------------------------\n");
}

void menu() {
    int tamanho;
    printf("Digite o tamanho da tabela hash: ");
    scanf("%d", &tamanho);

    Hash *hash = criar_hash(tamanho);
    int opcao, chave, valor, resultado;
    do {
        printf("\n------- Menu -------\n");
        printf("1. Inserir elemento\n");
        printf("2. Buscar elemento\n");
        printf("3. Remover elemento\n");
        printf("4. Imprimir Tabela\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a chave: ");
                scanf("%d", &chave);
                printf("Digite o valor: ");
                scanf("%d", &valor);
                inserir_hash(hash, chave, valor);
                break;
            case 2:
                printf("Digite a chave a ser buscada: ");
                scanf("%d", &chave);
                resultado = buscar_hash(hash, chave);
                if (resultado != -1) {
                    printf("Valor encontrado: %d\n", resultado);
                } else {
                    printf("Chave não encontrada.\n");
                }
                break;
            case 3:
                printf("Digite a chave a ser removida: ");
                scanf("%d", &chave);
                remover_hash(hash, chave);
                break;
            case 4:
                imprimir_hash(hash);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);

    destruir_hash(hash);
    printf("Programa encerrado.\n");
}