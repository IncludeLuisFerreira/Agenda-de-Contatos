#ifndef AGENDACONTATO_H
#define AGENDACONTATO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MALLOC_ERROR    "Erro ao alocar memoria dinamicamente!\n"
#define EMPTYLIST       "Lista vazia!\n"
#define NOTFOUND        "Contato nao encontrado!\n"
#define MAX_NAME        50
#define MAX_EMAIL       30
#define MAX_FONE        11
#define MAX_DDD         4


struct endereco{
    char rua[MAX_NAME];
    int numero;
    char bairro[MAX_NAME];
    char cidade[MAX_NAME];
};

struct telefone{
    char DDD[MAX_DDD];
    unsigned char numero_telefone[MAX_FONE];
};

typedef struct contato{
    char nome[MAX_NAME];
    char email[MAX_EMAIL];
    struct endereco end;
    struct telefone fone_movel;
    struct telefone fone_fixo;
    struct contato *proximo;
} Contato;

typedef struct lista{
    Contato *inicio;
    int TAM;
}Lista;

Contato lerContato();
void initLista(Lista *ptr);
void insert(Lista *lista, Contato contato, int pos);
void removeNode(Lista *lista, int pos);
void editarContato(Lista *lista, int pos);
void imprimirNode(Contato *aux, int i);
void imprimir(Lista *lista);
Contato* busca(Lista *lista, const char nome[50]);
void memoryContato(Lista *lista);
void safe_free(Lista *lista, Contato **contato);

/*Inicia uma variável do tipo Lista.
Parâmetros: 
    ptr: ponteiro do tipo Lista que será inicializada.
*/
void initLista(Lista *ptr){
    ptr->inicio = NULL;
    ptr->TAM = 0;

    memoryContato(ptr);
}
// Lê e retorna uma variável do tipo Contato.
Contato lerContato(){
    Contato c;
    fflush(stdin);

    printf("Digite o nome: ");
    fgets(c.nome, MAX_NAME, stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Digite o email: ");
    fgets(c.email, MAX_EMAIL, stdin);
    c.email[strcspn(c.email, "\n")] = '\0';

    printf("Digite o nome da cidade: ");
    fgets(c.end.cidade, MAX_NAME, stdin);
    c.end.cidade[strcspn(c.end.cidade, "\n")] = '\0';

    printf("Digite o nome do bairro: ");
    fgets(c.end.bairro, MAX_NAME, stdin);
    c.end.bairro[strcspn(c.end.bairro, "\n")] = '\0';

    printf("Digite o nome da rua: ");
    fgets(c.end.rua, MAX_NAME, stdin);
    c.end.rua[strcspn(c.end.rua, "\n")] = '\0';

    printf("Digite o numero da casa: ");
    scanf("%d", &c.end.numero);
    fflush(stdin);

    printf("DDD(telefone fixo): ");
    fgets(c.fone_fixo.DDD, 3, stdin);
    c.fone_fixo.DDD[strcspn(c.fone_fixo.DDD, "\n")] = '\0';
    fflush(stdin);

    printf("Numero do telefone fixo: ");
    fgets(c.fone_fixo.numero_telefone, 10, stdin);
    c.fone_fixo.numero_telefone[strcspn(c.fone_fixo.numero_telefone, "\n")] = '\0';

    printf("DDD(telefone movel): ");
    fgets(c.fone_movel.DDD, 3, stdin);
    c.fone_movel.DDD[strcspn(c.fone_movel.DDD, "\n")] = '\0';
    fflush(stdin);

    printf("Numero do telefone movel: ");
    fgets(c.fone_movel.numero_telefone, 10, stdin);
    c.fone_movel.numero_telefone[strcspn(c.fone_movel.numero_telefone, "\n")] = '\0';

    return c;
}

/// @brief Valida a posição que o usuario digitou
/// @param pos tipo int representando a posição digitada pelo usuario
/// @param list_tam tipo int tamanho atual da lista
/// @return 1 se estiver dentro do conjunto e 0 se estiver fora.
int valid_position(int pos, int list_tam){
    return (pos > 0 && pos <= list_tam + 1);
}

/*Insere um nó do tipo Contato na lista.

Parâmetros: 
    lista: ponteiro do tipo Lista onde o nó será inserido, caso lista->inicio == NULL encerra a função com mensagem de erro.
    contato: variável do tipo Contato que será inserida na lista.
    pos: posição onde será inserida a variável do tipo Contato.
*/
void insert(Lista *lista, Contato contato, int pos){
    Contato *novo = (Contato*)malloc(sizeof(Contato));
    Contato *aux = lista->inicio;
    
    if (novo) *novo = contato;
    else
    {
        printf(MALLOC_ERROR);
        return ;
    }

    if (!lista->inicio)
    {
        lista->inicio = novo;
        novo->proximo = NULL;
    }

    if (pos == 1)
    {
        novo->proximo = lista->inicio;
        lista->inicio = novo;
    }
    else if (pos > 1 && pos < lista->TAM + 1)
    {
        for (int i = 1; i < pos - 1; i++)
        {
            aux = aux->proximo;
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
    }
    else if (pos == lista->TAM + 1)
    {
        while(aux->proximo)
        {
            aux = aux->proximo;
        }
        aux->proximo = novo;
        novo->proximo = NULL;
    }
    lista->TAM++;
}
/*Remove um nó do tipo Contato da lista
Parâmetros:
    lista: ponteiro do tipo Lista onde será removido o nó, caso lista->inicio == NULL encerra a função com mensagem de erro.
    pos: posição do nó que será removido da lista.
*/
void removeNode(Lista *lista, int pos){
    Contato* aux, *remove = lista->inicio;

    if (!lista->inicio)
    {
        printf(EMPTYLIST);
        return ;
    }

    if (pos == 1)
    {
        remove = lista->inicio;
        lista->inicio = remove->proximo;
    }
    else if (pos > 1 && pos < lista->TAM)
    {
        aux = remove;
        for (int i = 1; i < pos - 1; i++)
        {
            aux = aux->proximo;
        }
        remove = aux->proximo;
        aux->proximo = remove->proximo;
    }
    else if (pos == lista->TAM)
    {
        aux = remove;
        while(aux->proximo->proximo)
        {
            aux = aux->proximo;
        }
        remove = aux->proximo;
        aux->proximo = NULL;
    }
    else 
    {
        printf("Posição inválida!\n");
        return ;
    }
    free(remove);
    remove = NULL;
    lista->TAM--;
}
/*Edita um nó do tipo Contato da lista mediante a confirmação do usuário.

Parâmetros:
    lista: ponteiro do tipo Lista onde será editado o nó, caso lista->inicio == NULL encerra a função com mensagem de erro.
    pos: posicao do nó que será editado na lista.
*/
void editarContato(Lista *lista, int pos){
    Contato *aux = lista->inicio;
    int i = 1, user;

    if (!lista->inicio)
    {
        printf(EMPTYLIST);
        return ;
    }

    while(i != pos)
    {
        aux = aux->proximo;
        i++;
    }

    printf("Editando Contato:\n");
    printf("Nome: %s\n", aux->nome);
    printf("[1]-Confirmar\t[0]-Cancelar: ");
    scanf("%d", &user);

    if (user == 1)
    {
        *aux = lerContato();
        printf("Editado com sucesso!\n");
    }
    else
    {
        printf("Processo cancelado!\n");
    }
}
/*Imprime o conteúdo de um nó do tipo Contato.
Parâmetros:
    aux = variável do tipo Contato que será impressa na tela.
    i = posicao do nó na lista.
*/
void imprimirNode(Contato *aux, int i){
    printf("\n\t****Contato %d****\n",i + 1);
    printf("-Nome: %s\n",aux->nome);
    printf("-Email: %s\n", aux->email);
    printf("-Rua: %s\n",aux->end.rua);
    printf("-Numero da casa: %d\n",aux->end.numero);
    printf("-Bairro: %s\n", aux->end.bairro);
    printf("-Cidade: %s\n", aux->end.cidade);
    printf("-DDD(fixo): %s\n", aux->fone_fixo.DDD);
    printf("-Telefone(fixo): %s\n", aux->fone_fixo.numero_telefone);
    printf("-DDD(movel): %s\n", aux->fone_movel.DDD);
    printf("-Telefone(movel): %s\n", aux->fone_movel.numero_telefone);
    printf("\t****************\n");
}
/*Imprime todos os nós de uma lista.
Parâmetros:
    lista: ponteiro do tipo Lista de onde será lido os nós, caso lista->inicio == NULL encerra a função com mensagem de erro.*/
void imprimir(Lista *lista){
    Contato *aux = lista->inicio;

    if (!aux)
    {
        printf(EMPTYLIST);
        return;
    }

    for (int i = 0; i < lista->TAM; i++)
    {
        imprimirNode(aux, i);
        aux = aux->proximo;
    }
}
/*Busca sequêncialmente um nó na lista.
Parâmetros:
    lista: ponteiro do tipo Lista onde será buscado o nó, caso lista->inicio == NULL encerra a função com mensagem de erro.
    nome: nome usado para achar o nó que tenha o mesmo nome no campo Nó->nome.
*/
Contato* busca(Lista *lista, const char nome[50]){
    Contato *aux = lista->inicio;

    if (!aux)
    {
        printf(EMPTYLIST);
        return NULL;
    }

    for (int i = 0; i < lista->TAM; i++)
    {
        if (strcmp(nome, aux->nome) == 0)
        {
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}

void memoryContato(Lista *lista){       // erro ao salvar ddd e telefone 0 e 1.
    Contato *novo = (Contato*)malloc(5 * sizeof(Contato));

    strcpy(novo[0].nome,"Carlos Almeida Dolgo\0");
    strcpy(novo[0].email, "carlos_al@gmail.com\0");
    strcpy(novo[0].end.rua, "Acarpio\0");
    novo[0].end.numero = 10;
    strcpy(novo[0].end.bairro,"Monte Verde\0");
    strcpy(novo[0].end.cidade,"Pocos de Caldas\0");
    strcpy(novo[0].fone_fixo.DDD, "35\0");
    strcpy(novo[0].fone_fixo.numero_telefone, "93062412\0");
    strcpy(novo[0].fone_movel.DDD, "35");
    strcpy(novo[0].fone_movel.numero_telefone, "936763322\0");


    lista->inicio = novo;

    strcpy(novo[1].nome,"Maria Clara Gonsalves Silveira\0");
    strcpy(novo[1].email, "MariaClaraGS@gmail.com\0");
    strcpy(novo[1].end.rua, "Margarida\0");
    novo[1].end.numero = 320;
    strcpy(novo[1].end.bairro,"Jardim flora\0");
    strcpy(novo[1].end.cidade,"Campinas\0");
    strcpy(novo[1].fone_fixo.DDD, "19\0");
    strcpy(novo[1].fone_fixo.numero_telefone, "96271824\0");
    strcpy(novo[1].fone_movel.DDD, "19\0");
    strcpy(novo[1].fone_movel.numero_telefone, "93062412\0");

    novo->proximo = (novo + 1);


    strcpy(novo[2].nome,"Jucelino Kubistech\0");
    strcpy(novo[2].email, "JKpresid@hotmail.com\0");
    strcpy(novo[2].end.rua, "Avelida Marida\0");
    novo[2].end.numero = 140;
    strcpy(novo[2].end.bairro,"Vila olimpia\0");
    strcpy(novo[2].end.cidade,"Governador Valadares\0");
    strcpy(novo[2].fone_fixo.DDD, "78\0");
    strcpy(novo[2].fone_fixo.numero_telefone, "951431435\0");
    strcpy(novo[2].fone_movel.DDD, "78\0");
    strcpy(novo[2].fone_movel.numero_telefone, "942015422\0");

    (novo + 1)->proximo = (novo + 2);

    strcpy(novo[3].nome,"Felipe Garcia Pavila\0");
    strcpy(novo[3].email, "Felipe2.garcia@if.edu.br\0");
    strcpy(novo[3].end.rua, "Argentina\0");
    novo[3].end.numero = 661;
    strcpy(novo[3].end.bairro,"Jardim formosa\0");
    strcpy(novo[3].end.cidade,"Pocos de Caldas\0");
    strcpy(novo[3].fone_fixo.DDD, "35\0");
    strcpy(novo[3].fone_fixo.numero_telefone, "931605443\0");
    strcpy(novo[3].fone_movel.DDD, "35\0");
    strcpy(novo[3].fone_movel.numero_telefone, "994072679\0");

    (novo + 2)->proximo = (novo + 3);

    strcpy(novo[4].nome,"Giovanna Lopes Carmim\0");
    strcpy(novo[4].email, "GI_lops@gmail.com\0");
    strcpy(novo[4].end.rua, "Lacio\0");
    novo[4].end.numero = 1107;
    strcpy(novo[4].end.bairro,"Vila minerva\0");
    strcpy(novo[4].end.cidade,"Sao Paulo\0");
    strcpy(novo[4].fone_fixo.DDD, "87\0");
    strcpy(novo[4].fone_fixo.numero_telefone, "91973455\0");
    strcpy(novo[4].fone_movel.DDD, "85\0");
    strcpy(novo[4].fone_movel.numero_telefone, "98732456\0");

    (novo + 3)->proximo = (novo + 4);
    lista->TAM += 5;
}

void safe_free(Lista *lista, Contato **contato){
    if (lista->inicio != NULL)
    {
        Contato *nod = lista->inicio;
        Contato *prox = NULL;

        for (int i = 0; i < lista->TAM; i++)
        {
            prox = nod->proximo;
            free(nod);
            nod = prox;
        }
        lista->inicio = NULL;
        lista->TAM = 0;
    } 

    if (*contato != NULL) 
    {
        free(*contato); 
        *contato = NULL; 
    }
}


#endif