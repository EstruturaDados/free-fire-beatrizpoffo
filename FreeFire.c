#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 50   // Capacidade da lista estática
#define TAM_NOME 50  // Tamanho máximo do nome do item

typedef struct {
    char nome[TAM_NOME];
    int poder;
} Item;

typedef struct {
    Item itens[TAM_MAX];
    int qtd;
} ListaEstatica;

typedef struct Nodo {
    Item item;
    struct Nodo *prox;
} Nodo;

typedef struct {
    Nodo *inicio;
} ListaEncadeada;

void inicializarListaEstatica(ListaEstatica *l) {
    l->qtd = 0;
}

int inserirListaEstatica(ListaEstatica *l, Item item) {
    if (l->qtd >= TAM_MAX) {
        printf("❌ Lista estática cheia!\n");
        return 0;
    }
    l->itens[l->qtd++] = item;
    return 1;
}

int removerListaEstatica(ListaEstatica *l, char nome[]) {
    for (int i = 0; i < l->qtd; i++) {
        if (strcmp(l->itens[i].nome, nome) == 0) {
            for (int j = i; j < l->qtd - 1; j++) {
                l->itens[j] = l->itens[j + 1];
            }
            l->qtd--;
            return 1;
        }
    }
    return 0;
}

void listarListaEstatica(ListaEstatica *l) {
    if (l->qtd == 0) {
        printf("Lista estática vazia.\n");
        return;
    }
    printf("=== Itens da Lista Estática ===\n");
    for (int i = 0; i < l->qtd; i++) {
        printf("%d. %s (Poder: %d)\n", i + 1, l->itens[i].nome, l->itens[i].poder);
    }
}

Item* buscarListaEstatica(ListaEstatica *l, char nome[]) {
    for (int i = 0; i < l->qtd; i++) {
        if (strcmp(l->itens[i].nome, nome) == 0) {
            return &l->itens[i];
        }
    }
    return NULL;
}

void inicializarListaEncadeada(ListaEncadeada *l) {
    l->inicio = NULL;
}

void inserirListaEncadeada(ListaEncadeada *l, Item item) {
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    novo->item = item;
    novo->prox = l->inicio;
    l->inicio = novo;
}

int removerListaEncadeada(ListaEncadeada *l, char nome[]) {
    Nodo *ant = NULL, *atual = l->inicio;
    while (atual != NULL && strcmp(atual->item.nome, nome) != 0) {
        ant = atual;
        atual = atual->prox;
    }
    if (atual == NULL)
        return 0;
    if (ant == NULL)
        l->inicio = atual->prox;
    else
        ant->prox = atual->prox;
    free(atual);
    return 1;
}

void listarListaEncadeada(ListaEncadeada *l) {
    if (l->inicio == NULL) {
        printf("Lista encadeada vazia.\n");
        return;
    }
    printf("=== Itens da Lista Encadeada ===\n");
    Nodo *aux = l->inicio;
    int i = 1;
    while (aux != NULL) {
        printf("%d. %s (Poder: %d)\n", i++, aux->item.nome, aux->item.poder);
        aux = aux->prox;
    }
}

Item* buscarListaEncadeada(ListaEncadeada *l, char nome[]) {
    Nodo *aux = l->inicio;
    while (aux != NULL) {
        if (strcmp(aux->item.nome, nome) == 0)
            return &aux->item;
        aux = aux->prox;
    }
    return NULL;
}

void exibirMenu() {
    printf("\n=== MENU DE AVENTURA ===\n");
    printf("1. Inserir item na lista estática\n");
    printf("2. Remover item da lista estática\n");
    printf("3. Listar itens da lista estática\n");
    printf("4. Buscar item na lista estática\n");
    printf("5. Inserir item na lista encadeada\n");
    printf("6. Remover item da lista encadeada\n");
    printf("7. Listar itens da lista encadeada\n");
    printf("8. Buscar item na lista encadeada\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

Item criarItem() {
    Item item;
    printf("Nome do item: ");
    scanf(" %[^\n]", item.nome);
    printf("Poder do item: ");
    scanf("%d", &item.poder);
    return item;
}

int main() {
    ListaEstatica listaE;
    ListaEncadeada listaL;
    inicializarListaEstatica(&listaE);
    inicializarListaEncadeada(&listaL);

    int opcao;
    char nome[TAM_NOME];

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (inserirListaEstatica(&listaE, criarItem()))
                    printf("✅ Item inserido na lista estática!\n");
                break;
            case 2:
                printf("Nome do item a remover: ");
                scanf(" %[^\n]", nome);
                if (removerListaEstatica(&listaE, nome))
                    printf("✅ Item removido!\n");
                else
                    printf("❌ Item não encontrado!\n");
                break;
            case 3:
                listarListaEstatica(&listaE);
                break;
            case 4:
                printf("Nome do item a buscar: ");
                scanf(" %[^\n]", nome);
                Item *encontradoE = buscarListaEstatica(&listaE, nome);
                if (encontradoE)
                    printf("Encontrado: %s (Poder: %d)\n", encontradoE->nome, encontradoE->poder);
                else
                    printf("❌ Item não encontrado!\n");
                break;
            case 5:
                inserirListaEncadeada(&listaL, criarItem());
                printf("✅ Item inserido na lista encadeada!\n");
                break;
            case 6:
                printf("Nome do item a remover: ");
                scanf(" %[^\n]", nome);
                if (removerListaEncadeada(&listaL, nome))
                    printf("✅ Item removido!\n");
                else
                    printf("❌ Item não encontrado!\n");
                break;
            case 7:
                listarListaEncadeada(&listaL);
                break;
            case 8:
                printf("Nome do item a buscar: ");
                scanf(" %[^\n]", nome);
                Item *encontradoL = buscarListaEncadeada(&listaL, nome);
                if (encontradoL)
                    printf("Encontrado: %s (Poder: %d)\n", encontradoL->nome, encontradoL->poder);
                else
                    printf("❌ Item não encontrado!\n");
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("❌ Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
